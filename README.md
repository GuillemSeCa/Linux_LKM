# Administration and System Design
## Practica 1 Fase 1

# Introduction

The objective of this project is to get a better knowledge on how the Linux kernel works and how driver is developed. A kernel is the core of the Linux OS that is in charge of the communication between the OS and the hardware or external devices of the computer (peripheries).

To make this project we have used the Raspberry Pi Zero using its pins (pins are identified as GPIO). On these pins we will have the buttons (4 buttons) and the LEDs (2 LEDs).

The operation expected when pressing a button is:
- Turn ON or OFF the LED.
- Execute a script for each press.

This buttons are identified as (A, B, C, D) and it's scripts as A.sh, B.sh, C.sh, D.sh.

<br>

# Installation
## Installation of the headers (IMPORTANT)
Installing the headers is a obligatory step. It's very straightforward by just running a command to get the package.
```
sudo apt install raspberrypi-kernel-headers
```

## Installation from the script (recommended)
In case you want to do the easy installation, you will have to download only the Installation script with the name ```Install.sh```. With that script all the process from the cloning to the installation is done by itself only having to run:
```
sh Install.sh
```

## Manual Installation from git repository
First you will have to clone this repository on your RaspberryPi.

There are two options when compiling using the Makefile (inside the code directory):
1. To clean the compilation (to compile a newer version with some changes for example) you will have to run the following command:

```
make clean
```
2. To compile the code you just have to do the following command:
```
make
```
3. Once we have the code compiled we have to insert it on the headers with this command:
```
sudo insmod LKM.ko
```
**At this stage the driver should work!**

4. To unistall the driver (for example if you want to put a newer version with some changes) you first have to remove the module using this command:
```
sudo rmmod LKM.ko
```

**NOW IT'S READY TO USE!**
<br>
<br>

# Uninstall of the module
To uninstall the module you just need to run the ```Unistall.sh``` script by running:
```
sh Unistall.sh
```
<br>

# Development Journal

## Burning Raspbian OS to the sd

Burning the RaspberryPi OS Lite on the sd card was one of the first tasks of the project. Doing some research, I found that there exists a software for Windows/Linux/Mac to burn the image directly and easy (Raspberry Imager).

## Headers installation

One of the first problems we have encountered during the development of this Module was getting the headers for the raspberry. This process took me about 2-3 hours getting information and where to get them from.

The first idea was to get them from the raspberry's Linux repository and install it from there but encountered many problems with the daemon that was being used to compile the headers. Another problem with that idea was that I was getting another version of the headers, as I didn't have much context on the importance of the version I searched a new way (hoping it was easier) of installing the headers.

Searching something new, I found a much easier way to install them:
```
sudo apt install raspberrypi-kernel-headers
```

## Module coding
Once we have the headers installed, I read diagonally the documentation provided and understood that the implementation was the easy part. Created 4 functions for the buttons (inputs) and mapping 2 LEDs (outputs). Took about 30 minutes, this part.

One of the last minute additions was the functionality that for each button press It would have to execute a given script. At first I thought this would be done with the execute() function from C, but later on I saw it wasn't working and I had to use the call_usermodehelper() to have the job done. To solve the 2nd and 3rd argument I had to search for some examples of the function being called and saw what was being expected there. I have to add that the official documentation for this function could be better explained, in particular this 2 arguments

## Debugging
To debug the system we used ```tail -f /var/log/kern.log``` to check all the printks were doing great and actuating when they were supposed to actuate. This was very useful to detect problems and debug unexpected behaviors.

<br>

# Conclusions
One of the things I have valued the most during the development of the project was how starting without knowing much I had to do the reasearch not only documentation of the kernel but examples... I think it not only improved my understanding on linux but also helped to do research of a new technology more efficient.

I also value the visibility of the code, if it works it should turn on the LED. This was a more phisical way of debugging at the start of the coding. The process of development has been very iterative (trying to turn on a led, making a led depend to a button, making a button execute the script...). This iterations helped get a better depth on the understanding of the kernel.

<br>

# Repository
This project can be found in GitHub:

https://github.com/GuillemSeCa/Linux_LKM

<br>

# Credits

Guillem Serra Cazorla (gserracazorla@gmail.com)

www.guillemserracazorla.com
<br>
---
**NOTE:**

All this project has been developed and tested under the RaspberryPi Zero on the Raspberry Pi OS Lite.

---


Corrected with https://www.corrector.co/