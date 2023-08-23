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
	.endpacket = DCC_TERM,
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

void set_trig(uint8_t val )
{
	if ( val )
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_SET);
	else
		  HAL_GPIO_WritePin(ARDUINO_D2_GPIO_Port, ARDUINO_D2_Pin, GPIO_PIN_RESET);
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim)
{
	System.system |= SYSTEM_DCC1_HALFDONE;
	System.system |= SYSTEM_DCC1_EXPIRED;

	if ((System.system & SYSTEM_DCC1_HPACKET) == SYSTEM_DCC1_HPACKET)
	{
		System.dcc_flags |= DCC_DCC1_TXDONE;
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	System.system &= ~SYSTEM_DCC1_HALFDONE;
	System.system |= SYSTEM_DCC1_EXPIRED;

	if ((System.system & SYSTEM_DCC1_FPACKET) == SYSTEM_DCC1_FPACKET)
	{
		System.dcc_flags |= DCC_DCC1_TXDONE;
	}
}

void init_dcc_pkt(void)
{
	memcpy(&System.dcc_ch1_packet,&DCC_Idle_Pkt,DCC_PACKET_LEN*2);
	memcpy(&System.dcc_ch1_packet[DCC_PACKET_LEN],&DCC_Idle_Pkt,DCC_PACKET_LEN*2);
}
/*
 * change
 * 		if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)pData, (uint32_t)&htim->Instance->CCR1,Length) != HAL_OK)
 * to
 *		if (HAL_DMA_Start_IT(htim->hdma[TIM_DMA_ID_CC1], (uint32_t)pData, (uint32_t)&htim->Instance->PSC,Length) != HAL_OK)
 * in
 * 		HAL_TIM_PWM_Start_DMA , stm32f7xx_hal_tim.c, line 1766
 * or
 * 		use provided dcc_HAL_TIM_PWM_Start_DMA
 *
 */
void dcc_init(void)
{
	DBGMCU->APB1FZ = 0xFFFFFFFF;
	DBGMCU->APB2FZ = 0xFFFFFFFF;

	LCD_config();
	HAL_TIM_Base_Start_IT(&TICK_TIMER);
	HAL_UART_Receive_IT(&DCC_HOST, &System.uart1_rxchar, 1);
	init_dcc_pkt();
	System.dcc_ch1_repeat_cnt = System.dcc_ch1_repeat_number = 1;
	dcc_HAL_TIM_PWM_Start_DMA(&DCC_CH1,TIM_CHANNEL_1,(uint32_t *)System.dcc_ch1_packet,DCC_PKT_LEN*NUM_DCC_PACKET );
	BSP_LED_Init(LED_GREEN);
}

void dcc_process(void)
{
	if ((System.dcc_flags & DCC_DCC1_POWER) == DCC_DCC1_POWER)
		DCC_CH1.Instance->CR1 |= TIM_CR1_CEN;
	else
		DCC_CH1.Instance->CR1 &= ~TIM_CR1_CEN;
	if ((System.dcc_flags & DCC_DCC2_POWER) == DCC_DCC2_POWER)
		DCC_CH2.Instance->CR1 |= TIM_CR1_CEN;
	else
		DCC_CH2.Instance->CR1 &= ~TIM_CR1_CEN;

	if ((System.system & SYSTEM_DCC1_EXPIRED) == SYSTEM_DCC1_EXPIRED)
	{
		System.system &= ~SYSTEM_DCC1_EXPIRED;
		if ((System.dcc_flags & DCC_DCC1_PKTPEND) == DCC_DCC1_PKTPEND)
		{
			if ((System.system & SYSTEM_DCC1_HALFDONE) == SYSTEM_DCC1_HALFDONE)
			{
				memcpy(&System.dcc_ch1_packet,&DCC_Work_Pkt,DCC_PACKET_LEN*2);
				System.system |= SYSTEM_DCC1_HPACKET;
			}
			else
			{
				memcpy(&System.dcc_ch1_packet[DCC_PACKET_LEN],&DCC_Work_Pkt,DCC_PACKET_LEN*2);
				System.system |= SYSTEM_DCC1_FPACKET;
			}
			set_trig(1);
			System.dcc_flags &= ~DCC_DCC1_PKTPEND;
		}
	}
	if ((System.dcc_flags & DCC_DCC1_TXDONE) == DCC_DCC1_TXDONE)
	{
		if ( System.dcc_ch1_repeat_cnt == 0 )
		{
			if ((System.system & SYSTEM_DCC1_HPACKET) == SYSTEM_DCC1_HPACKET)
			{
				memcpy(&System.dcc_ch1_packet,&DCC_Idle_Pkt,DCC_PACKET_LEN*2);
				System.system &= ~SYSTEM_DCC1_HPACKET;
			}
			if ((System.system & SYSTEM_DCC1_FPACKET) == SYSTEM_DCC1_FPACKET)
			{
				memcpy(&System.dcc_ch1_packet[DCC_PACKET_LEN],&DCC_Idle_Pkt,DCC_PACKET_LEN*2);
				System.system &= ~SYSTEM_DCC1_FPACKET;
			}
			System.dcc_ch1_repeat_cnt = System.dcc_ch1_repeat_number;
			System.dcc_flags &= ~DCC_DCC1_PKTPEND;
			set_trig(0);
		}
		else
		{
			System.dcc_ch1_repeat_cnt--;
			System.dcc_flags |= DCC_DCC1_PKTPEND;
		}
		System.dcc_flags &= ~DCC_DCC1_TXDONE;
	}
}


uint8_t state = 0;
void dcc_loop(void)
{
	if ((System.tick_flags & TICK10ms_FLAG) == TICK10ms_FLAG)
	{
#ifdef	ENABLE_LCD
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
#endif
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
	dcc_process();
}
