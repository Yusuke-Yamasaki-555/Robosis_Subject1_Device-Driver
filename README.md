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
- 抵抗(300Ω程度のもの) 3個
- ジャンパーワイヤー(オス・メス) 4本

## 配線
- 以下の写真のように配線を組んでください。
![IMG_2575](https://user-images.githubusercontent.com/91410662/145711892-803c7371-49a0-4cec-95f9-2ea7ef06c6bc.JPG)
![配線](https://user-images.githubusercontent.com/91410662/145711824-d8f3b4e5-b558-4ea0-ba32-56ebfa7426cb.jpg)
- なお、一番右の緑色のLEDが二進数の一桁目、黄色が二桁目、赤色が三桁目となっています。
- 各LEDとGPIOピンの対応は、以下のようになっています。

| LED-color | GPIO-number |
| --- | --- |
| green | 25 |
| yellow | 24 |
| red | 23 |

- Raspberry Pi 3B+ のピン配置は、[こちら](https://www.raspberrypi.com/documentation/computers/os.html#gpio-and-the-40-pin-header)を参照してください。

## 実行方法
### セットアップ
- このリポジトリをクローン後、生成されたディレクトリに移動し、set_make.bashを実行してください。以下がそのコマンドです。(コマンド内の”$”は、入力する必要がありません)
```sh
$ git clone https://github.com/Yusuke-Yamasaki-555/Robosis_Subject1_Device-Driver.git # https通信の場合
 # ssh通信の場合：$ git clone git@github.com:Yusuke-Yamasaki-555/Robosis_Subject1_Device-Driver.git
$ cd Robosis_Subject_Device-Driver/
$ ./set_make.bash # セットアップ用のスクリプト
```
- もし、"myled_bash","set_make.bash","remove_make.bash"の各ファイルに実行権限がない場合は、以下のコマンドを実行し、実行権限を付与する必要があります。
```sh
$ chmod 775 myled_bash
$ chmod 775 set_make.bash
$ chmod 775 remove_make.bash
```
- 以上で、デバイスドライバが実行出来る状態となりました。

### 実行
- 以下のコマンドで、シェルスクリプトであるmyled_bashが実行出来ます。実際に実行している様子の動画は[こちら]()(リンク先：Youtube)。
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
- このリポジトリにある全てのコードは、GNU General Public License v3.0 を採用しています。ライセンスの内容はCOPYINGファイルに記載されており、各プログラムの著作権については各プログラムのコード内に記載されています。(GNU General Public Lisence 公式サイト：https://www.gnu.org/licenses/gpl-3.0.en.html)
- myled.cは、ryuichiueda様から公開されているGitHubの[リポジトリ](https://github.com/ryuichiueda/robosys2020/blob/master/md/device_driver.md)を参考にさせていただき、作成しました。
