Try to integrate the ethernet driver for the beagleboard into
seL4.

# TODO
 * introduce a delay service for the TCP stack
 * configure memory region to access (for example, for the buffer
   or for the timer (check DMTIMER7)
 * register the IRQ
 * check the code when it disables the IRQ. Might introduce
   a semaphore/mutex then.

