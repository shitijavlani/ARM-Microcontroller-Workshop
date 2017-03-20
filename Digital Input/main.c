/*
 * main.c
 */


#include <stdint.h>
#include <inc\tm4c123gh6pm.h>


int main()
{

    // Enable clock to GPIO PortF
    SYSCTL_RCGCGPIO_R |= 0x20;

    // Enables write access to the GPIOCR register.
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    // Commit register, reflects changes made to GPIOAFSEL, GPIOPUR, GPIOPDR, GPIODEN.
    GPIO_PORTF_CR_R = 0xff;
    // Configure direction of pin as input(0) or output(1).
    GPIO_PORTF_DIR_R |= 0x0E;
    // Enables weak pull-up resistors on the corresponding pins of the bits set.
    GPIO_PORTF_PUR_R |= 0x11;
    // Enable digital function.
    GPIO_PORTF_DEN_R |= 0x1F;

    // Execute this code forever.
    while(1)
    {
        // Check which switch is pressed.
        switch(GPIO_PORTF_DATA_R & 0x11)
        {
        case 0x00:
            // Turn on Red LED.
            GPIO_PORTF_DATA_R = 0x02;
            break;
        case 0x01:
            // Turn on Green LED.
            GPIO_PORTF_DATA_R = (1<<2);
            break;
        case 0x10:
            // Turn on Blue LED.
            GPIO_PORTF_DATA_R = (1<<3);
            break;
        default:
            // // Turn off all LEDs.
            GPIO_PORTF_DATA_R &= ~((1<<1) | (1<<2) | (1<<3));
            break;
        }
    }

}
