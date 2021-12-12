#!/bin/bash

# author : YusukeYamasaki
# lisence : GPL
# description : remove for LED control
# version : 0.0.1

echo ===== remove module =====
sudo rmmod myled
sleep 0.5
echo ===== check "ls -l /dev/myled0"  =====
ls -l /dev/myled0
sleep 0.5
echo ===== make_clean =====
make clean
sleep 0.5
