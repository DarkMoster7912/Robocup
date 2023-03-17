/*
 * Controllo.h
 *
 * Created: 27/02/2023 17:59:41
 *  Author: Enrico
 */ 


#ifndef CONTROLLO_H_
#define CONTROLLO_H_

extern void controllo_movimento( int data );
extern void controllo_telecamera( int data );
extern void adc_init( void );
extern int adc_value( void );
extern void adc_control( int k );
extern void interrupt_rasp( void );


#endif /* CONTROLLO_H_ */