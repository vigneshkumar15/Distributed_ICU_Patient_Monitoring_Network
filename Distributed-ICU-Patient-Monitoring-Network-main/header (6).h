#ifndef HEADER_H

#define HEADER_H




typedef unsigned int u32;

typedef signed int s32;


typedef unsigned char u8;

typedef signed char s8;


typedef unsigned short int u16;

typedef short int s16;




// LCD


extern void lcd_data(unsigned char data);

extern void lcd_cmd(unsigned char cmd);

extern void lcd_string(char *p);

extern void lcd_float(float f);

extern void lcd_integer(int num);




// UART


extern void uart0_init(unsigned int baud);

extern void uart0_tx(unsigned char data);

extern void uart0_tx_string(char *ptr);

extern void uart0_integer(int num);

extern void uart0_rx_string(unsigned char *ptr,int len);




// Delay


extern void delay_sec(unsigned int sec);

extern void delay_ms(unsigned int ms);

extern void delay_us(unsigned int us);




// I2C


extern void i2c_init(void);

extern void i2c_send(u8 sa,u8 mr,u8 data);

extern u8 i2c_read(u8 sa,u8 mr);

extern void i2c_read_buf(u8 sa,u8 mr,u8 *buf,u8 len);




// ADC

void adc_init(void);

u32 adc_read(u8 );
//CAN

typedef struct CAN1_MSG{

	u32 id;

	u32 byteA;

	u32 byteB;

	u8 rtr;

	u8 dlc;

	u8 ff;//ide

}CAN1;

extern void can1_rx(CAN1 *ptr);

extern void can1_tx(CAN1 v);

extern void can1_init(void);

#endif





