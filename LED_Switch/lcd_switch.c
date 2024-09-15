
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000
int port_value=0;

void main()
{
    TRISB=0XF0;   //1111 0000 RB4-RC7 AS INPUT   RB0-RB3 AS OUTPUT
    TRISC=0X00;  // 0000 0000  ALL PORT SET AS OUTPUT
    PORTB=0X00;  // TO SET ALL  PORT AS 0
    
    while(1)
    {
        port_value=PORTB; // ACCORDING TO CHANGE IN THE PORTB IT DETERMINE CASE
       switch(port_value) 
       {
           case 0xE0 : PORTC =0x40;   //PORTB= 1110 0000  // RC6=1 RC1=0
           break;
             case 0xD0 : PORTC =0x42;   //PORTB= 1101 0000  // RC6=1 RC1=1
           break;
             case 0xB0 : PORTC =0x02;   //PORTB= 1011 0000  //RC6=0 RC1=1
           break;
             case 0x70 : PORTC =0x00;   //PORTB= 0110 0000  //RC6=0 RC1=0
           break;
           default: PORTC=0x00;         // if NO switch is pressesed
           break;
       }
    }
}



