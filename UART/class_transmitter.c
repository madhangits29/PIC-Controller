
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
// FUNCTION PROTOTYPE
//---------------------------------MASTER SIDE
void master_init();

//FUNCTION VARIABLE
unsigned char value;


void main()
{
    master_init();
    while(1)
    {
        value=PORTB & 0xF0;
        switch(value)
        {
            case 0xE0:
                TXREG='A';  // loading the value in register
                break;
                case 0xD0:
                TXREG='B';  // loading the value in register
                break;
                case 0xB0:
                TXREG='C';  // loading the value in register
                break;
                case 0x70:
                TXREG='D';  // loading the value in register
                break;
                
        }
        __delay_ms(100); // switch debouncing
    }
}

void master_init()
{
    TRISB=0xF0; // 1111 0000 RB4-Rb7 port is input
    OPTION_REG=0x7F;  // enable pullup
    TRISC= 0xC0;   /// 1100 0000 enable the serial port
    RCSTA=0x90;  // 1001 0000 Enable the SPEN bit and CREN-continous receiver enable pin
    TXSTA= 0x20; // 0010 0000  enable the TXen pin
    SPBRG=0x09; //   Baudrate 
}

