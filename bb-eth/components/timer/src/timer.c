#include <stdio.h>

#include <platsupport/timer.h>
#include <platsupport/plat/timer.h>
#include <sel4platsupport/plat/timer.h>
#include <sel4platsupport/timer.h>
#include <sel4utils/util.h>


#include <Timer.h>



pstimer_t *timer_drv = NULL;


volatile static uint64_t ticks = 0;
uint64_t period = 100000000;



void irq_callback(void *_ UNUSED)
{

timer_handle_irq(timer_drv, DMTIMER2_INTERRUPT);


ticks++;


if ( ( ticks % 10) == 0)
{
	Prod_Pinger_activator_emit();
}
if ( ( ticks % 20) == 0)
{
	Cons_PingMe_activator_emit();
}


    irq_reg_callback(irq_callback, NULL);
   }



void post_init (void)
{


timer_config_t config;

config.vaddr = (void*)reg;
config.irq = DMTIMER2_INTERRUPT;

timer_drv = ps_get_timer(DMTIMER2, &config);
assert(timer_drv);
    irq_reg_callback(irq_callback, NULL);

    timer_periodic(timer_drv, period);
	timer_start (timer_drv);
}

