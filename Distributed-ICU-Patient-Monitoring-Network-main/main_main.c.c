#include <LPC21xx.h>
#include "header.h"
#include "max30102.h"
#include "spo2.h"
#include<stdio.h>
MAX30102_Data sensor;  //structure
CAN1 v1;
int main(void)
{
	
	u32 adcout0,adcout1;
	u8 adcout2;
	float vout1,v2,tempr,t2;
	 u8 print_count = 0;
	char s[60];
	/*init fun*/
	can1_init();
	adc_init();
    uart0_init(9600);
    i2c_init();
    delay_ms(100);
    uart0_tx_string("\r\n");
    uart0_tx_string("TEMP LDR & SpO2 TEST\r\n");
    MAX30102_Init();
    SpO2_Init();
	  //	v1.id=0x234;
	v1.rtr=0;//data-frame
	v1.dlc=4; //4byte
	v1.byteA=0;
	v1.byteB=0;
    while(1)
    {
        /* Read one sample */

        MAX30102_ReadFIFO(&sensor);
        SpO2_Process(sensor.red, sensor.ir);
        /* Print every 50 samples (~500ms at 100Hz) */
        print_count++;
        if(print_count >= 50)
        {
            print_count = 0;

            uart0_tx_string("----------------------\r\n");

            uart0_tx_string("RED=");

            uart0_integer(sensor.red);

           uart0_tx_string("\r\nIR=");

            uart0_integer(sensor.ir);

            uart0_tx_string("\r\nSpO2=");

            uart0_integer(Get_SpO2());

            uart0_tx_string("\r\n");

			adcout0=adc_read(0);//read Ain0 temp

		 adcout1=adc_read(1); //read Ain0 ldr

			 adcout0=adcout0&0x3ff;

			 adcout1=adcout1&0x3ff;

			   adcout2=Get_SpO2();

	v1.byteA=(adcout0|(adcout1<<10))|(adcout2<<20);
		
		sprintf(s,"adc=%d ldr=%d \r\n",adcout0,adcout1);

		uart0_tx_string(s);
		vout1=((float)adcout0*3.3)/1023;

		tempr=(vout1-0.5)/0.01;
		sprintf(s,"temp=%.2f   vout=%.2f\r\n",tempr,vout1);
		uart0_tx_string(s);
		v2=	(adcout1*3.3)/1023;
      t2=(v2/3.3)*100;
	sprintf(s,"LDR=%.2f   vout=%.2f\r\n",t2,v2);
	uart0_tx_string(s);
			can1_tx(v1);//send data-frame


        }	
        /* Keep sampling at ~100Hz */

        delay_ms(100);
    }
}
