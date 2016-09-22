Try to integrate the ethernet driver for the beagleboard into
seL4.

# Installation
This code works with seL4/CAmkES. The driver is integrated into a CAmkES
component. All the driver code is in ConsumerThreadImpl component.

To install CAmkES, check this out:
http://sel4.systems/Info/CAmkES/GettingStarted.pml

Once you have a CAmkES environment.
 * Patch the kernel with kernel-patch.diff The kernel is in the
   kernel/ directory
 * Link or copy the bb-eth into the apps/ directory
 * In Kconfig , under the application section, add the following line
       source "apps/bb-eth/Kconfig"
 * run make menuconfig and select the bb-eth application. Make sure
   you are using the am335x target
 * compile
 * try to run

If you are experiencing any troubleshooting when compiling or running,
you can read 
http://julien.gunnm.org/geek/sel4/beaglebone%20black/2016/06/15/beaglebone-black-sel4-uart1/
it explains how to compile, execute and run an seL4 app on the beaglebone


# Todo
 * check the code when it disables the IRQ. Might introduce
   a semaphore/mutex then.

# Done
 * introduce a delay service for the TCP stack
 * configure memory region to access (for example, for the buffer
   or for the timer (check DMTIMER7)
 * register the IRQ
