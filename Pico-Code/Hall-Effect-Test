from machine import Pin, ADC
import utime
 
analog_value = ADC(26)
led = Pin(25, Pin.OUT)

pins = [
    Pin(6,Pin.OUT),
    Pin(7,Pin.OUT),
    Pin(8,Pin.OUT),
    Pin(9,Pin.OUT)
    ]
pin1 = Pin(6, Pin.OUT)
pin2 = Pin(7, Pin.OUT)
pin3 = Pin(8, Pin.OUT)
pin4 = Pin(9, Pin.OUT)

full_step_sequence = [
    [1,0,0,0],
    [0,1,0,0],
    [0,0,1,0],
    [0,0,0,1]]
 
while True:
    reading = analog_value.read_u16()     
    print("ADC: ",reading)
    if reading < 18000:
        led.value(1)
        pin1.value(0)
        pin2.value(0)
        pin3.value(0)
        pin4.value(0)
        break
    else:
        led.value(0)
        for step in full_step_sequence:
            for i in range(len(pins)):
                pins[i].value(step[i])
                utime.sleep(0.001)
