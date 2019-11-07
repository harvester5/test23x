/*******************************************************
Проект IC Tester
Определение 8 ножечных чипов
Project : 
Version : 
Date    : 19.10.2019
Author  : 
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <delay.h>  
#include <alcd.h>
// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

flash const char names[4][8] = {'L','M','3','2','8',  0, 0, 0,
                                'T','L','0','6','2',  0, 0, 0,
                                'M','O','S','F','E','T', 0, 0,
                                'M','C','3','4','0','6','3',0 };

unsigned int read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | ADC_VREF_TYPE;
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA|=(1<<ADSC);
    // Wait for the AD conversion to complete
    while ((ADCSRA & (1<<ADIF))==0);
    ADCSRA|=(1<<ADIF);
    return ADCW;
}

void main(void)
{
    char i, j;
    int r[8];
    DDRA=0;    PORTA=0;
    DDRB=0;    PORTB=0;
    DDRC=0;    PORTC=0;
    DDRD=0;    PORTD=0;

    ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);

    ADMUX=ADC_VREF_TYPE;
    ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 0
// RD - PORTB Bit 1
// EN - PORTB Bit 2
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
    lcd_init(16);
    lcd_puts("IC Tester");
    for (i=0; i<8; i++)
       {
       PORTC = 1<<i;
       for (j=0; j<8; j++)
         {
         r[j] = read_adc(j);
         }
       }
    
    while (1)
      {
      

      }
}
