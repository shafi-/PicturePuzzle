/*
 * slave.c
 *
 * Created: 5/22/2016 11:23:31 PM
 *  Author: Shafi
 */ 

#include <avr/io.h>
#include <stdint-gcc.h>

//input
#define DATAREADY 0b00000001			//PINA0

//output
#define READYTOREAD 0b00010000			//PINA4

//input
#define DATASENT 0b00100000				//PINA5

//output
#define DATAREADCOMPLETE 0b01000000		//PINA6

unsigned char data = 0x00;
unsigned char pinAStatus;
uint64_t track = 0;

unsigned char rcvdData[] =
{
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};


void setup()
{
	DDRA = 0b11011110; //1 dataReadComplete dataSent ReadyToRead 111 DataReady
	DDRB = 0xff;
	DDRC = 0xff;
	DDRD = 0x00;	
}

void readData()
{
	if((DATAREADY & PINA) == 1)
	{
		DDRD = 0x00;
		PORTB = (PORTB | 0b00000001);
		PORTA = READYTOREAD;
		while((DATASENT & PINA) == 0)
		{
			pinAStatus = PINA;
			//if((DATAREADY && PINA) == 0)
			//	return;
		}
//		if((DATASENT & PINA) == 1)
		{
			PORTB = (PORTB | 0b00000010);
			rcvdData[0] = PIND;
			PORTC = 0b00000111;
			PORTB = PIND; 
			DDRD = 0xff;
			PORTA = DATAREADCOMPLETE;
		}
	}
	track++;
}

void writeData()
{
	PORTB = rcvdData[0];
}

int main(void)
{
	setup();
	while(1)
	{
		readData();
		writeData();		
	}
	return 0;
}