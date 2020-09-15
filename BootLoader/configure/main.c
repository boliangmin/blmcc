#include "sys.h"
#include "configure.h"
#include "delay.h"

int main(void)
{
	  u16 i= 0;
	  BoardInit();
	
	  while(1)
	  {
			  printf("hhhhhhh%d\r\n",i++);
				delay_ms(50);
	  }
}

