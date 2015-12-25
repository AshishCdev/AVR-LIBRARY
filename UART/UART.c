
/*
 * UART.c
 *
 * Created: 3/29/2015 2:28:20 AM
 *  Author: Ashish kushwaha
 * Email: Ashish_kushwaha@outlook.com
 * Website: arm-tutorials.com
 */ 
#include <avr/io.h>
#include <stdlib.h>
#include "UART.h"

void serial_init(){
		UCSRB=(1<<TXEN)|(1<<RXEN);		
		UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
		UBRRL=51;                                  ///9600   baudrate at xtal 11.0592Mhz	
}
//This function sends the string and terminates with LF \n
void serial_send(char *p)
{
	serial_Erase_all();
	for (;*p!=0;p++)
	{
		while (!(UCSRA&(1<<UDRE)));
		UDR=*p;
	}
	while (!(UCSRA&(1<<UDRE)));
	UDR=10;
}

void serial_send_byte(char byte){
	serial_Erase_all();
	while (!(UCSRA&(1<<UDRE)));
	UDR=byte;
}

void serial_Erase_all(void){
	unsigned char trash=0;
	while (UCSRA & (1<<RXC)){ 
	trash=UDR;
	}
}

unsigned char serial_read_byte(void)
{
	while (!(UCSRA&(1<<RXC)));
	return UDR;
}


char *serial_read_line(int size,char *target){
	target=(char*)malloc(sizeof(char)*size);
	int i=0;
	if (target==0) return 0; //returns if can't allocate the memory 
	else for(;((i<size)&&(target[i-1]=='\n')&&(target[i-1]=='\r'));i++){
		target[i]=serial_read_byte();
	}
	target[i-1]='\0';
	 return target;
}

int serial_read_int(void){
	int getval=0,ret=0,flag=0;
	while(getval!='\n'){
	getval=serial_read_byte();
	if (getval=='-')
	{
		flag=1;
	}
	if ((getval>='0')&&(getval<='9'))
	{
		ret=((ret*10)+(getval-48));
	}
	}
	if (flag==1)ret=(ret*(-1));
	return ret;	
}