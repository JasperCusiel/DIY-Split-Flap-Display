from machine import Pin
import utime

pins = [
    Pin(6,Pin.OUT),
    Pin(7,Pin.OUT),
    Pin(8,Pin.OUT),
    Pin(9,Pin.OUT)
    ]

full_step_sequence = [
    [1,0,0,0],
    [0,1,0,0],
    [0,0,1,0],
    [0,0,0,1]]

while True:
    for step in full_step_sequence:
        for i in range(len(pins)):
            pins[i].value(step[i])
            utime.sleep(0.001)
