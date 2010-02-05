#include <lpc17xx.h>
#include "type.h"

int main (void)
{	    		
	uint32_t i, j;

	SystemInit();
	GPIO2 -> FIODIR = 0x000000FF;		/* P2.xx defined as Outputs */
	GPIO2 -> FIOCLR = 0x000000FF;		/* turn off all the LEDs */


	while(1)
	{
		for(i = 0; i < 8; i++)
		{
			GPIO2 -> FIOSET = 1 << i;
			for(j = 1000000; j > 0; j--);
		}
		GPIO2 -> FIOCLR = 0x000000FF;
		for(j = 1000000; j > 0; j--);
	}
}





