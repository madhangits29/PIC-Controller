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

// Function prototype
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay(unsigned int);
void lcd_output(unsigned int);
void keyscan();
void init();
// Variable declaration
unsigned char c,d,value;
unsigned char array[30]={"SET SPD:    rpm"};
unsigned int i,j=0,d1,d2,d3,d4;
void main()
{
    init();
    while(1)
    {
        keyscan();
    }
}

//Function definition
void init()
{
    TRISC = 0x00; // Rc7-Rc0 set as output 0000 0000
    TRISD = 0x00; // RD7-RD0  set as output 0000 0000
    OPTION_REG &= 0x7F;  // to act as pull_up resistor
    TRISB=0xF0; // RB4-RB7 set as input for switch
    lcd_cmd(0x3F);
    delay(100);
    lcd_cmd(0x3F);
    delay(100);
    lcd_cmd(0x3F);
    delay(100);
    lcd_cmd(0x38); //  0011 1000   N-1(Rc3) for 16X2;
                      //  F=0(Rc2)for 5X7 dot
    delay(100);
    lcd_cmd(0x06); // Right Justification
    delay(100);
    lcd_cmd(0x0C); // Dispaly on the Cursor
    delay(100);
    lcd_cmd(0x01);
    delay(100); // clear screen
}

void lcd_data(unsigned char d) {
    PORTC |= 0x08; // RC3 =1
    PORTD = d; // DATA
    PORTC |= 0x01; // CLOCK ENABLE
    PORTC &= ~0x01; // CLOCLK DISABLE
    __delay_ms(100);
}

void lcd_cmd(unsigned char c) {
    PORTC &= 0XF7; // RC3 =0
    PORTD = c;
    PORTC |= 0x01; // CLOCK ENABLE
    PORTC &= ~0x01; // CLOCLK DISABLE
    __delay_ms(100);
}

void delay(unsigned int delaycount) {

    while (--delaycount);
}

void keyscan()
{
    value= PORTB & 0xF0;  //  to consider  last four bit as 1111 0000
    switch(value)
    {
        case 0xE0:
            lcd_cmd(0x80);  // for set spd
            for(i=0;i<8;i++)
            {
                lcd_data(array[i]);
            }
            
            lcd_cmd(0x8C);
            for(i=12;i<15;i++)   //  for rpm
            {
                lcd_data(array[i]);
            }
            lcd_cmd(0x88);
            lcd_output(j); // to set 0000
            break;
        case 0xD0:
            j++;
            lcd_cmd(0x88);
           
            if (j>5000)
            {
                j=5000;  // j cannot execced 5000
            }
             lcd_output(j);
            break;
        case 0xB0:
            j--;
            lcd_cmd(0x88);
            if(j<1)
            {
                j=1;   // if j<1 set as 1
            }
            lcd_output(j);
            
            break;
        case 0x70:
            lcd_cmd(0x88);
            j=0;
            lcd_output(j); // reset
            break;
    }
            
}

void lcd_output(unsigned int i)
{
    d4=(unsigned char)(i/1000);
    d3=(unsigned char)((i-(d4*1000))/100);
    d2=(unsigned char) ((i-(d4*1000)-(d3*100))/10);
    d1=(unsigned char) (i-(d4*1000)-(d3*100)-(d2*10));
    lcd_cmd(0x88);
    lcd_data(0x30+d4);
     lcd_cmd(0x89);
    lcd_data(0x30+d3);
     lcd_cmd(0x8A);
    lcd_data(0x30+d2);
     lcd_cmd(0x8B);
    lcd_data(0x30+d1);
}
