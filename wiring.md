## LCD Connections:
>rs = 2
>en = 3
>d4 = 4
>d5 = 5
>d6 = 6
>d7 = 7

## Buttons:
>Set Alarm/View Alarm = 8
>Set Minute (increments by one everytime the button is pressed) = 10
>Set Hours (increments by one everytime the button is pressed) = 9
>Exit Button = 11

## DHT11 Sensor:
>output = 12

#DS3231 RTC:
>SCL of DS3231 = A5 of Arduino
>SDA of DS3231 = A4 of Arduino

## Buzzer/led for the alarm:
>output = 13

## IMPORTANT:
'''
Apart from this, 
You also need to connect appropriate resistors
with all the push buttons (10K resistors), as you have to do with any arduino board.
'''

Also,
you need to manually adjust/programmatically adjust brightness/contrast of your LCD
## Normal LCD module
>manual when you have a simple LCD, with no other board
## I2C LCD module
>programatically when you have an LCD with I2c interface
>In that case, you only get two wires SCL and SDA for the LCD, the code has to be modified a little
>Also you have to import the necessary  I2C LCD library