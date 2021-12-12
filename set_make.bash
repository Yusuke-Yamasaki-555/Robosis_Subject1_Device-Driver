#!/bin/bash

# author : YusukeYamasaki
# lisence : GPL
# description : Set up for LED control
# version : 0.0.1

echo ===== make =====
make
sleep 0.5
echo ===== install module =====
sudo insmod myled.ko
sleep 0.5
echo ===== authorise module =====
sudo chmod 666 /dev/myled0
sleep 0.5
echo ===== check "ls -l /dev/myled0" =====
ls -l /dev/myled0
sleep 0.5
