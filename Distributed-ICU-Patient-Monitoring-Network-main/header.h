/*header.h*/


typedef unsigned char u8;

typedef signed char s8;

typedef unsigned int u32;

typedef signed int s32;




extern void delay_sec(unsigned int sec);

extern void delay_ms(unsigned int ms);

extern void lcd_data(unsigned char data);

extern void lcd_cmd(unsigned char cmd);

extern void lcd_init(void);

extern void lcd_string(char *ptr);

extern void lcd_integer(int num);


extern void uart0_init(unsigned int baud);

extern void uart0_tx(unsigned char data);

extern unsigned char uart0_rx(void);

extern void uart0_tx_string(char *ptr);

extern void uart0_binary(int num);

extern void uart0_integer(int num);

extern void uart0_hex(int num);


extern void spi0_init(void);

extern u8 spi0(u8 data);

extern u32 mcp3204_adc_read(u8 ch_num);


extern void i2c_init(void);

extern void i2c_send(u8, u8, u8);

extern u8 i2c_receive(u8 , u8);




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




