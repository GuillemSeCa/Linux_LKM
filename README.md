# Administration and System Design
## Practica 1 Fase 1

# Installation from script
In case you wanna do the easy installation you will have to download only the Installation script with the name ```Install.sh```. With that script all the process from the clonning to the installation is done by itself only having to run:
```
sh Install.sh
```
<br>

# Manual Installation from git repository
First of all you will have to clone this repository on your RaspberryPi. Then you will have to enter and do a ```make``` that will compile all you need to add this module. Once it finishes you will just have to do ```sudo insmod LKM.ko``` to install it. 

**NOW IT'S READY TO USE!**
<br>
<br>

# Unistall of the module
To unistall the module you just need to run the ```Unistall.sh``` script by running:
```
sh Unistall.sh
```
<br>

# Development Journal
One of the first problems we have encountered during the development of this Module was getting the headers for the raspberry. This process took me about 2-3 hours getting information and where to get them from.

The first idea was to get them from the raspberry's linux repository and install it from there but encountered many problems with the deamon that was being used to compile the headers. Annother problem with that idea was that I was getting annother version of the headers, as I didn't have much context on the importance of the version I searched a new way (hoping it was easier) of installing the headers. 

Searching something new I found a much easyier way to install them:
```
sudo apt install raspberrypi-kernel-headers
```

Once we have the headers installed I read diagonally the documentation provided and understood that the implementation was the easy part. Created 4 functions for the buttons (inputs) and mapping 2 LEDs (outputs). Took about 30 minutes this part. 




<br>

# Credits
Guillem Serra Cazorla (gserracazorla@gmail.com)

www.guillemserracazorla.com
<br>
---
**NOTE:**

All this project has been developed and tested under the RaspberryPi Zero.

---
