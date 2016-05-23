/*
 * InterMicroControllerCommunication.c
 *
 * Created: 5/22/2016 11:22:12 PM
 *  Author: Shafi
 */ 


#include <avr/io.h>
#include <stdint-gcc.h>

//output
#define DATAREADY 0x00			//PINA0
#define DATAREADY2 0x02			//PINA1
#define DATAREADY3 0x04			//PINA2
#define DATAREADY4 0x08			//PINA3

//input
#define READYTOREAD 0x10		//PINA4

//output
#define DATASENT 0x12			//PINA5

//input
#define DATAREADCOMPLETE 0x14	//PINA6

void setup()
{
	DDRA = 0b00101111; // in in_dataReadComplete out_dataSent in_readyToRead out_dataReady1 out_dataReady2 out_dataReady3 out_dataReady4 
	DDRD = 0x00;
	DDRB = 0x00;
}

void sendData()
{
	PORTA = DATAREADY;
	while((READYTOREAD & PINA) == 0)
	{
		;
	}
	DDRD = 0xff;
	PORTD = 0b01010101;
	PORTA = DATASENT;
	while((DATAREADCOMPLETE & PINA) == 0)
	{
		;
	}
	DDRD = 0x00;
	PORTA = 0x00;
}
int main(void)
{
	setup();
	sendData();
    while(1)
    {
        //TODO:: Please write your application code 
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