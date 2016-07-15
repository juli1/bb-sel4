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

#define CONFIG_SWITCH_EXIT_CMD             (2)

static volatile unsigned int flagIsr = 1;


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



unsigned int devmem;


void CPSWPinMuxSetup(void);
void CPSWClkEnable(void);
void EVMPortMIIModeSelect(void);
void EVMMACAddrGet(unsigned int addrIdx, unsigned char *macAddr);

static CPSW_PHY_PARAM_IF cpswPhyParam;
static CPSW_CONF_IF cpswConfig;


int run(void)
{

   unsigned int ipAddr;
   unsigned int initFlg = 1;
   LWIP_IF lwipIfPort1, lwipIfPort2;

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

   AintcCPSWIntrSetUp();
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
   httpd_init();

   cpswConfig.phy_param = &cpswPhyParam;

   /* Loop forever.  For Switch Condigraton and interrupt handlers. */
   while(1)
   {
      unsigned int switchConfig = 0;
      unsigned char switchConfigInputHelp[] = "):  ";

      if(initFlg)
      {
         printf("\n\r\n\r === CPSW Configurations === ");
         printf("\n\r\n\r === Available PHY Configurations ===");
         printf("\n\r\n\r1 - Configure Phy of a Port ");
         printf("\n\r\n\r2 - Exit ");
         initFlg = 0;
      }

      if (!initFlg)
      {
         printf("\n\r\n\r Select Switch Configuration (1 to %d",
               CONFIG_SWITCH_EXIT_CMD);

         switchConfig = UserValueInfoGet(1, CONFIG_SWITCH_EXIT_CMD, 0, FALSE,
               switchConfigInputHelp);

         printf("\n\r\n\rSwitch Configuration selected: %d\r\n",
               switchConfig);

         if(EnetLWIPSwitchConfiguration(switchConfig))
            initFlg = 1;
      }

      if(switchConfig == CONFIG_SWITCH_EXIT_CMD)
         break;
   }

   /* Loop forever.  All the work is done in interrupt handlers. */
   while(1)
   {
      ; /* Perform nothing */
   }

   return 0;
}


