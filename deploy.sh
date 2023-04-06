#!/bin/bash
scp artifacts/s21_cat artifacts/s21_grep user@19.168.0.2:/home/user/
ssh root@19.168.0.2 "mv /home/user/s21_cat /home/user/s21_grep /usr/local/bin/"
