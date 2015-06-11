# Beagle OS

A microkernel and basic operating system that runs on BeagleBone Black hardware.
The kernel is loaded as a bare metal application via the boot loader and initializes
all the hardware components that it can use.

Eventually it will boot into a simple shell.

## Getting Started

You will need an ARM cross-compiler (GCC is the only supported compiler at the moment).
After that, basic makefile experience will get things built.

Then you will need to figure out the Uboot boot loader and how you want to load the
kernel. TFTP has been the easiest for us so far.

## Resources

[ARM Assembly Tutorial](http://www.davespace.co.uk/arm/introduction-to-arm/)

A copy of the ARM architecture reference manual is located in the resources directory of
this repository. You will also want a quick reference for the calling convention that the
compiler expects when you implement functions in assembly:

[ARM Embedded API Calling Conventions](http://stackoverflow.com/questions/261419/arm-to-c-calling-convention-registers-to-save)

[BeagleBone Black Tech Reference](http://www.ti.com/lit/ug/spruh73l/spruh73l.pdf)

There is a copy of the software reference manual for the BeagleBone in the resources
directory of this repository.

[Linker Script Tutorial](http://www.delorie.com/gnu/docs/binutils/ld_6.html)
[Das Uboot Bootloader](http://www.denx.de/wiki/U-Boot)
[BeagleBone Black Bare Metal Setup](http://www.cs.sfu.ca/CourseCentral/433/bfraser/other/BareMetalGuide.pdf)
