![SMW Banner](http://smw.supersanctuary.net/site/logo.png)

# Super Mario War PS3 [![Releases](https://img.shields.io/github/release/blckbearx/SMW-ps3)](https://github.com/blckbearx/SMW-ps3/releases/latest)

Super Mario War game for the PS3.

[The original port by lachrymose can be found here.](https://gamebrew.org/images/1/18/SuperMarioWar_R2.zip)

## Repo explanation

### Folders
* 'include' and 'source': Source code files. Mostly .cpp and .h files.
* 'pkgfiles': Files that are added to the final package when compiling with 'make pkg' command. Contains game data and assets.
### Files:
* ICON0.PNG: The game's icon. Seen in the PS3's XMB when installed.
* Make_X.bat: Used for compiling without using the command line.
  * EBOOT.BIN: Compiles the executable that goes inside the final package.
  * PKG: Compiles and packages the game for installing on the console.
  * SELF: Compiles a signed executable that can be run 'externally'.
  * clean: Cleans previous compiled code. Used for re-compiling when code is changed.
* Makefile: Stores all compiling settings and some final package info.
* SDL Inputs.txt: Info on how the code sees each input.
* sfo.xml: Aditional final package info. Used for changing game version.

## Prerequisites for compiling

What you'll need:

* The [PS3 Toolchain](https://github.com/ps3dev/ps3toolchain) compiled for your OS.
* In case you're using the pre-compiled PSDK3v2 on Windows you'll also need libvorbis (provided as a zip in this repo, open the zip file and extract the folder next to the PSDK3v2 folder to merge them) The game won't have music though.

## Installing on PS3

Just download the PKG file and install on the PS3 via Package Manager.
