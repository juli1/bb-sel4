#include <camkes.h>

#include <generatedtypes.h>
#include <stdio.h>
#include <string.h>

#include "locator.h"
//#include "httpd.h"
#include "lwiplib.h"
#include "lwipopts.h"

#include "soc_AM335x.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "hw_cm_per.h"
#include "hw_cm_dpll.h"
#include "dmtimer.h"


unsigned int dmtimer7_mem;
unsigned int prcm_mem;
unsigned int control_mem;

unsigned int ss_mem;
unsigned int mdio_mem;
unsigned int wr_mem;
unsigned int cpdma_mem;
unsigned int ale_mem;
unsigned int cppi_ram_mem;
unsigned int port0_mem;
unsigned int port1_mem;
unsigned int silver1_mem;
unsigned int port2_mem;
unsigned int silver2_mem;



#define CONFIG_SWITCH_EXIT_CMD             (2)

static volatile unsigned int flagIsr = 1;

static void CPSWCore0RxIsr(void)
{
    lwIPRxIntHandler(0);
}

/*
** Interrupt Handler for Core 0 Transmit interrupt
*/
static void CPSWCore0TxIsr(void)
{
    lwIPTxIntHandler(0);
}

void DMTimer7ModuleClkConfig(void)
{
    HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) =
                             CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) &
     CM_PER_L3S_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) =
                             CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) &
     CM_PER_L3_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) =
                             CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) &
                               CM_PER_L3_INSTR_CLKCTRL_MODULEMODE) !=
                                   CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) =
                             CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) &
        CM_PER_L3_CLKCTRL_MODULEMODE) != CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE);

    HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) =
                             CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
                              CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL) !=
                                CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) =
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP;

    while((HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) &
                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL) !=
                               CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP);

    HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKCTRL) =
                             CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE;

    while((HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKCTRL) &
      CM_PER_L4LS_CLKCTRL_MODULEMODE) != CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE);

    /* Select the clock source for the Timer7 instance. */
    HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER7_CLK) &=
          ~(CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL);

    HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER7_CLK) |=
          CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL_CLK_M_OSC;

    while((HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER7_CLK) &
           CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL) !=
           CM_DPLL_CLKSEL_TIMER7_CLK_CLKSEL_CLK_M_OSC);

    HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) |=
                             CM_PER_TIMER7_CLKCTRL_MODULEMODE_ENABLE;
    while((HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) &
     CM_PER_TIMER7_CLKCTRL_MODULEMODE) != CM_PER_TIMER7_CLKCTRL_MODULEMODE_ENABLE);

    while((HWREG(SOC_CM_PER_REGS + CM_PER_TIMER7_CLKCTRL) & 
     CM_PER_TIMER7_CLKCTRL_IDLEST) != CM_PER_TIMER7_CLKCTRL_IDLEST_FUNC);

    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) &
            CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));

    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) &
            CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));

    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
           (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK |
            CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));

    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) &
           (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK |
            CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER7_GCLK)));
}

static void DMTimerIsr(void)
{
    /* Clear the status of the interrupt flags */

    DMTimerIntStatusClear(SOC_DMTIMER_7_REGS, DMTIMER_INT_OVF_EN_FLAG);

    DMTimerDisable(SOC_DMTIMER_7_REGS);

    flagIsr = TRUE;
}

unsigned int DMTimerWritePostedStatusGet(unsigned int baseAdd)
{
    /* Return the status of TWPS register */
    return (HWREG(baseAdd + DMTIMER_TWPS));
}


#define DMTimerWaitForWrite(reg, baseAdd)   \
            if(HWREG(baseAdd + DMTIMER_TSICR) & DMTIMER_TSICR_POSTED)\
            while((reg & DMTimerWritePostedStatusGet(baseAdd)));



void DMTimerModeConfigure(unsigned int baseAdd, unsigned int timerMode)
{
    /* Wait for previous write to complete */
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, baseAdd);

    /* Clear the AR and CE field of TCLR */
    HWREG(baseAdd + DMTIMER_TCLR) &= ~(DMTIMER_TCLR_AR | DMTIMER_TCLR_CE);

    /* Wait for previous write to complete */
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, baseAdd);

    /* Set the timer mode in TCLR register */
    HWREG(baseAdd + DMTIMER_TCLR) |= (timerMode & (DMTIMER_TCLR_AR | 
                                                   DMTIMER_TCLR_CE));
}



void DelayTimerSetup(void)
{   

#ifdef DELAY_USE_INTERRUPTS
    /* This function will enable clocks for the DMTimer7 instance */
    DMTimer7ModuleClkConfig();

    /* Registering DMTimerIsr */
    IntRegister(SYS_INT_TINT7, DMTimerIsr);

    /* Set the priority */
    IntPrioritySet(SYS_INT_TINT7, 0, AINTC_HOSTINT_ROUTE_IRQ);

    /* Enable the system interrupt */
    IntSystemEnable(SYS_INT_TINT7);

    DMTimerCounterSet(SOC_DMTIMER_7_REGS, 0);

    /* Configure the DMTimer for Auto-reload and compare mode */
    DMTimerModeConfigure(SOC_DMTIMER_7_REGS, DMTIMER_ONESHOT_NOCMP_ENABLE);
#else
    DMTimer7ModuleClkConfig();

    DMTimerModeConfigure(SOC_DMTIMER_7_REGS, DMTIMER_ONESHOT_NOCMP_ENABLE);
#endif

}

//static void AintcCPSWIntrSetUp(void)
//{
//    /* Enable IRQ for ARM (in CPSR)*/
//    IntMasterIRQEnable();
//
//    IntAINTCInit();
//    
//    /* Register the Receive ISR for Core 0 */
//    IntRegister(SYS_INT_3PGSWRXINT0, CPSWCore0RxIsr);
  
    /* Register the Transmit ISR for Core 0 */
