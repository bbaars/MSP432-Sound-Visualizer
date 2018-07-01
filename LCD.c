/*
 * LCD.c
 *
 *  Created on: Jul 1, 2018
 *      Author: brandon
 */

/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include "ST7735.h"

/******************************************************************************
 * This Function initializes MCLK to 48Mhz frequency for the LCD to Function
 *****************************************************************************/
void LCD_ClockInit48Mhz(void){

    /* configure pins for peripheral/crystal usage */
    MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
            GPIO_PIN3 + GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // Set Back light pin to Output
    P6->DIR |= BIT6;
    P6->OUT |= BIT6;

    /* enables external frequencies */
    MAP_CS_setExternalClockSourceFrequency(32000, 48000000);

    /* Starting HFXT in non-bypass mode without a timeout. Before we start
     * we have to change VCORE to 1 to support 48Mhz clock */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* false means there are no timeouts set, will return when stable */
    MAP_CS_startHFXT(false);

    /* initializing MCLK to HFXT (effectively to 48 MHz) */
    MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* intializing the SMLK to 12 MHz */
    MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_4);

    ST7735_InitR(INITR_REDTAB);

    ST7735_FillScreen(ST7735_WHITE); //white color

    ST7735_SetRotation(2);
}
