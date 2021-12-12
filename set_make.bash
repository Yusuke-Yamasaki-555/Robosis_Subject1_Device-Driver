#!/bin/bash

:<<'#COMMENT_OUT'
    Copyright (C) 2021 Yusuke Yamasaki

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
#COMMENT_OUT

# author : Yusuke Yamasaki
# lisence : GPL
# description : Set up for LED-control
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
