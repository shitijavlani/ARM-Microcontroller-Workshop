/*
 * main.c
 */


#include <stdint.h>
#include <inc\tm4c123gh6pm.h>


// Forward declaration of wait function.
static void wait (void);


int main()
{

    // Enable clock signal to GPIO Port F.
    SYSCTL_RCGCGPIO_R |= 0x20;

    // Set Direction of GPIO as output on PF1, PF2, PF3.
    GPIO_PORTF_DIR_R |= 0xE;

    // Enable digital function on PF1, PF2, PF3.
    GPIO_PORTF_DEN_R |= 0xE;

    // Loop Forever.
    while(1)
    {
        // Turn on Red LED.
        GPIO_PORTF_DATA_R = 0x02;
        wait();
        // Turn on Green LED.
        GPIO_PORTF_DATA_R = 0x04;
        wait();
        // Turn on Blue LED.
        GPIO_PORTF_DATA_R = 0x08;
        wait();
    }

}


static void wait (void)
{

    int32_t clockCounter = 0;
    while(clockCounter++ < 1000000);

}
