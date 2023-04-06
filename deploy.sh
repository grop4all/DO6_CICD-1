#!/usr/bin/expect -f
ls .
spawn scp src/cat/s21_cat src/grep/s21_grep student@192.168.0.2:/home/student/

expect {
    "*yes/no" { send -- "yes\r"}
    "*password" { send -- "student\r"}
}
spawn ssh student@19.168.0.2 "echo student | sudo -S mv s21_cat s21_grep /usr/local/bin/"
expect "*password*"
send -- "student\r"
expect eof