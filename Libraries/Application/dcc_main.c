/*
 * dcc_main.c
 *
 *  Created on: Aug 16, 2023
 *      Author: fil
 */
#include "main.h"
#include "lcd.h"
#include "stm32746g_discovery.h"
#include "dcc_parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

System_TypeDef	System;

DCC_Pkt_TypeDef	DCC_Idle_Pkt =
{
	.preamble = {
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1
	},
	.separator0 = DCC_0,
	.address = {
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1
	},
	.separator1 = DCC_0,
	.data = {
			DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0
	},
	.separator2 = DCC_0,
	.ecc = {
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1
	},
	.endpacket = DCC_1,
};

DCC_Pkt_TypeDef	DCC_Reset_Pkt =
{
	.preamble = {
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1
	},
	.separator0 = DCC_0,
	.address = {
			DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0
	},
	.separator1 = DCC_0,
	.data = {
			DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0
	},
	.separator2 = DCC_0,
	.ecc = {
			DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0
	},
	.endpacket = DCC_1,
};

DCC_Pkt_TypeDef	DCC_Work_Pkt =
{
	.preamble = {
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,
			DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1,DCC_1
	},
	.separator0 = DCC_0,
	.address = {
			DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0
	},
	.separator1 = DCC_0,
	.data = {
			DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0
	},
	.separator2 = DCC_0,
	.ecc = {
			DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0,DCC_0
	},
	.endpacket = DCC_1,
};


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ( htim == &TICK_TIMER )
		System.tick_flags |= TICK10ms_FLAG;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if ( huart == &DCC_HOST)
	{
		System.uart1_rxchar = DCC_HOST.Instance->RDR;
		System.uart1_flags |= UART1_CH;
		if ( (( System.uart1_flags & UART1_OPENFLAG) == 0 ) && ( System.uart1_rxchar == '<' ) )
		{
			System.uart1_flags |= UART1_OPENFLAG;
			System.uart1_rxindex = 0;
		}
		else
		{
			if ( (( System.uart1_flags & UART1_OPENFLAG) == UART1_OPENFLAG ) && ( System.uart1_rxchar == '>' ))
			{
				System.uart1_flags &= ~UART1_OPENFLAG;
				System.uart1_flags |= UART1_BUF;
			}
			else
			{
				System.uart1_rxbuf[System.uart1_rxindex] = System.uart1_rxchar;
				System.uart1_rxindex++;
				System.uart1_rxindex &= (DCC_HOST_MAX_LEN-1);
			}
		}
	}
}

static void CH1_XferHalfCpltCallback(DMA_HandleTypeDef *hdma)
{
	System.system |= (SYSTEM_DCC1_HALFDONE | SYSTEM_DCC1_DMADONE);
}

static void CH1_XferCpltCallback(DMA_HandleTypeDef *hdma)
{
	System.system &= ~SYSTEM_DCC1_HALFDONE;
	System.system |= SYSTEM_DCC1_DMADONE;
}

static void PWM_Start_DCC_CH1(void)
{
	DCC_CH1.hdma[TIM_DMA_ID_CC1]->XferHalfCpltCallback = CH1_XferHalfCpltCallback;
	DCC_CH1.hdma[TIM_DMA_ID_CC1]->XferCpltCallback = CH1_XferCpltCallback;
	/* Set the DMA error callback */
	DCC_CH1.hdma[TIM_DMA_ID_CC1]->XferErrorCallback = TIM_DMAError ;
	/* Enable the DMA channel */
	HAL_DMA_Start_IT( DCC_CH1.hdma[TIM_DMA_ID_CC1], (uint32_t)System.dcc_ch1_packet, (uint32_t)&DCC_CH1.Instance->PSC, DCC_PACKET_LEN);

	/* Enable the TIM Capture/Compare 1 DMA request */
	DCC_CH1.Instance->DIER |= TIM_DMA_CC1;

	DCC_CH1.Instance->BDTR|=TIM_BDTR_MOE;
	/* Enable the Peripheral */
	//DCC_CH1.Instance->CR1|=TIM_CR1_CEN;
}

void init_dcc_pkt(void)
{
uint32_t	i,k,*idle = (uint32_t *)&DCC_Idle_Pkt;
	for(k=0;k<NUM_DCC_PACKET;k++)
		for(i=0;i<DCC_PACKET_LEN;i++)
			System.dcc_ch1_packet[i+k*DCC_PACKET_LEN] = idle[i];
}

void dcc_init(void)
{
	DBGMCU->APB1FZ = 0xFFFFFFFF;
	DBGMCU->APB2FZ = 0xFFFFFFFF;

	LCD_config();
	HAL_TIM_Base_Start_IT(&TICK_TIMER);
	HAL_UART_Receive_IT(&DCC_HOST, &System.uart1_rxchar, 1);
	init_dcc_pkt();
	PWM_Start_DCC_CH1();
	BSP_LED_Init(LED_GREEN);
}



uint8_t state = 0;
void dcc_loop(void)
{
	if ((System.tick_flags & TICK10ms_FLAG) == TICK10ms_FLAG)
	{
		System.tick_counter++;
		if ( System.tick_counter > 100 )
		{
			System.tick_counter=0;
			LCD_demo(state);
			BSP_LED_On(LED_GREEN);
			state++;
			state &= 0x03;
		}
		else
			BSP_LED_Off(LED_GREEN);

		System.tick_flags &= ~TICK10ms_FLAG;
	}

	if ((System.uart1_flags & UART1_CH) == UART1_CH)
	{
		HAL_UART_Receive_IT(&DCC_HOST, &System.uart1_rxchar, 1);
		System.uart1_flags &= ~UART1_CH;
	}

	if ((System.uart1_flags & UART1_BUF) == UART1_BUF)
	{
		dcc_parser();
		System.uart1_flags &= ~UART1_BUF;
		HAL_UART_Transmit_IT(&DCC_HOST, System.uart1_txbuf, System.uart1_txlen);
	}

	if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER)
		DCC_CH1.Instance->CR1 |= TIM_CR1_CEN;
	else
		DCC_CH1.Instance->CR1 &= ~TIM_CR1_CEN;

	if ((System.dcc_flags & DCC_DCC2_POWER) == DCC_DCC2_POWER)
		DCC_CH2.Instance->CR1 |= TIM_CR1_CEN;
	else
		DCC_CH2.Instance->CR1 &= ~TIM_CR1_CEN;

	if ((System.dcc_flags & DCC_DCC1_PKTPEND) == DCC_DCC1_PKTPEND)
	{
		if ((System.system & SYSTEM_DCC1_DMADONE) == SYSTEM_DCC1_DMADONE)
		{
			if ((System.system & SYSTEM_DCC1_HALFDONE) == SYSTEM_DCC1_HALFDONE)
			{
				memcpy(&System.dcc_ch1_packet,&DCC_Work_Pkt,sizeof(DCC_Work_Pkt));
			}
			else
			{
				memcpy(&System.dcc_ch1_packet+sizeof(System.dcc_ch1_packet)/2,&DCC_Work_Pkt,sizeof(DCC_Work_Pkt));
			}
			memcpy(&DCC_Work_Pkt,&DCC_Idle_Pkt,sizeof(DCC_Work_Pkt));
			System.system &= ~SYSTEM_DCC1_DMADONE;
		}
		System.dcc_flags &= ~DCC_DCC1_PKTPEND;
	}
}
