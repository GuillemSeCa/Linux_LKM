# Administration and System Design
## Practica 1 Fase 1

# Installation from script
In case you want to do the easy installation, you will have to download only the Installation script with the name ```Install.sh```. With that script all the process from the cloning to the installation is done by itself only having to run:
```
sh Install.sh
```
<br>

# Manual Installation from git repository
First you will have to clone this repository on your RaspberryPi. Then you will have to enter and do a ```make``` that will compile all you need to add this module. Once it finishes, you will just have to do ```sudo insmod LKM.ko``` to install it. 

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

Once we have the headers installed, I read diagonally the documentation provided and understood that the implementation was the easy part. Created 4 functions for the buttons (inputs) and mapping 2 LEDs (outputs). Took about 30 minutes, this part. 

To debug the system we used ```tail -f /var/log/kern.log``` to check all the printks were doing great and actuating when they were supposed to actuate. This was very useful to detect problems and debug unexpected behaviors.


<br>

# Credits
Guillem Serra Cazorla (gserracazorla@gmail.com)

www.guillemserracazorla.com
<br>
---
**NOTE:**

All this project has been developed and tested under the RaspberryPi Zero on the Raspberry Pi OS Lite.

---
