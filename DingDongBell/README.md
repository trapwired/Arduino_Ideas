# Bell - Bot: Explanation
The idea is simple, an Arduino is connected to the pins of a conventional Bbll and monitors its voltage. As soon as this voltage is over a certain threshold (= someone ringed the Bell), a message is sent via the Telegram bot API to notify me.

# Telegram - URL - Format
Telegram allows for simple http requests of the following form. I.E. to send MESSAGE (Spaces via + --> To send Hello World, MESSAGE would be Hello+World) to CHAT_ID via the bot with the following credentials BOT_CREDENTIALS (of the form bot123456789:Abcdefghijklmnopqrstuvwxyz):
https://api.telegram.org/BOT_CREDENTIALS/sendMessage?chat_id=CHAT_ID&text=MESSAGE  
SECRET_TELEGRAM_LINK_PARTIAL is just the above describe link without the first part (https://api.telegram.org)
