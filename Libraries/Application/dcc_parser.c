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

void encode_byte(uint16_t *dest , uint8_t value)
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
	encode_byte((uint16_t *)&DCC_Work_Pkt.address,address);
	encode_byte((uint16_t *)&DCC_Work_Pkt.data,speed);
	encode_byte((uint16_t *)&DCC_Work_Pkt.ecc,ecc);
}

void compile_reset_packet(void)
{
	memcpy(&DCC_Work_Pkt,&DCC_Reset_Pkt,sizeof(DCC_Work_Pkt));
	System.dcc_flags |= DCC_DCC1_PKTPEND;
	System.dcc_flags |= DCC_DCC2_PKTPEND;
}

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
	default:		ret_val = 255;
	}
	return ret_val;
}

uint8_t four_bytes_commands(char cmd,int p0,int p1,int p2,char dir)
{
uint8_t	ret_val = 0;

	switch ( cmd)
	{
	case 'A' 	:	if (( p0 == 1 ) || (p0 == 2 ))
					{
						sprintf((char *)System.uart1_txbuf,"Track %d , Address %d , Speed %d , Direction %c\n\r",p0,p1,p2,dir);
						compile_command_packet(p1,p2,dir);
						ret_val = p0-1;
					}
					else
					{
						ret_val = 255;
					}
					break;
	default:		ret_val = 255;
	}
	return ret_val;
}

uint8_t dcc_parser(void)
{
int	p0,p1,p2,pnum,cmdlen;
char track,cmd,speed,dirflag,dir;
uint8_t	ret_val = 0;

	cmdlen = strlen((char * )System.uart1_rxbuf);
	pnum = sscanf((char *)System.uart1_rxbuf,"%c %d %c %d %c %d %c %c",&track,&p0,&cmd,&p1,&speed,&p2,&dirflag,&dir);
	switch (pnum)
	{
	case 1 :	ret_val = one_byte_commands(track);
				break;
	case 8 :	ret_val = four_bytes_commands(cmd,p0,p1,p2,dir); // <T 1 A 55 S 12 D F>   <T 2 A 1 S 12 D F>
				break;
	default:	ret_val = 255;// <T 4 A 1 S 12 D F>
	}
	if ( ret_val == 255 )
	{
		sprintf((char *)System.uart1_txbuf,"Command error %d\n\r",pnum);
	}
	else
	{
		if (pnum != 1 )	// single bytes commands has no modulation excluding reset
		{
			if ( ret_val == 0 )
			{
				if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER )
					System.dcc_flags |= DCC_DCC1_PKTPEND;
				else
					sprintf((char *)System.uart1_txbuf,"Track %d is off\n\r",ret_val);
			}
			if ( ret_val == 1 )
			{
				if ((System.dcc_flags & DCC_DCC2_POWER) == DCC_DCC2_POWER )
					System.dcc_flags |= DCC_DCC2_PKTPEND;
				else
					sprintf((char *)System.uart1_txbuf,"Track %d is off\n\r",ret_val);
			}
		}
	}
	bzero(System.uart1_rxbuf,cmdlen);
	System.uart1_txlen = strlen((char *)System.uart1_txbuf);
	return ret_val;
}
