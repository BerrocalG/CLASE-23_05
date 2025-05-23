#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned char value=0;
unsigned char dato=0;
void config_ADC(void){
  ADCSRA|=(1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADMUX|=(1<<REFS0);
}


ISR(ADC_vect){
  unsigned char low=ADCL;
  unsigned char high=ADCH;
  value=(high*256+low)*(5.0/1023.0);
  UCSR0B|=(1<<UDRIE0);


}
void config_USART(void){
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
  UBRR0=103;
 
}


char flag=0;
ISR(USART_UDRE_vect){
 
 
 UDR0=value+48;
 UCSR0B&=~(1<<UDRIE0);
 ADCSRA|=(1<<ADSC);
}


int main(void){
  DDRD|=0x02;
  config_ADC();
  config_USART();
  sei();
  ADCSRA|=(1<<ADSC);
  while(1){
     
  }
}
