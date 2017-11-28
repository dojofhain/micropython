from microbit import *

rgb_led.set(red=100)
sleep(1000)
rgb_led.set(green=100)
sleep(1000)
rgb_led.set(blue=100)
sleep(1000)
rgb_led.set(red=100, green=100, blue=100)
sleep(1000)
rgb_led.set()
sleep(1000)

for i in range(255):
    rgb_led.set(red=i)
    sleep(10)

colors = [255, 0, 0]
for dec in range(3):
    inc = (dec + 1) % 3

    for i in range(255):
        rgb_led.set(red=colors[0], green=colors[1], blue=colors[2])
        colors[inc] += 1
        colors[dec] -= 1
        sleep(10)

for i in range(5):
    rgb_led.off()
    sleep(500)
    rgb_led.on()
    sleep(500)

for i in reversed(range(255)):
    rgb_led.set(red=i)
    sleep(10)
