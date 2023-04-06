#!/bin/bash
scp artifacts/s21_cat artifacts/s21_grep user@19.168.0.2:/home/user/
ssh user@19.168.0.2 "echo user | sudo -S mv s21_cat s21_grep /usr/local/bin/"