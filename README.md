# rpi_pico_fakefire

This is the electric fireplace project.

Main goal is to have this :
![alt text](/img/fire.png)

But with flickering, and sound, and little bonus like color control...
Idea came after landlord decided that we could not use our fireplace anymore, and didn't want to pay 400-500 bucks for an electric one.

The trick is to use foam (the kind you can find at reno store for filling cracks and holes) with lights, of course since just simple Christmas lights don't twinkle, I wanted to use a microcontroller with leds.

After several tests, I abandonned the leds for a led strip, better to handle... 
Used ATtiny85 at the beginning, but the 10MHz versions I have cannot manage the 800 or 400kHz ws2811 chips plus the calculation for the lights.

In the end, a raspberry pico is much better for the project, the PIOs can handle IR reception without stopping the stream of light, and I could write a program to manage the lights.
Could have gone with the rp2040 only, but for 4$...


Analysis for the signal controlling the ws2811 :

![alt text](/img/analyze.jpg)

![alt text](/img/analyze2.jpg)

This gave me the occasion to create libraries for the IR receiver (TSOP1838B) and the ws2811


First prototype was on a... prototype board, but decided to go real PCB with Kicad and JLCPCB, result :

![alt text](/img/ff_pcb_3d.png)
PCB in 3D on Kicad




![alt text](/img/PCB_reception.jpeg)
PCB received




![alt text](/img/IMG_20230127_171639_069.jpg)
PCB almost fully populated

So far, project is continuing... There are issues on IR reception, probably using 3 resistors to decrease the voltage from 5V to 3.3 for GPIO was not a good idea.
Need to make some tests as I could not find the input impedance of the pico GPIO.



Mapping buttons : 

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
