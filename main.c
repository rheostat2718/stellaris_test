#define PART_LM4F120H5QR



#include <stdio.h>
#include <stdlib.h>
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
	
void PutString(char *ptr);
void Put( char c);
void delay( unsigned int ms);

static char sout[100];

int main(void)
{

	SysCtlClockSet( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	unsigned int cs = SysCtlClockGet();
	GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);

//	GPIOPinConfigure(GPIO_PA0_U0RX);
//	GPIOPinConfigure(GPIO_PA1_U0TX);


	UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),115200,UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE);

	UARTEnable(UART0_BASE);
	unsigned int x;

	for(x=0;;++x)
	{
		ltoa( (long) x,sout);
		PutString(sout);
		Put(0x0d);
		Put(0x0a);
		delay(1);
	}

	return 0;
}



void PutString(char *ptr)
{
	while ( *ptr != '\0')
	{
		Put(*ptr);
		ptr++;
	}
}

void Put( char c)
{
	UARTCharPut(UART0_BASE,c);
}

void delay( unsigned int s)
{
	SysCtlDelay((SysCtlClockGet()*s)/3/10);
}
