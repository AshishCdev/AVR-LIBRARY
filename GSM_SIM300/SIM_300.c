
/*
 * SIM_300.c
 *
 * Created: 3/29/2015 2:28:20 AM
 *  Author: Ashish kushwaha
 * Email: ashish_kushwaha@outlook.com
 * Website: arm-tutorials.com
 */ 
#define F_CPU 11059200

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "SIM_300.h"

char j[buff_size];

void serial_init(){
		UCSRB=(1<<TXEN)|(1<<RXEN)|(1<<RXCIE);		
		UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
		UBRRL=5;                                  ///115200   baudrate at xtal 11.0592Mhz	
}
//This function sends the string and terminates with CR for GSM application
void serial_send(char *p)
{
	serial_Erase_all();
	for (;*p!=0;p++)
	{
		while (!(UCSRA&(1<<UDRE)));
		UDR=*p;
	}
	while (!(UCSRA&(1<<UDRE)));
	UDR='\r';
}

void serial_send_byte(char byte){
	serial_Erase_all();
	while (!(UCSRA&(1<<UDRE)));
	UDR=byte;
}

void serial_Erase_all(void){
	_delay_ms(50);
	unsigned char trash=0;
	while (UCSRA & (1<<RXC)){ 
	trash=UDR;
	}
	UDR=0;
}

unsigned char serial_read_byte(void)
{
	while (!(UCSRA&(1<<RXC)));
	return UDR;
}


unsigned int *GSM_read_line(char after){
	int i=-1;
	char trash=0;
	for(after;after>0;--after){
		trash = serial_read_byte();	
		}
	do
	{	i++;
		j[i]=serial_read_byte();
	}while(j[i]!='\r');
	j[i]='\0';
	serial_Erase_all();
	return j;
}

int serial_read_int(void){
	int getval=0,ret=0,flag=0;
	while(getval!='\r'){
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

void serial_Erase_n(char bytes){
	unsigned char trash=0;
	for (bytes;bytes<0;--bytes)
	{
		while (!(UCSRA&(1<<RXC)));
		trash=UDR;
	}
	
}
///////////////////////time_out using watchDOG timer
void timeoutEN(void){
	WDTCR|=(1<<WDE)|(1<<WDP0)|(1<<WDP1)|(1<<WDP2);
}

void timeoutDIS(void){
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	WDTCR = 0x00;
}
/////////////////////////////////////////////////////

void GSM_init(void){
	
		serial_init();
		serial_send_byte('A');
		serial_send_byte('T');
		serial_send_byte('\r');
		serial_send("ATE0");
		timeoutEN();
		if (!(strcmp(GSM_read_line(2),"OK")))	
		timeoutDIS();
		else while(1);
}

char GSM_sim_sta(void){
	serial_send("AT+CSMINS?");
	return (!strcmp(GSM_read_line(11),"0,1"));
	 
}

char GSM_regis(void){
	serial_send("AT+CREG?");
	return(!strcmp(GSM_read_line(9),"0,1"));
}

unsigned int *GSM_get_string(void){
	char trash=0;
	int i=-1;
	do 
	{
		trash=serial_read_byte();
	} while (trash!=34);
	
	do
	{	i++;
		j[i]=serial_read_byte();
	}while(j[i]!=34);
	j[i]='\0';
	serial_Erase_all();
	return j;
}

void GSM_call_dis(void){
	serial_send("ATH0");
	serial_Erase_all();
}

unsigned long digi_extract(char *p){
	int ret=0;
	for (char i=0;p[i]!='\0';i++)
	{
	if ((p[i]>='0')&&(p[i]<='9'))
	{
		ret=((ret*10)+(p[i]-48));
	}
	}
	return ret;	
}

void serial_send_nf(char *p){
	serial_Erase_all();
	for (;*p!=0;p++)
	{
		while (!(UCSRA&(1<<UDRE)));
		UDR=*p;
	}
}