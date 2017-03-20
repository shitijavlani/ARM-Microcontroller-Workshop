/*
 * main.c
 */


#include <stdint.h>
#include <inc\tm4c123gh6pm.h>


volatile static uint16_t g_ui16ADCResult = 0;


int main()
{

    /***************** MODULE INITIALIZATION *****************/
    // This register provides software the capability to enable and disable the ADC modules in Run mode
    // The ADC module 1 is enabled by setting bit 1. ADC module 0 is enabled by setting bit 0.
    SYSCTL_RCGCADC_R |= 0x02; //Step 1

    // This register provides software the capability to enable and disable GPIO modules in Run Mode
    // Enable PortE (1<<4), will be used for pot: Enable PortF (1<<5), will be used for LED
    SYSCTL_RCGCGPIO_R |= 0x30; //Step 2

    // This register is the data direction register
    // We clear pin One in order to make it an input
    GPIO_PORTE_DIR_R &= ~0x02;

    /************************* LED *************************/
    // Enable digital functions for the corresponding pin
    GPIO_PORTF_DEN_R |= 0x02;
    // Disable alternate functions, we are using digital
    GPIO_PORTF_AFSEL_R |= 0x02;
    // Setting the pins makes them an output
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DATA_R |= 0x02;
    /*******************************************************/

    //Selects the alternate function, in this case analog
    GPIO_PORTE_AFSEL_R |= 0x02; //Step 3

    //Using analog => disable the digital function of that pin (I am using PE1 which corresponds to AIN2)
    GPIO_PORTE_DEN_R &= ~0x02; //Step 4

    //Analog function of the pin is enabled, the isolation is disabled, and the pin is capable of analog functions (pin PE1)
    GPIO_PORTE_AMSEL_R |= 0x2; //Step 5

    /****** Sample Sequencer Configuration ******/

    //Disable sample sequencer 3 (I used SS3 because SS3 allows us to sample from one pin)
    //Disabling the sequencer during programming prevents erroneous execution if a trigger event
    //were to occur during the configuration process.
    ADC1_ACTSS_R &= ~0x08; //Step 1

    //I am using SS3 whos bits start from 12->15, => I assigned 0xF<<12.
    // Always (countinuously sample)
    ADC1_EMUX_R = 0xF000; //Step 2

    //Select my analog input. I am using PE1 which corresponds to AIN2.
    ADC1_SSMUX3_R = 0x2; //Step 3

    //I set bit END0(bit 1), and bit IE0(bit 2) to be used for interrupts.
    ADC1_SSCTL3_R = 0x6; //Step 4

    //Interrupts are used, => I set bit 3 (SS3 Interrupt Mask).
    ADC1_IM_R = 0x08;//Step 5

    //Sample Sequencer 3 is enabled again.
    ADC1_ACTSS_R |= 0x08;//Step 6

    //This bit is cleared by writing a 1. Clearing this bit also clears the INR3 bit in the ADCRIS register.
    ADC1_ISC_R = 0x08;

    // Enable the interrupt in the NVIC.
    NVIC_EN1_R |= (1<<(INT_ADC1SS3-48));

    while(1)
    {
        if(g_ui16ADCResult > 2047)
            GPIO_PORTF_DATA_R |= (1<<1);
        else
            GPIO_PORTF_DATA_R &= ~(1<<1);
    }

}


void ADC1SS3_Handler (void)
{

    g_ui16ADCResult = ADC1_SSFIFO3_R;
    ADC1_ISC_R = (1<<3);

}
