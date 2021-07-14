from machine import Pin

hall_sense = Pin(26, Pin.IN, Pin.PULL_UP)

while True:
    print(hall_sense.value()
