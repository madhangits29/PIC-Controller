

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

//define prototype
void init();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_output(unsigned int);
// declaring variables
unsigned char c,d,n,j,store[10];
unsigned long value,voltage;
unsigned int  low, high,val;

void main()
{
    init();
    while(1)
    {
        ADCON0=0x81;   // 1000  0001
        ADCON0 |= 0x04; // 0000 0100   we switched on the ADC on process button  
        while(ADCON0 & 0X04);   // if the ADCON again back to RC2 =0 the process completed
        low=ADRESL;  //  storing the adc value
        high=ADRESH;
        value=((unsigned int)high<< 8) + (unsigned int)low;
        voltage =(value *48 )/1023 ;  // calbiration with in 48
        lcd_cmd(0x80);
        lcd_output(voltage);
        __delay_ms(1000);
    }
        
}

void init()
{
    TRISD=0x00;   //  for lcd connection
    TRISC=0x00;    //  for enable and disable and selection
    TRISA=0x01;    //  creating one RA1 has Input to get data   0000 0001
    ADCON0=0x81;  //   1000 0001   Bit 1-for adc on ,Bit 6-7 for clock frequancy
    ADCON1=0x80;  //   Bit -0-3 for channel selection   bit 7 for left or right justification
    
   lcd_cmd(0x3F);
   __delay_ms(100);
      lcd_cmd(0x3F);
      __delay_ms(100);
      lcd_cmd(0x3F);
     __delay_ms(100);
      lcd_cmd(0x38); //  0011 1000   N-1(Rc3) for 16X2;
     __delay_ms(100);
    lcd_cmd(0x06); // Right Justification
      __delay_ms(100);
    lcd_cmd(0x0C);  // Dispaly on the Cursor
     __delay_ms(100);;
    lcd_cmd(0x01);
      __delay_ms(100);// clear screen
    
}

void lcd_data(unsigned char d)
{
   PORTC|=0x08;   // RC3 =1
   PORTD =d;      // DATA
   PORTC |= 0x01; // CLOCK ENABLE
   PORTC &=~0x01;  // CLOCLK DISABLE
   __delay_ms(100);
}

void lcd_cmd(unsigned char c)
{
    PORTC&=0XF7; // RC3 =0
    PORTD= c;
     PORTC |= 0x01; // CLOCK ENABLE
   PORTC &=~0x01;  // CLOCLK DISABLE
    __delay_ms(100);
}
      void lcd_output(unsigned int i)
{
    unsigned char r;
    j=1;
    val=i;
    
    while(val!=0)
    {
        r=val%10;
        store[j]=r;
        j++;
        val=val/10;
    }
    store[j]='\0';
    j=j-1;
    if(store[2]>0)      //  for handling single digit
    {
        n=0x30+store[2];
        lcd_data(n);
    }
    else
    {
        lcd_data(0x20);
    }
    n=0x30+store[1];
    lcd_data(n);
    n=0x56;
    lcd_data(n);
}