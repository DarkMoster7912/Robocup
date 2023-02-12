#define  F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Pid_PWM.h"
#include "I2C.h"
#include "serial.h"

volatile int data = 0;
void I2C_received(uint8_t received_data)
{
	data = received_data;
}

void I2C_requested()
{
	I2C_transmitByte(data);
}

int main(void)
{
	I2C_init(0x10);
	I2C_setCallbacks(I2C_received, I2C_requested);
	_delay_ms(1500);
    //PID();
	//PWM();
	_delay_ms(2000);
    while (1) 
    {
		//avanti();
		switch(data){
			//Laser
			case 0x11: 
				//laser1();
				stop_tutto();
				_delay_ms(1500);
				do{
					sinistra();
				} while(data != 0x27);
				stop_tutto();
				_delay_ms(1500);
				if((data != 0x11) |
				(data != 0x12) |
				(data != 0x13) |
				(data != 0x14) |
				(data != 0x15) |
				(data != 0x16) ){
					
					avanti();
					}else {
					do{
						destra();
					}while(data != 0x26);
					stop_tutto();
					_delay_ms(1500);
					
					if((data != 0x11) |
					(data != 0x12) |
					(data != 0x13) |
					(data != 0x14) |
					(data != 0x15) |
					(data != 0x16) ){
						avanti();
						}else{
						do{
							destra();
						}while(data != 0x26);
						stop_tutto();
						_delay_ms(1500);
						avanti();
					}
				}
			break;
			case 0x12:
				stop_tutto();
			break;
			case 0x13:
				stop_tutto();
			break;
			case 0x14:
				stop_tutto();
			break;
			case 0x15:
				stop_tutto();
			break;
			case 0x16:
				stop_tutto();
			break;
			//Giroscopio
			case 0x17:
				stop_tutto();
			break;
			case 0x18:
				stop_tutto();
			break;
			case 0x19:
				avanti();
			break;
			//Telecamere
			case 0x20:
			//code
			break;
			//altro?
		}
    }
}

