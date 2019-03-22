#include "new.h"

static __IO uint32_t TimingDelay;

/*--------------------------------------------------------RUTIN DELAY-----------------------------------------------------------------------------*/
void t(__IO uint32_t nTime)
{ 
  for(int i=0; i<5; i++)
	  {
	  GPIO_ToggleBits(GPIOA, GPIO_Pin_1);
	  delay_ms(nTime);
    }

 }
