/*
 * dcc_parser.c
 *
 *  Created on: Aug 17, 2023
 *      Author: fil
 */

#include "main.h"
#include "dcc_main.h"
#include "dcc_parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void encode_byte(uint32_t *dest , uint8_t value)
{
uint8_t i,mask=0x80;
	for ( i=0;i<8;i++)
	{
		dest[i] = DCC_0;
		if (( value & mask) == mask)
			dest[i] = DCC_1;
		mask = mask >> 1;
	}
}

void compile_command_packet(uint8_t address, uint8_t speed , char direction)
{
uint8_t ecc,data;
	data = 0x40 | speed;
	if ( direction == 'F')
		data |= 0x20;
	ecc = address ^ data;
	encode_byte((uint32_t *)&DCC_Work_Pkt.address,address);
	encode_byte((uint32_t *)&DCC_Work_Pkt.data,speed);
	encode_byte((uint32_t *)&DCC_Work_Pkt.ecc,ecc);
}

void compile_reset_packet(void)
{
	memcpy(&DCC_Work_Pkt,&DCC_Reset_Pkt,sizeof(DCC_Work_Pkt));
}

/* <f 1234 5678 9012> */
uint8_t one_byte_commands(char cmd)
{
uint8_t	ret_val = 0;

	switch ( cmd)
	{
	case 'A' 	: 	sprintf((char *)System.uart1_txbuf,"Track 0 Main On\n\r");
					System.dcc_flags |= DCC_DCC1_POWER;
					break;
	case 'a' 	: 	sprintf((char *)System.uart1_txbuf,"Track 0 Main Off\n\r");
					System.dcc_flags &= ~DCC_DCC1_POWER;
					break;
	case 'B' 	: 	sprintf((char *)System.uart1_txbuf,"Track 1 Main On\n\r");
					System.dcc_flags |= DCC_DCC2_POWER;
					break;
	case 'b' 	: 	sprintf((char *)System.uart1_txbuf,"Track 1 Main Off\n\r");
					System.dcc_flags &= ~DCC_DCC2_POWER;
					break;
	case 'x' 	: 	sprintf((char *)System.uart1_txbuf,"All Off\n\r");
					System.dcc_flags &= ~DCC_DCC1_POWER;
					System.dcc_flags &= ~DCC_DCC2_POWER;
					break;
	case 'X' 	: 	sprintf((char *)System.uart1_txbuf,"All On\n\r");
					System.dcc_flags |= DCC_DCC1_POWER;
					System.dcc_flags |= DCC_DCC2_POWER;
					break;
	case 'R' 	: 	sprintf((char *)System.uart1_txbuf,"Sent RESET\n\r");
					System.dcc_flags |= DCC_DCC1_RESET;
					System.dcc_flags |= DCC_DCC2_RESET;
					compile_reset_packet();
					break;
	case 'S' 	: 	sprintf((char *)System.uart1_txbuf,"Status\n\r");
					if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER)
						strcat((char *)System.uart1_txbuf,"Track0 ON\n\r");
					else
						strcat((char *)System.uart1_txbuf,"Track0 OFF\n\r");
					if ((System.dcc_flags & DCC_DCC2_POWER) == DCC_DCC2_POWER)
						strcat((char *)System.uart1_txbuf,"Track1 ON\n\r");
					else
						strcat((char *)System.uart1_txbuf,"Track1 OFF\n\r");
					break;
	default:	sprintf((char *)System.uart1_txbuf,"Command error\n\r");
				ret_val = 1;
	}
	return ret_val;
}

uint8_t four_bytes_commands(char cmd,int p0,int p1,char dir)
{
uint8_t	ret_val = 0;

	switch ( cmd)
	{
	case 'T' 	: 	sprintf((char *)System.uart1_txbuf,"T : Address %d , Speed %d , Direction %c\n\r",p0,p1,dir);
					compile_command_packet(p0,p1,dir);
					break;
	default:	sprintf((char *)System.uart1_txbuf,"Command error\n\r");
				ret_val = 1;
	}
	return ret_val;
}

uint8_t dcc_parser(void)
{
int	p0,p1,pnum;
char cmd,dir;
uint8_t	ret_val = 0;

	pnum = sscanf((char *)System.uart1_rxbuf,"%c %d %d %c",&cmd,&p0,&p1,&dir);
	switch (pnum)
	{
	case 1 :	ret_val = one_byte_commands(cmd);
				break;
	case 4 :	ret_val = four_bytes_commands(cmd,p0,p1,dir);
				break;
	default:	sprintf((char *)System.uart1_txbuf,"Command error %d\n\r",pnum);
				ret_val = 1;
	}
	if ( ret_val == 0 )
	{
		System.dcc_flags |= DCC_DCC1_PKTPEND;
		System.dcc_flags |= DCC_DCC2_PKTPEND;
	}
	System.uart1_txlen = strlen((char *)System.uart1_txbuf);
	return ret_val;
}
