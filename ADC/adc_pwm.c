
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

// function prototype
void init();
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_output(unsigned int);


// variable name
unsigned char k[10];
unsigned char n,j;
unsigned int i, lowvalue,highvalue,voltage,value,m;



//main function
void main()
{
    init();
    while(1)
    {
        ADCON0=0x81; //1000 0001  // ADC ON
        ADCON0 |=0x04; // Status checking bit
        while(ADCON0 & 0x04);
        lowvalue=ADRESL;
        highvalue=ADRESH;
        value =((unsigned int)highvalue<<8)+(unsigned int)lowvalue; // changing to 10 bit
        voltage= value/3;
        lcd_cmd(0x80);
        lcd_output(voltage);
        CCPR1L=(voltage)>>2 ; // right shift the two bits, so 8 bit goes to CCPRIL
        CCP1CON=((CCP1CON & 0x0C )+((voltage &0x03)<<4)); // clearing 4:5 bit  << moving lsb bit to the 4:5;
        __delay_ms(1000);
        
    }
}


//function definition
void init()
{
    TRISD=0x00;
    TRISC= 0X00;
    TRISA=0x01;
    ADCON0=0X81;
    ADCON1=0x8E;
    CCP1CON=0x3C;
    CCPR1L=0x2E;
    T2CON= 0x06;  // timer 
    PR2=0x5E;      // period
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
    unsigned char s,j=1;
    m=i;
    while(m!=0)
    {
        s=m%10;
        k[j]=s;
        j++;
        m=m/10;
    }
    k[j]='\0';
    j=j-1;
    if(k[4]>0)
    {
        n=0x30+k[4];
        lcd_data(n);
        n=0x30+k[3];
        lcd_data(n);
        n=0x30+k[2];
        lcd_data(n);
        n=0x30+k[1];
        lcd_data(n);
        return;
    }
    else if(k[3]>0)
    {
        lcd_data(0x20);
        n=0x30+k[3];
        lcd_data(n);
        n=0x30+k[2];
        lcd_data(n);
        n=0x30+k[1];
        lcd_data(n);
        
    }
    else if(k[2]>0)
    {
        lcd_data(0x20);
        lcd_data(0x20);
        n=0x30+k[2];
        lcd_data(n);
        n=0x30+k[1];
        lcd_data(n);
        
    }
    else if(k[1]>0)
    {
        lcd_data(0x20);
         lcd_data(0x20);
          lcd_data(0x20);
          n=0x30+k[1];
          lcd_data(n);
         
        
    }
   
    n=0x56;
    lcd_data(n);
    __delay_ms(1000);
    
}

