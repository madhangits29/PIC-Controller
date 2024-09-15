
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

unsigned char val;

void main()
{
    TRISB = 0xF0;  // 1111 0000  Input mode
    PORTB=0x00;
    TRISC =0x00;
    PORTC=0x00;
    OPTION_REG &=0x7E ;
    // INTCON &=0xF0; 
    INTCON |= 0x88 ;    // 1000 1000  Global Intrupt , RBIE enable
    TRISD =0x00;
    PORTD =0x00;
    
            // THread MODe
    while(1)
    {
           PORTC= 0xFF; // all  port
           __delay_ms(100);
           PORTC=0x00;
           __delay_ms(100);
    }
    
}
  // HANDLER MODE
void __interrupt() ISR()
{
    if(INTCON &0x01)
    {
        
        val=PORTB;
        if(PORTB==0XE0)
        {
            PORTD=0xFF; 
            __delay_ms(1000);
            PORTD=0x00;
            __delay_ms(1000);
        }     
             
   INTCON &= 0xFE;  // clearing Intrupt
}
}





