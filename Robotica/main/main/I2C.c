/*
 * I2C.c
 *
 * Created: 24/11/2022 15:58:59
 *  Author: Enrico
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>
#include "I2C.h"
#include "serial.h"

//BAUD RATE 1*10^6	
volatile int k;
/*uint8_t sendData[TWI_DATA_LENGTH];
uint8_t receivedData[TWI_DATA_LENGTH];


void init_interrupt(){
	sei();
}

void init_TWI(){
	TWCR = (1 << TWEN) | (1 << TWIE);		//Enable TWI and Enable Interrupt
	TWBR = ((F_CPU / SCL_FREQ) - 16) / 2;		//Set SCL to 100kHz
}

//TWI functions
ISR(TWI_vect){
	static int byteNumber = 0;					//Count the bytes received from the slave
	
	switch(TWSR){
		case 0x40:								//0x40 SLA+R has been transmitted; ACK has been received
		byteNumber = 0;							//Reset byte counter
		TWI_ACK();								//Continue TWI with acknowledgment enabled
		break;
		
		case 0x50:								//0x50 Data byte has been received; ACK has been returned
		receivedData[byteNumber] = TWDR;		//Read the data register and save the data
		byteNumber++;							//Increase the counter for the next byte
		if(byteNumber < TWI_DATA_LENGTH - 1){	//If the next byte is NOT the last
			TWI_ACK();								//Continue with ACK
			}else{									//Else
			TWI_NACK();								//Continue and send NACK after the next byte to stop the slave
		}
		break;
		
		case 0x58:								//0x58 Data byte has been received; NOT ACK has been returned
		receivedData[byteNumber] = TWDR;		//Read the last byte
		TWI_Stop();								//And stop the TWI connection
		break;
	}
}

void writeToSlave(uint8_t address, uint8_t* data){
	
	TWI_Start();								//Send a start signal to claim the data bus
	TWICheckCode(0x08);							//0x08 - A START condition has been transmitted
	
	TWIWrite(address << 1);						//Send an address over the data line to address a slave
	TWICheckCode(0x18);							//0x18 - SLA+W has been transmitted; ACK has been received
	
	for(int i = 0; i < TWI_DATA_LENGTH; i++){	//Send all the bytes in the array one by one
		TWIWrite(data[i]);							//Send the current data byte to the slave
		TWICheckCode(0x28);							//0x28 - Data byte has been transmitted; ACK has been received
	}
	
	TWI_Stop();									//Stop the TWI connection
	
}
void readFromSlave(uint8_t address){
	
	TWI_Start();								//Send a start signal to claim the data bus
	TWICheckCode(0x08);							//0x08 - A START condition has been transmitted
	
	TWIWrite( (address << 1) + 1 );				//Send an address over the data line with a 'read' request to request data from a slave
	
	//The rest of the functions are handled by the ISR based on the different status codes
}

void TWIWrite(uint8_t byte){
	TWDR = byte;					//Set the data in the data register to be handled by the TWI
	TWI_NACK();						//Start the TWI send process, ACK is not needed because we are sending
	TWIWaitUntilReady();			//Wait until the TWI has finished its task to avoid outrunning the TWI
}
void TWIWaitUntilReady(){
	while (!(TWCR & (1 << TWINT)));	//Wait until the TWI has finished its task by listening to the INT bit
}
void TWICheckCode(uint8_t code){
	uint8_t TWIstatus = (TWSR & 0xF8);		//Read the status code by masking off the unused register bits in TWSR
	if(TWIstatus != code){
		Serial_Send("\n\n\rERROR: Wrong status!\n\rTWI status: 0x");
		Serial_Send("\n\rExpected status: 0x");
		Serial_Send( itoa( code, buffer, 16) );
		Serial_Send("\n\n\r");
	}
}*/

uint8_t sendData[TWI_DATA_LENGTH];
uint8_t receivedData[TWI_DATA_LENGTH];


void k0x60( int byteNumber){
	byteNumber = 0;							//Reset byte counter
	TWI_ACK();
}

void k0x80( int byteNumber){
	receivedData[byteNumber] = TWDR;		//Read the data register and save the data
	byteNumber++;							//Increase the counter for the next byte
	if(byteNumber < TWI_DATA_LENGTH - 1){	//If the next byte is NOT the last
		TWI_ACK();								//Continue with ACK
		}else{									//Else
		TWI_NACK();								//Continue and send NACK after the next byte to stop the slave
	}
}

int conversione(){
	k=8;
	if(k==8){
		/*int i;
		int Data;
		for(i=0; i<8; i++){
			Data += receivedData[i] * pow(2, i);
		}
		return Data;*/
		return receivedData[0];
	}
	return 0;
}

void k0x88( int byteNumber){
	receivedData[byteNumber] = TWDR;		//Read the last byte
	TWI_NACK();
	//TWI_Stop();								//And stop the TWI connection
}

void init_interrupt(){
	sei();
}

void init_TWI(){
	TWCR = (1<<TWEN)|(1<<TWEA)|(1<<TWINT)|(1<<TWIE);/*(1 << TWEN) | (1 << TWEA);*/		//Enable TWI and Enable Interrupt
	//TWBR = ((F_CPU / SCL_FREQ) - 16) / 2;		//Set SCL to 100kHz
	TWAR = 0x10<<1;			//Slave address
	DDRD=1;
}


//TWI functions
ISR(TWI_vect){
	static int byteNumber = 0;					//Count the bytes received from the slave
	
	switch(TWSR){
		case 0x60:								//0x40 SLA+R has been received; ACK has been received
		/*byteNumber = 0;							//Reset byte counter
		TWI_ACK();*/
		k0x60(byteNumber);								//Continue TWI with acknowledgment enabled
		conversione();
		break;
		
		case 0x80:								//0x50 Data byte has been received; ACK has been returned
		/*receivedData[byteNumber] = TWDR;		//Read the data register and save the data
		byteNumber++;							//Increase the counter for the next byte
		if(byteNumber < TWI_DATA_LENGTH - 1){	//If the next byte is NOT the last
			TWI_ACK();								//Continue with ACK
			}else{									//Else
			TWI_NACK();								//Continue and send NACK after the next byte to stop the slave
		}*/
		k0x80(byteNumber);
		break;
		
		case 0x88:								//0x58 Data byte has been received; NOT ACK has been returned
		/*receivedData[byteNumber] = TWDR;		//Read the last byte
		TWI_Stop();*/								//And stop the TWI connection
		k0x88(byteNumber);
		break;
	}
}





void TWIWaitUntilReady(){
	while (!(TWCR & (1 << TWINT)));	//Wait until the TWI has finished its task by listening to the INT bit
}


void TWI_Start(){
	TWCR = (1<<TWEN)|(1<<TWEA)|(1<<TWINT)|(1<<TWIE);	//Start TWI; Enable TWI; Enable TWI interrupt; Send start signal;
	TWIWaitUntilReady();								//Wait until start is send;
}
/*void TWI_Stop(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)/*|(1<<TWSTO);	//Start TWI; Enable TWI; Enable TWI interrupt; Send stop signal;
}*/
void TWI_ACK(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE)|(1<<TWEA);	//Continue TWI; Enable TWI; Enable TWI interrupt; Enable acknowledgment;
}
void TWI_NACK(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWIE);				//Start/continue TWI; Enable TWI; Enable TWI interrupt;
}
