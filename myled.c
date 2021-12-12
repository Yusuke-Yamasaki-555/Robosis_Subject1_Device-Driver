/*
	Copyright (C) 2021 Yusuke Yamasaki, Ryuichi Ueda

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>

/* Lisence */
MODULE_AUTHOR("Ryuichi Ueda, Yusuke Yamasaki");
MODULE_DESCRIPTION("Driver for LED-Control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");
/* /Lisence */

/* Global */
static dev_t dev;
static struct cdev cdv; // キャラクタデバイスの情報を格納する構造体
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL; // アドレスをマッピングするための配列を定義
/* /Global */

// catすると寿司を表示する無駄機能の実装
static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
	int size = 0;
	char sushi[] = {0xF0,0x9F,0x8D,0xA3,0x0A}; // 寿司の絵文字のバイナリ
	if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
		printk( KERN_INFO "sushi : copy_to_user failed\n" );
		return -EFAULT;
	}
	size += sizeof(sushi);
	return size;
}

// デバイスファイルから(echoで書き込み)の字の読み込み
static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos) // デバイスファイルに書き込みがあった時の挙動
{
	char c;
	if(copy_from_user(&c,buf,sizeof(char))) // copy_from_user:カーネルの外(=ユーザランド)からの字を読み込む
		return -EFAULT; // error

	// ON/OFFの書き込み(z・y：全部、1・2：GPIO23、a・b：GPIO24、A・B：GPIO25)
	if(c == 'z'){
		gpio_base[10] = 1 << 23;
		gpio_base[10] = 1 << 24;
		gpio_base[10] = 1 << 25; // OFF: 「GPCLR0」のGPIO25に対応するところに１を書き込む
	}
	else if(c == 'y'){
		gpio_base[7] = 1 << 23;
		gpio_base[7] = 1 << 24;
		gpio_base[7] = 1 << 25; // ON: 「GPSET0」のGPIO25に対応するところに１を書き込む
	}
	else if(c == '1'){
		gpio_base[7] = 1 << 23;
	}
	else if(c == '2'){
		gpio_base[10] = 1 << 23;
	}
	else if(c == 'a'){
		gpio_base[7] = 1 << 24;
	}
	else if(c == 'b'){
		gpio_base[10] = 1 << 24;
	}
	else if(c == 'A'){
		gpio_base[7] = 1 << 25;
	}
	else if(c == 'B'){
		gpio_base[10] = 1 << 25;
	}

	// printk(KERN_INFO "receive %c\n",c);
	return 1; // 読み込んだ文字数を返す（この場合、１はダミー）このreturn 1がないと、永遠に終わらなくなる。再起必須
}

static struct file_operations led_fops = { // 挙動を書いた関数のポインタを格納する構造体(VFSから使われる)
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};

static int __init init_mod(void) // カーネルモジュールの初期化
{
	int retval;
	int n;

	gpio_base = ioremap_nocache(0x3f200000, 0xA0); // レジスタアドレスのリマップ

	// GPIOピンを出力にする(ピンを出力するレジスタに１を書き込む。他の値は１でないとならない)
	// GPIO25の機能はGPFSEL2にある。GPFSEL2の17,16,15番目のビットを001に設定
	for(n = 23; n <= 25; n++){
		const u32 led = n; // GPIOn
		const u32 index = led/10; // GPFSEL2(GPIO25の入出力を決めるピンが、2?番にある)
		const u32 shift = (led%10)*3;
		const u32 mask = ~(0x7 << shift); // 11111111111111000111111111111111(~は、反転)
		gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift); // 001:output flag\
	                                                                   11111111111111001111111111111111\
								変えたいところだけを０にする | 変えるところに１を入れる
	}

	retval = alloc_chrdev_region(&dev, 0, 1, "myled"); // デバイス番号の取得
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
		
	}
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));
	
	cdev_init(&cdv, &led_fops); // キャラクタデバイスの初期化(file_operationsを返す(led_fops))
	retval = cdev_add(&cdv, dev, 1); // キャラクタデバイスをカーネルに登録
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
	}
	
	// /sys/class下にこのデバイスの情報を置く(ユーザ側から情報が見えるように)
	cls = class_create(THIS_MODULE,"myled"); // class_createでクラスの作成
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev)); // デバイス情報の作成
	return 0;
}

static void __exit cleanup_mod(void) // 後始末
{
	cdev_del(&cdv); // キャラクタデバイスの破棄
	device_destroy(cls, dev); // デバイスの削除
	class_destroy(cls); // クラスの削除
	unregister_chrdev_region(dev, 1); // デバイス番号の開放
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev)); // ログを吐く
}

/* マクロで関数を登録 */
module_init(init_mod);
module_exit(cleanup_mod);
/* /マクロで関数を登録 */
