#define  F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Pid_PWM.h"
#include "I2C.h"
#include "serial.h"


void controllo_movimento(int data){
	switch(data){
		case 0x01:
			stop_tutto();
			delay_movimento(2);		//sinistra
			break;
		case 0x02:
			avanti();
			delay_movimento(1);		//avanti
			/*_delay_ms(700);		//800
			stop_tutto();*/
			_delay_ms(500);
			break;
		case 0x03:
			stop_tutto();
			delay_movimento(3);		//destra
			break;
		case 0x04:
			stop_tutto();		//fermo
			break;
		
		
		//Giroscopio
		case 0x27:				//sinistra
			sinistra();
			break;
		case 0x26:				//destra
			destra();
			break;
		
		
		default:
			stop_tutto();
			break;
	}
}


void adc_init(){
	ADMUX = (1<<REFS0);
	ADCSRB = 0;
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1);
}

int adc_value(){
	int k;
	ADCSRA = ADCSRA | (1<<ADSC);
	while((ADCSRA&(1<<ADSC))!=0);
	k = ADC;
	return k;
}


void adc_control( int k ){		//definire delay
	if(k==400){
		stop_tutto();
		_delay_ms(300);
		indietro();
		_delay_ms(600);
	}
	else;
}

void controllo_telecamera( int data){
	int i;
	if(data == 0x36){
		Serial_Send("croce\n");
		avanti();
		_delay_ms(200);
		stop_tutto();
		_delay_ms(500);
		cubetto();
		for(i=0; i<5; i++){
			PORTF = 1;			//da definire		entrata o uscita adc?
			_delay_ms(450);
			PORTF = 0;				//da definire		entrata o uscita adc?
			_delay_ms(450);
		}
	}
	else;
}


void interrupt_rasp(){
	PORTF = 2;
	_delay_ms(10);
	PORTF = 0;
}