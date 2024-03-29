# rpi_pico_fakefire

The electric fireplace project.

Main goal is to have this :
![alt text](/img/fire.png)

But with flickering, and sound, and little bonus like color control...
Idea came after landlord decided that we could not use our fireplace anymore, and didn't want to pay 400-500 bucks for an electric one.

## **How to ?**
The trick is to use foam (the kind you can find at reno store for filling cracks and holes) with lights, of course since just simple Christmas lights don't twinkle, we need to use a microcontroller with leds.

After several tests, I abandonned the idea of leds with PWM, for a led strip, much better, but the ws2812/ws2811 needs special timings.
Used ATtiny85 at the beginning since I had plenty, but the low-power 10MHz versions cannot manage the 800 or 400kHz ws2811 chips plus the calculation for the lights.

As I found, a raspberry pico is much better for the project, the PIOs can decipher IR reception without stopping the stream (a complete IR frame is around 40ms) , and I could write a PIO-assembly program to manage the lights within the main C file.
Could have gone with the rp2040 only, but for 4$...


## **What is there in the end ?**
Final board contains :
- a 12V / 5V converter, switching DC-DC
- a MOSFET to control 12V supply to the strip
- NAND gate for 3.3V to 5V conversion (could have done with diode)
- a DFPlayer for the sound
- a PAM8403 for amplification (not really necessary for one 4 Ohm speaker)
- TSOP1838B IR receiver
- a raspberry pico for all the logic
- a 4 Ohm speaker
- several old 5mm leds and through hole resistor for a retro look



## **Analysis for the signal controlling the ws2811 :**

![alt text](/img/analyze.jpg)

![alt text](/img/analyze2.jpg)

This gave me the occasion to create libraries for the IR receiver (TSOP1838B) and the ws2811.



## **The PCB :**
First prototype was on a... prototype board, but decided to go real PCB with Kicad and JLCPCB, result :

![alt text](/img/ff_pcb_3d.png)
PCB in 3D on Kicad




![alt text](/img/PCB_reception.jpeg)
PCB received




![alt text](/img/IMG_20230127_171639_069.jpg)
PCB almost fully populated


## **What now ?**
So far, project is continuing... There are issues on IR reception, probably using 3 resistors to decrease the voltage from 5V to 3.3 for GPIO was not a good idea.
Need to make some tests as I could not find the input impedance of the pico GPIO.

## **Pro/cons**

- I've put 16V capacitor for the 12V supply, it's bad, but it was what I had in my drawer
- Forgot to put a UART/serial port, quite a mess to debug even if I could use the SWD
- Didn't add filtering for the sound, not specialist in this, right now the cracking wood sound is more like frying oil.

## **Mapping buttons : **

on off (top)                    menu
BA45FF00                        B847FF00

Test            +               return
BB44FF00        BF40FF00        BC43FF00

<<              play            >>
F807FF00        EA15FF00        F609FF00

0               -               C
E916FF00        E619FF00        F20DFF00

1               2               3
F30CFF00        E718FF00        A15EFF00

4               5               6
F708FF00        E31CFF00        A55AFF00

7               8               9
BD42FF00        AD52FF00        B54AFF00
