/*
 * dcc_main.h
 *
 *  Created on: Aug 16, 2023
 *      Author: fil
 */

#ifndef APPLICATION_DCC_MAIN_H_
#define APPLICATION_DCC_MAIN_H_

extern	ADC_HandleTypeDef hadc3;
extern	CRC_HandleTypeDef hcrc;
extern	DCMI_HandleTypeDef hdcmi;
extern	DMA2D_HandleTypeDef hdma2d;
extern	I2C_HandleTypeDef hi2c1;
extern	I2C_HandleTypeDef hi2c3;
extern	LTDC_HandleTypeDef hltdc;
extern	QSPI_HandleTypeDef hqspi;
extern	RTC_HandleTypeDef hrtc;
extern	SAI_HandleTypeDef hsai_BlockA2;
extern	SAI_HandleTypeDef hsai_BlockB2;
extern	SD_HandleTypeDef hsd1;
extern	SPDIFRX_HandleTypeDef hspdif;
extern	SPI_HandleTypeDef hspi2;
extern	TIM_HandleTypeDef htim1;
#define	DCC_CH1				htim1
extern	TIM_HandleTypeDef htim2;
#define	DCC_CH2				htim2
extern	TIM_HandleTypeDef htim3;
extern	TIM_HandleTypeDef htim5;
extern	TIM_HandleTypeDef htim7;
#define	TICK_TIMER			htim7
extern	TIM_HandleTypeDef htim8;
extern	TIM_HandleTypeDef htim12;
extern	DMA_HandleTypeDef hdma_tim1_ch1;
#define	DCC_DMA_CH1				hdma_tim1_ch1
extern	UART_HandleTypeDef huart1;
#define	DCC_HOST			huart1
extern	UART_HandleTypeDef huart6;
#define	HUART6			huart6
extern	SDRAM_HandleTypeDef hsdram1;

#define	DCC_HOST_MAX_LEN		64
#define	DCC_PREAMBLE_LEN		16
#define	DCC_ADDRESS_LEN			8
#define	DCC_DATA_LEN			8
#define	DCC_ECC_LEN				8
#define	DCC_PKT_LEN				(DCC_PREAMBLE_LEN+1+DCC_ADDRESS_LEN+1+DCC_DATA_LEN+1+DCC_ECC_LEN+1)
#define	PULSE100uS				100
#define	PULSE58uS				58
#define	DCC_0					PULSE100uS
#define	DCC_1					PULSE58uS

typedef struct {
	uint32_t		preamble[16];
	uint32_t		separator0;
	uint32_t		address[8];
	uint32_t		separator1;
	uint32_t		data[8];
	uint32_t		separator2;
	uint32_t		ecc[8];
	uint32_t		endpacket;
}DCC_Pkt_TypeDef;
extern	DCC_Pkt_TypeDef	DCC_Idle_Pkt;
extern	DCC_Pkt_TypeDef	DCC_Reset_Pkt;
extern	DCC_Pkt_TypeDef	DCC_Work_Pkt;

#define	DCC_PACKET_LEN		(DCC_PREAMBLE_LEN+1+DCC_ADDRESS_LEN+1+DCC_DATA_LEN+1+DCC_ECC_LEN+1)
#define	NUM_DCC_PACKET		2

typedef struct {
	uint8_t			system;
	uint8_t			tick_flags;
	uint8_t			tick_counter;
	uint8_t			dcc_flags;
	uint8_t			uart1_flags;
	uint8_t			uart1_rxchar;
	uint8_t			uart1_rxbuf[DCC_HOST_MAX_LEN];
	uint8_t			uart1_rxindex;
	uint8_t			uart1_txbuf[DCC_HOST_MAX_LEN*4];
	uint8_t			uart1_txlen;
	uint32_t		dcc_ch1_packet[DCC_PACKET_LEN*NUM_DCC_PACKET];
	uint8_t			dcc_ch1_packet_index;
	uint32_t		dcc_ch2_packet[DCC_PACKET_LEN*NUM_DCC_PACKET];
	uint8_t			dcc_ch2_packet_index;
}System_TypeDef;
extern	System_TypeDef	System;

/* system */
#define	SYSTEM_DCC1_HALFDONE	0x20
#define	SYSTEM_DCC2_HALFDONE	0x10
#define	SYSTEM_DCC1_DMADONE		0x08
#define	SYSTEM_DCC2_DMADONE		0x04
/* tick_flags */
#define	TICK10ms_FLAG			0x80
/* uart1_flags */
#define	UART1_OPENFLAG			0x04
#define	UART1_BUF				0x02
#define	UART1_CH				0x01
/* dcc_flags */
#define	DCC_DCC1_POWER			0x80
#define	DCC_DCC1_RESET			0x40
#define	DCC_DCC2_POWER			0x08
#define	DCC_DCC2_RESET			0x04
#define	DCC_DCC1_PKTPEND		0x80
#define	DCC_DCC2_PKTPEND		0x40

extern	void dcc_init(void);
extern	void dcc_loop(void);

#endif /* APPLICATION_DCC_MAIN_H_ */
