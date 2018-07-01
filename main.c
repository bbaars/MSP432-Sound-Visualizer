
/******************************************************************************
 * MSP432 Sound Visualizer
 *
 * Description: Using a microphone and the ST7735 LCD, a sound
 * visualizer was created with ADC14 samples. These samples were shown
 * in the form of a graphic equalizer on the LCD screen
 *
 * P1.5 ->  SPI_CLK
 * P1.6 ->  MOSI
 * P3.6 ->  TFT_RST
 * P5.0 ->  TFT_CS
 * P5.2 ->  TFT_DC
 * P6.6 ->  TFT_BACK_LIGHT
 *
 *
 * Author: Brandon Baars, Mike Ford, Jason Hunter
*******************************************************************************/
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* User Includes */
#include "ADC14.h"
#include "LCD.h"
#include "ST7735.h"
#include "Variables.h"

void static updateGraphicEqualizer(void);

int main(void) {

    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    LCD_ClockInit48Mhz();
    microPhoneADC14Init();

     while(1){
         updateGraphicEqualizer();
         Delay1ms(20);
     }
}

void static updateGraphicEqualizer(void) {

    uint16_t color = 0x0F0F;

    float zero = sounds[0];
    float one = sounds[1];
    float two = sounds[2];
    float three = sounds[3];
    float four = sounds[4];
    float five = sounds[5];
    float six = sounds[6];
    float seven = sounds[7];
    float eight = sounds[8];
    float nine = sounds[9];
    float ten = sounds[10];


    ST7735_FillRect(ST7735_TFTWIDTH - ST7735_TFTWIDTH / 10, 0, ST7735_TFTWIDTH / 10, (uint16_t) (ST7735_TFTHEIGHT * (zero / 5)), color);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 2), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (one / 5)), color << 1);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 3), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (two / 5)), color << 2);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 4), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (three / 5)), color << 3);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 5), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (four / 5)), color >> 1);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 6), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (five / 5)), color >> 5);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 7), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (six / 5)), color >>5);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 8), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (seven / 5)), color << 1);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 9), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (eight / 5)), color >> 1);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 10), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (nine / 5)), color << 2);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 11), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (ten / 5)), color << 2);


    ST7735_FillRect(ST7735_TFTWIDTH - ST7735_TFTWIDTH / 10, 0, ST7735_TFTWIDTH / 10, (uint16_t) (ST7735_TFTHEIGHT * (zero / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 2), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (one / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 3), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (two / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 4), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (three / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 5), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (four / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 6), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (five / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 7), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (six / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 8), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (seven / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 9), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (eight / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 10), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (nine / 5)), ST7735_WHITE);
    ST7735_FillRect(ST7735_TFTWIDTH - ((ST7735_TFTWIDTH / 10) * 11), 0, ST7735_TFTWIDTH / 10, (ST7735_TFTHEIGHT * (ten / 5)), ST7735_WHITE);


}

