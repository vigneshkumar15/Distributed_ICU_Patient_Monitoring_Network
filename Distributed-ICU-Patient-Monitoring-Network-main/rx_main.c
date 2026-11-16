#include "header.h"
#include<stdio.h>

CAN1 r1;

int main(){

	u32 adcout0,adcout1;
	u8 adcout2;
	float temp,vout,v2,t2;
	char s[50];
	can1_init();

	uart0_init(9600);

	uart0_tx_string("nodeB\r\n");

	while(1){

		can1_rx(&r1);//receive data/remote frame

		if(r1.rtr==0)

			{
			//uart0_tx_string("data-frame received\r\n");
			adcout0=(r1.byteA&0x3ff);
			 adcout1=((r1.byteA>>10)&0x3ff);
			 adcout2=((r1.byteA>>20)&0xff);
			 uart0_tx_string("\r\n-----------------------------\r\n");
             uart0_tx_string("TEMP LDR & SpO2 TEST\r\n");
			 sprintf(s,"value =  %d %d %d\r\n",adcout0,adcout1,adcout2);
			 uart0_tx_string("\r\n-----------------------------\r\n");
			 uart0_tx_string(s);
			  vout=(adcout0*3.3)/1023;
			  temp=(vout-0.5)/0.01;
			 sprintf(s,"temparature=%.2f ^c\r\n",temp);
			  uart0_tx_string(s);
			  v2=	(adcout1*3.3)/1023;
              t2=(v2/3.3)*100;
       	      sprintf(s,"LDR=%.2f   vout=%.2f\r\n",t2,v2);
            	uart0_tx_string(s);
			   sprintf(s,"spo2=%d %%\r\n",adcout2);
            	uart0_tx_string(s);

		//sprintf(s,"value =  %d\r\n",adcout0);
			 // uart0_tx_string(s);
			}

		else 

			uart0_tx_string("remote-frame received\r\n");

	}

}

