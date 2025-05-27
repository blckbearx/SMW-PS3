![logo](https://github.com/user-attachments/assets/2ad2defc-d816-4432-9e5f-813fcccb2154)

# Super Mario War PS3 [![Releases](https://img.shields.io/github/release/blckbearx/SMW-ps3)](https://github.com/blckbearx/SMW-ps3/releases/latest)

Super Mario War game for the PS3.

[The original port by lachrymose can be found here.](https://archive.org/details/super-mario-war-r-2-original)

## Repo explanation

### Folders
* 'include' and 'source': Source code files. Mostly .cpp and .h files.
* 'pkgfiles': Files that are added to the final package when compiling with 'make pkg' command. Contains game data and assets.
### Files:
* ICON0.PNG: The game's icon. Seen in the PS3's XMB when installed.
* Makefile: Stores all compiling settings and some final package info.
* SDL Inputs.txt: Info on how the code sees each input.
* sfo.xml: Aditional final package info. I use it to easily update the game version string.

## Building

What you'll need:

* The [PS3 Toolchain](https://github.com/ps3dev/ps3toolchain) compiled for your OS.
* Optional: xmlstarlet in order to correctly print the version number on the final package file name.

Just cd into where you cloned the repo and run ```make pkg``` to build a PKG file for installing.

Optionally, you can run ```make npdrm``` (or ```make run``` if you have PS3Load set up) if you want to test the binaries (you need to have the game assets either in its install folder inside the PS3 HDD (/dev_hdd0/game/SMW00PS33/USRDIR/smw) or in a USB drive (/dev_usb00x/smw, x being the number of the USB port you plugged the drive in)).

## Installing on PS3

Just download the PKG file from the releases page and install on the PS3 via Package Manager.
