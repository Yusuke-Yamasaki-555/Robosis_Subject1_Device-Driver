# Robosis_Subject1_Device-Driver
## 概要
- Paspberry Pi で３つのLEDライトをGPIOから制御するデバイスドライバと、それを利用したシェルスクリプトです。
- シェルスクリプトはデバイスドライバの使用例の１つであり、ターミナルに表示された数式にLEDが二進数法を用いてクイズ形式で答えるというものになっています。

## 動作環境
- 機種：Raspberry Pi 3B+
- OS：Ubuntu 20.4.3 LTS
- 最低容量：664KB
- 最低RAM：Raspberry Pi 3B+ の仕様に準拠

## 必要なもの
- Raspberry Pi 3B+ 及び、動作・操作に必要な各種配線
- ブレッドボード
- LED(緑、黄、赤) 各1個
- 抵抗(290Ω) 3個
- ジャンパーワイヤー(オス・メス) 4本

## 配線
- 以下の写真と回路図を参考に配線を組んでください。LEDのアノード・カソードの向きに注意してください。
- ・写真
![配線](https://user-images.githubusercontent.com/91410662/145711824-d8f3b4e5-b558-4ea0-ba32-56ebfa7426cb.jpg)
- ・回路図
![B08E15D9-F770-4041-B619-5F8450DF38E6](https://user-images.githubusercontent.com/91410662/146053105-2e083db8-648e-44da-b861-bc75b89fbb44.jpeg)
- なお、緑色のLEDが二進数の一桁目、黄色が二桁目、赤色が三桁目となっています。
- 各LEDとGPIOピンの対応は、以下のようになっています。

| LED-color | GPIO-number |
| --- | --- |
| green | 25 |
| yellow | 24 |
| red | 23 |

- Raspberry Pi 3B+ のピン配置は、[こちら](https://www.raspberrypi.com/documentation/computers/os.html#gpio-and-the-40-pin-header)を参照してください。

## 実行方法
### セットアップ
- このリポジトリをクローン後、生成されたディレクトリに移動し、**set_make.bash**を実行してください。以下がそのコマンドです。(コマンド内の”$”は、入力する必要がありません)
```sh
$ git clone https://github.com/Yusuke-Yamasaki-555/Robosis_Subject1_Device-Driver.git # https通信の場合
 # ssh通信の場合：$ git clone git@github.com:Yusuke-Yamasaki-555/Robosis_Subject1_Device-Driver.git
$ cd Robosis_Subject_Device-Driver/
$ ./set_make.bash # セットアップ用のスクリプト
```
- もし、**myled_bash** , **set_make.bash** , **remove_make.bash**の各ファイルに実行権限が与えられていない場合、以下のコマンドを実行し、実行権限を付与する必要があります。
```sh
$ chmod 775 myled_bash
$ chmod 775 set_make.bash
$ chmod 775 remove_make.bash
```
- 以上で、デバイスドライバが実行出来る状態となりました。

### 実行
- 以下のコマンドで、シェルスクリプトである**myled_bash**が実行出来ます。これを実行することで、ターミナルに表示される数式に対してLEDが二進数法を用いて答えます。実際に実行している様子の動画は[こちら](https://youtu.be/_6jM9WL6Hgo****)(リンク先：Youtube)。
```sh
$ ./myled_bash
```

### 終了
- 以下のコマンドを実行することでデバイスドライバを削除し、クローン後と同じ状態になります。
```sh
$ ./remove_make.bash # 片付け用のスクリプト
```
- 以降デバイスドライバを必要とする場合、再度セットアップを行ってください。ただし、git cloneコマンドを使用する必要はありません。

## ライセンスについて
- このリポジトリにある全てのコードは、GNU General Public License v3.0 を採用しています。ライセンスの内容は**COPYING**ファイルに記載されており、各プログラムの著作権については各プログラムのコード内に記載されています。(GNU General Public Lisence 公式サイト：https://www.gnu.org/licenses/gpl-3.0.en.html)
- **myled.c**は、ryuichiueda様から公開されているGitHubの[リポジトリ](https://github.com/ryuichiueda/robosys2020/blob/master/md/device_driver.md)を参考にさせていただき、作成しました。
- **README.md**の書き方に関して、[makotoyoshigoe様のREADME.md](https://github.com/makotoyoshigoe/RobotSystem2021_DeviceDriver)を参考にさせていただきました。なお内容と文章に関しましては、私が一から考え記述しており、コピーは一切しておりません。
