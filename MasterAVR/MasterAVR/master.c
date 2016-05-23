/*
 * InterMicroControllerCommunication.c
 *
 * Created: 5/22/2016 11:22:12 PM
 *  Author: Shafi
 */ 


#include <avr/io.h>
#include <stdint-gcc.h>

//output
#define DATAREADY 0b00000001			//PINA0
#define DATAREADY2 0x02			//PINA1
#define DATAREADY3 0x04			//PINA2
#define DATAREADY4 0x08			//PINA3

//input
#define READYTOREAD 0b00010000		//PINA4

//output
#define DATASENT 0b00100000			//PINA5

//input
#define DATAREADCOMPLETE 0b01000000	//PINA6

int isSent = 0;
uint64_t track = 0;
unsigned char statusA;
	
void setup()
{
	DDRA = 0b00101111; // in in_dataReadComplete out_dataSent in_readyToRead out_dataReady1 out_dataReady2 out_dataReady3 out_dataReady4 
	DDRD = 0x00;
	DDRB = 0x00;
}

void sendData()
{
	PORTA = DATAREADY;
	statusA = DATAREADY;
	while((READYTOREAD & PINA) == 0)
	{
		statusA = PINA;
	}
	DDRD = 0xff;
	PORTD = 0b01010101;
	PORTA = DATASENT;
	statusA = DATASENT;
	while((DATAREADCOMPLETE & PINA) == 0)
	{
		statusA = PINA;
	}
	PORTA = 0x00; 
	isSent = 1;
	DDRD = 0x00;
	PORTA = 0x00;
}
int main(void)
{
	setup();
//	sendData();
    while(1)
    {
        //TODO:: Please write your application code 
		while(isSent == 0)
		{
			track++;
			sendData();
		}
	}
}


uint16_t data[] = {
	0b1111111111111111,
	0b0111111111111110,
	0b0011111111111100,
	0b0001111111111000,
	0b0000111111110000,
	0b0000011111100000,
	0b0000001111000000,
	0b0000000110000000,
	0b0000000110000000,
	0b0000001111000000,
	0b0000011111100000,
	0b0000111111110000,
	0b0001111111111000,
	0b0011111111111100,
	0b0111111111111110,
	0b1111111111111111
};