//    IntRegister(SYS_INT_3PGSWTXINT0, CPSWCore0TxIsr);
    
    /* Set the priority */
//    IntPrioritySet(SYS_INT_3PGSWTXINT0, 0, AINTC_HOSTINT_ROUTE_IRQ);
//    IntPrioritySet(SYS_INT_3PGSWRXINT0, 0, AINTC_HOSTINT_ROUTE_IRQ);

    /* Enable the system interrupt */
//    IntSystemEnable(SYS_INT_3PGSWTXINT0);
//    IntSystemEnable(SYS_INT_3PGSWRXINT0);
//}


static void IpAddrDisplay(unsigned int ipAddr) 
{
    printf ("%d.%d.%d.%d", (ipAddr & 0xFF), ((ipAddr >> 8) & 0xFF),
                       ((ipAddr >> 16) & 0xFF), ((ipAddr >> 24) & 0xFF));
}



unsigned int devmem;


void CPSWPinMuxSetup(void);
void CPSWClkEnable(void);
void EVMPortMIIModeSelect(void);
void EVMMACAddrGet(unsigned int addrIdx, unsigned char *macAddr);

static CPSW_PHY_PARAM_IF cpswPhyParam;
static CPSW_CONF_IF cpswConfig;

void delay(unsigned int milliSec)
{
printf("Need to implement delay function\n");
}



int run(void)
{

   unsigned int ipAddr;
   unsigned int initFlg = 1;
   LWIP_IF lwipIfPort1, lwipIfPort2;

   dmtimer7_mem = (unsigned int) timer7reg;
   prcm_mem = (unsigned int) prcm_reg;
   control_mem = (unsigned int) control_reg;

ss_mem = (unsigned int) ss_reg;
mdio_mem = (unsigned int) mdio_reg;
cppi_ram_mem = (unsigned int) cppi_ram_reg;

wr_mem = (unsigned int) mdio_mem + 0x200;;

cpdma_mem = (unsigned int) ss_mem + 0x800;
ale_mem = (unsigned int) ss_mem + 0xD00;
port0_mem = (unsigned int) ss_mem + 0x100;
port1_mem = (unsigned int) ss_mem + 0x200;
silver1_mem = (unsigned int) ss_mem + 0xD80;
port2_mem = (unsigned int) ss_mem + 0x300;
silver2_mem = (unsigned int) ss_mem + 0xDC0;


/*
wr_mem = (unsigned int) wr_reg;
cpdma_mem = (unsigned int) cpdma_reg;
ale_mem = (unsigned int) ale_reg;
port0_mem = (unsigned int) port0_reg;
port1_mem = (unsigned int) port1_reg;
silver1_mem = (unsigned int) silver1_reg;
port2_mem = (unsigned int) port2_reg;
silver2_mem = (unsigned int) silver2_reg;
*/



#ifdef LWIP_CACHE_ENABLED
//   CacheEnable(CACHE_ALL);
#endif

//   CPSWPinMuxSetup();
   CPSWClkEnable();

   /* Chip configuration RGMII selection */
   EVMPortMIIModeSelect();

   /* Get the MAC address */
   EVMMACAddrGet(0, lwipIfPort1.macArray); 
   EVMMACAddrGet(1, lwipIfPort2.macArray); 

printf ("MACADDR1 %x:%x:%x:%x:%x:%x\n", lwipIfPort1.macArray[0], lwipIfPort1.macArray[1], lwipIfPort1.macArray[2], lwipIfPort1.macArray[3], lwipIfPort1.macArray[4] , lwipIfPort1.macArray[5]);
printf ("MACADDR1 %x:%x:%x:%x:%x:%x\n", lwipIfPort2.macArray[0], lwipIfPort2.macArray[1], lwipIfPort2.macArray[2], lwipIfPort2.macArray[3], lwipIfPort2.macArray[4] , lwipIfPort2.macArray[5]);

   // FIXME: look at this function and setup correctly the IRQ
   //AintcCPSWIntrSetUp();
   DelayTimerSetup();

   printf ("\n\rStarterWare Ethernet Application. Access the"
         " embedded web page using http://<ip address assigned>/index.html"
         " via a web browser. \n\r\n\r");

   printf ("Acquiring IP Address for Port 1... \n\r" );

#if STATIC_IP_ADDRESS_PORT1

   lwipIfPort1.instNum = 0;
   lwipIfPort1.slvPortNum = 1; 
   lwipIfPort1.ipAddr = STATIC_IP_ADDRESS_PORT1; 
   lwipIfPort1.netMask = 0; 
   lwipIfPort1.gwAddr = 0; 
   lwipIfPort1.ipMode = IPADDR_USE_STATIC; 

   ipAddr = lwIPInit(&lwipIfPort1);

#else

   lwipIfPort1.instNum = 0;
   lwipIfPort1.slvPortNum = 1; 
   lwipIfPort1.ipAddr = 0; 
   lwipIfPort1.netMask = 0; 
   lwipIfPort1.gwAddr = 0; 
   lwipIfPort1.ipMode = IPADDR_USE_DHCP; 

   ipAddr = lwIPInit(&lwipIfPort1);

#endif
   if(ipAddr)
   {
      printf ("\n\r\n\rPort 1 IP Address Assigned: ");
      IpAddrDisplay(ipAddr);
   }
   else
   {
      printf("\n\r\n\rPort 1 IP Address Acquisition Failed.");
   }

   /* Initialize the sample httpd server. */
//   httpd_init();


   /* Loop forever.  All the work is done in interrupt handlers. */
   while(1)
   {
      ; /* Perform nothing */
   }

   return 0;
}


