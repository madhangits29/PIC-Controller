
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
//----------RECEIVER SIDE
void slave_init();
unsigned char value;

void main()
{
    slave_init();
    while (1)
    {
        if (PIR1 & 0x20) //RB5 0010 0000 receiver buffer i full or not 1-full ,0-empty
        
    {    PORTD=0x00;
        value = RCREG;
        switch (value) 
        {

            case 'A':
                PORTD = 0X02; // RD1 AND RD4 OFF
                break;
            case 'B':
                PORTD = 0X10; // RD1 off AND RD4 on
                break;
            case 'C':
                PORTD = 0X12; // RD1 on RD4 On
                break;
            case 'D':
                PORTD = 0X00; // RD1 AND RD4 OFF
                break;
        }
         __delay_ms(100);
         
    }  
}
}
void slave_init() {

    TRISD = 0x00; // 0000 0000 portb as input
    TRISC = 0xC0; /// 1100 0000 enable the serial port
    RCSTA = 0x90; // 1001 0000 Enable the SPEN bit and CREN-continous receiver enable pin
    TXSTA = 0x20; // 0010 0000  enable the TXen pin
    SPBRG = 0x09; //   Baudrate 
    
}


