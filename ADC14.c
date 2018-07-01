/*
 * ADC14.c
 *
 *  Created on: Jul 1, 2018
 *      Author: brandon
 */

/* DriverLib Includes */
#include "driverlib.h"
#include "msp.h"

#include "Variables.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

int counter = 0;

/*
 * Initializes the ADC Module
 */
void microPhoneADC14Init(void) {


    //enable ADC module
    MAP_ADC14_enableModule();

    //Setting clocksource to masterclock, with a predivider of 1 and divider of 4
    // MCLK/1/4
//    ADC14->CTL0 = (ADC14->CTL0
//                & ~(ADC14_CTL0_PDIV_MASK | ADC14_CTL0_DIV_MASK | ADC14_CTL0_SSEL_MASK))
//                | ADC_DIVIDER_3 | ADC_PREDIVIDER_4 | ADC_CLOCKSOURCE_MCLK;

    //takes 48Mhz down to 3Mhz
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_SMCLK, ADC_PREDIVIDER_32,
            ADC_DIVIDER_8, 0);

    // Configure the ADC Mem to use MEM0
    // Use single sample mode so that only a single ADC Channel will be stored at MEM0
    MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0,
                                        ADC_VREFPOS_AVCC_VREFNEG_VSS,
                                        ADC_INPUT_A13,
                                        false);

    //set pin (5.5 A0) as ADC input
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,
                                                   GPIO_PIN0,
                                                   GPIO_TERTIARY_MODULE_FUNCTION);
    MAP_ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);

    //enable ADC interrupt, specifically on channel 0
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_ADC14_enableInterrupt(ADC_INT0);

    MAP_ADC14_enableConversion();

    //toggle an ADC read/conversion
    MAP_ADC14_toggleConversionTrigger();

    //enable interrupts
    MAP_Interrupt_enableMaster();
}


/*
*   ADC IRQ. This is called whenever there is a conversion that is finished for ADC_MEM0.
*/
void ADC14_IRQHandler(void) {

    uint16_t status = MAP_ADC14_getEnabledInterruptStatus();

    MAP_ADC14_clearInterruptFlag(status);

    if (ADC_INT0 & status) {

        MAP_ADC14_toggleConversionTrigger();

        int result = MAP_ADC14_getResult(ADC_MEM0);

        float voltage = result * (5 / 16384.0);

        if (counter > 11) {
            counter = 0;
        }

        sounds[counter++] = voltage;
    }
}
