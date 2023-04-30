## Description

This is an educational project to help me get exposed to embedded systems and robotics. The idea here to take a well documented Arduino based project and port it to pure C. I am starting with ATmega uCs to better learn how the MPU-6050 IMU, the I2C and UART/USART protocols, and the AVR architecture before moving to something more production oriented like an ARM based STM32 board. 

Along the way, I am also getting exposed to the domain knowledge of how a basic flight controller might work, and will look to implement some more mathematically intensive concepts like Euler rotation angles/transforms and quarternions next.

## Attribution

This is a project purely for learning purposes, and I have made use of several resources to explore different approaches to the I2C and MPU6050 interfacing logic. Here is a list of the sources that I have referred to along the way: 
- http://www.brokking.net/ymfc-al_main.html
- https://github.com/YifanJiangPolyU/MPU6050/
- https://github.com/hexagon5un/AVR-Programming/tree/master/Chapter17_I2C
- https://github.com/MikhailZhyhariev/mpu6050/
- https://github.com/hollingerc/AVR/
- https://www.electronicwings.com/avr-atmega/atmega1632-i2c

A shoutout to Joop Brokking's YMFC project, a wonderful resource to learn more about how quadcopters work and how to build one yourself at home! 



