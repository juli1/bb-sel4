#include <camkes.h>

#include <generatedtypes.h>
#include <stdio.h>
#include <string.h>

#include "locator.h"
//#include "httpd.h"
#include "lwiplib.h"
//#include "lwipopts.h"




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
//   LWIP_IF lwipIfPort1, lwipIfPort2;

#ifdef LWIP_CACHE_ENABLED
   CacheEnable(CACHE_ALL);
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
         pintf("\n\r\n\r1 - Configure Phy of a Port ");
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


