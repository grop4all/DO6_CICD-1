#!/bin/bash

# TELEGRAM_BOT_TOKEN = '6036727773:AAFVnhvI-ySiDQRMj2lFF5AAB74OLfQXido'

URL="https://api.telegram.org/bot6036727773:AAFVnhvI-ySiDQRMj2lFF5AAB74OLfQXido/sendMessage"
TEXT="Deploy status: $1%0A%0AProject:+$2%0AURL:+$3/pipelines/$4/%0ABranch:+$5"

curl -s --max-time 30 -d "chat_id=457397290&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null

