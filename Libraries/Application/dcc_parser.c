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

uint8_t compile_reset_packet(void)
{
	if ( ((System.dcc_flags & DCC_DCC1_POWER) == 0 ) && ((System.dcc_flags & DCC_DCC2_POWER) == 0 ))
			return 1;
	encode_byte((uint16_t *)&DCC_Work_Pkt.address,0);
	encode_byte((uint16_t *)&DCC_Work_Pkt.data,0);
	encode_byte((uint16_t *)&DCC_Work_Pkt.ecc,0);
	System.dcc_flags |= DCC_DCC1_PKTPEND;
	System.dcc_flags |= DCC_DCC2_PKTPEND;
	return 0;
}

uint8_t	temp_string[DCC_HOST_MAX_LEN];

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
	case 'R' 	: 	ret_val = compile_reset_packet();
					if ( ret_val )
						sprintf((char *)System.uart1_txbuf,"RESET failed, no powered track found\n\r");
					else
					{
						sprintf((char *)System.uart1_txbuf,"Sent RESET\n\r");
						System.dcc_flags |= DCC_DCC1_RESET;
						System.dcc_flags |= DCC_DCC2_RESET;
					}
					ret_val = 0;
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
					sprintf((char *)temp_string,"Repetition ch1 %d ch2 %d\n\r",System.dcc_ch1_repeat_number+1,System.dcc_ch2_repeat_number+1);
					strcat((char *)System.uart1_txbuf,(char *)temp_string);
					break;
	default:		ret_val = 1;
	}
	return ret_val;
}

uint8_t two_bytes_commands(char cmd,int track,int address,int data)
{
uint8_t ecc;
	if ( cmd == 'T' )
	{
		ecc = address ^ data;
		encode_byte((uint16_t *)&DCC_Work_Pkt.address,address);
		encode_byte((uint16_t *)&DCC_Work_Pkt.data,data);
		encode_byte((uint16_t *)&DCC_Work_Pkt.ecc,ecc);
		encode_byte((uint16_t *)&DCC_Work_Pkt.fill,0xff);

		if ( track == 1 )
		{
			if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER )
				System.dcc_flags |= DCC_DCC1_PKTPEND;
		}
		if ( track == 2 )
		{
			if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER )
				System.dcc_flags |= DCC_DCC2_PKTPEND;
		}
		if ( ((System.dcc_flags & DCC_DCC1_PKTPEND) == DCC_DCC1_PKTPEND ) || ((System.dcc_flags & DCC_DCC2_PKTPEND) == DCC_DCC2_PKTPEND ) )
			sprintf((char *)System.uart1_txbuf,"track %d address %d data %d\n\r",track,address,data);
		else
			sprintf((char *)System.uart1_txbuf,"%s Command failed, track %d is off\n\r",TRACK_NOT_POWERED_ERROR,track);
		return 0;
	}
	return 1;
}

uint8_t three_bytes_commands(char cmd,int track,int address,int datal,int datah)
{
uint8_t ecc;
	if ( cmd == 'T' )
	{
		ecc = address ^ datal ^ datah;
		encode_byte((uint16_t *)&DCC_Work_Pkt.address,address);
		encode_byte((uint16_t *)&DCC_Work_Pkt.data,datal);
		encode_byte((uint16_t *)&DCC_Work_Pkt.ecc,datah);
		encode_byte((uint16_t *)&DCC_Work_Pkt.fill,ecc);
		if ( track == 1 )
		{
			if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER )
				System.dcc_flags |= DCC_DCC1_PKTPEND;
		}
		if ( track == 2 )
		{
			if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER )
				System.dcc_flags |= DCC_DCC2_PKTPEND;
		}
		if ( ((System.dcc_flags & DCC_DCC1_PKTPEND) == DCC_DCC1_PKTPEND ) || ((System.dcc_flags & DCC_DCC2_PKTPEND) == DCC_DCC2_PKTPEND ) )
			sprintf((char *)System.uart1_txbuf,"track %d address %d datal %d datah %d\n\r",track,address,datal,datah);
		else
			sprintf((char *)System.uart1_txbuf,"%s Command failed, track %d is off\n\r",TRACK_NOT_POWERED_ERROR,track);
		return 0;
	}
	return 1;
}

uint8_t dcc_parser(void)
{
int	p0,p1,p2,p3,p4,pnum,cmdlen;
char cmd;
uint8_t	ret_val = 1;

	cmdlen = strlen((char * )System.uart1_rxbuf);
	pnum = sscanf((char *)System.uart1_rxbuf,"%c %d %d %d %d %d",&cmd,&p0,&p1,&p2,&p3,&p4);
	switch (pnum)
	{
	case 1 :	ret_val = one_byte_commands(cmd);
				break;
	case 4 :	ret_val = two_bytes_commands(cmd,p0,p1,p2); // <T 1 12 33>
				break;
	case 5 :	ret_val = three_bytes_commands(cmd,p0,p1,p2,p3); // <T 1 12 33 55>
				break;
	default:	break;// <D 1 12 33 55>
	}

	if ( ret_val  )
		sprintf((char *)System.uart1_txbuf,"%s Command error %d params string # %s #\n\r",PARAMETER_ERROR,pnum,(char *)System.uart1_rxbuf);

	bzero(System.uart1_rxbuf,cmdlen);
	System.uart1_txlen = strlen((char *)System.uart1_txbuf);
	return ret_val;
}
