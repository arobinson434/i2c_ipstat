# I2C IP Stat
WIP
A simple progam to read the IP of the host and display it on an SSD1306 OLED.
This is intended to run on a Raspberry Pi.

## Purpose
I want to do dev work on my Raspberry Pi Zero 2W by cross compiling on my Linux
box, and then copying the binaries to my pi via SCP. The pi is running Buildroot
and I don't have any HDMI drivers loaded, so I can only interact with it via
UART or SSH. I want to have it join my WiFi automatically, but I don't have an
easy way to know it's IP.

This project is intended bridge that need. It simply reads the IP of the pi from
`/proc/net/fib_trie` and displays it on the 
[Adafruits Pi OLED](https://www.adafruit.com/product/3527).

## Building
I am cross compiling this program to run in Buildroot, so my Makefile makes
certain assumptions about your setup.

First, I am assuming that you have sourced the `environment-setup` script from
Buildroot's `output/host/` directory.

Second, I am assuming that your current Buildroot SDK has the `BCM2835` hardware
driver installed. For what it's worth, at the time of writing this, Buildroot
only has v1.73 of the driver, but the `SSD1306` driver I am using says it needs
v1.74. I didn't even test v1.73, I just modified the Buildroot package to point
v1.74 and pulled it.

Lastly, I am assuming that you have the
[SSD1306 OLED RPI](https://github.com/gavinlyonsrepo/SSD1306_OLED_RPI) built,
and available up one directory, `../`. Building the driver took a little
Makefile tweaking but it wasn't too bad. I may upload a fork at some point.

As I said above, this is currently a work in progress. At some point, I may
(separately) upload my Buildroot configs and other tweaks.
