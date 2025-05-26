/*
//ejercicio 1: mostrar voltaje potenciometro con interrupciones de 0.0 a 5.0
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

float value=0;
unsigned char dato=0;
int flag=0;
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
  UBRR0=103; //velocidadde tranmision por palabra
}

ISR(USART_UDRE_vect){
  switch(flag){
    case 0:
    UDR0=(unsigned char)(value)+48; //unidad
    flag=1;
    break;
    case 1:
    UDR0=(unsigned char)(46);//punto
    flag=2;
    break;
    case 2:
    UDR0=((unsigned char)(value*10))%10+48; //decena
    flag=3;
    break;
    case 3:
    UDR0=((unsigned char)(value*100))%10+48;//centena
    flag=4;
    break;
    case 4:
    UDR0=(unsigned char)(13); //abajo
    flag=5;
    break;
    case 5:
    UDR0=(unsigned char)(10); //izquierda
    flag=0;
    UCSR0B&=~(1<<UDRIE0);
    ADCSRA|=(1<<ADSC);
    _delay_ms(100);
    break;
  }
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
  */
/*
  //EJERCICIO 2 para recibir un caracter
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

  char receive_char(void){
    while(!(UCSR0A&(1<<RXC0)));
    return UDR0;
  }

  void config_USART(void){
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UBRR0=103;
  }
  unsigned char dato=0;
  ISR(USART_UDRE_vect){
    UDR0=dato;
    UCSR0B&=~(1<<UDRIE0);
  }
  int main(void){
    config_USART();
    sei();
    while(1){
      dato=receive_char();
      UCSR0B|=(1<<UDRIE0);
    }
  }
*/


//EJERCICIO 3 con interrupcion usart

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
float value=0;
int flag=0;
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

char receive_char(void){
  while(!(UCSR0A&(1<<RXC0)));
  return UDR0;
}

void config_USART(void){
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0)| (1<<RXCIE0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
  UBRR0=103;//9600 
}

unsigned char dato=0;
ISR(USART_UDRE_vect){
  switch(flag){
    
    case 0:
    UDR0=(unsigned char)(value)+'0';
    flag=1;
    break;

    case 1:
    UDR0=(unsigned char)(46);
    flag=2;
    break;

    case 2:
    UDR0=((unsigned char)(value*10))%10+'0';
    flag=3;
    break;

    case 3:
    UDR0=((unsigned char)(value*100))%10+'0';
    flag=4;
    break;

    case 4:
    UDR0=(unsigned char)(13);
    flag=5;
    break;

    case 5:
    UDR0=(unsigned char)(10);
    flag=0;
    UCSR0B&=~(1<<UDRIE0);
   _delay_ms(100);
    break;
  }
}

ISR(USART_RX_vect){
  dato=UDR0;
   if(dato=='a'){
    dato=0;
    ADCSRA|=(1<<ADSC);
   }
}

int main(void){
  config_USART();
  config_ADC();
  sei();
  while(1){
   
  }
}


//EJERCICIO 4 
