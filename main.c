/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

/***********************************************************
Creates an integer variable called ui8PinData and
initializes it to 2. This will be used to cycle through the three LEDs, lighting them one at
a time. Note that the C99 type is an 8-bit unsigned integer and that the variable name
reflects this.
************************************************************/
int ui8PinData=6;

/*****************************************************************************
Main function performs init and manages system.

Called automatically after the system and compiler pre-init sequences.
*****************************************************************************/
int main(void)
{
	//To set the clock frequency to be 40MHz.
	SysCtlClockSet(SYSCTL_SYSDIV_16|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	//Enable GPIO peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	//create a while(1) loop to send a “1” and “0” to the selected GPIO pin, with an
	//equal delay between the two.
	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2| GPIO_PIN_3, ui8PinData);
		SysCtlDelay(2000000);
		GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0x00);
		SysCtlDelay(2000000);
		if(ui8PinData==6) {ui8PinData=10;} else if (ui8PinData==10) {ui8PinData=12;} else {ui8PinData=ui8PinData/2;}
	}
}
