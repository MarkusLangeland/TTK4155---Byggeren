#pragma once 

#include "stdint.h"
#include "spi_com_driver.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include "mcp2515.h"
#include "can_controller.h"

enum MODES {
	NORMAL, 
	SLEEP,
	LOOPBACK,
	LISTENONLY,
	CONFIG,
};

typedef struct
{
	uint16_t id;
	char data_length;
	signed char data[8];
} CAN_MESSAGE;

enum can_configs {
	sync = 1,
	proqSeg = 1,
	ps1 = 8,
	ps2 = 6,
	sjw = 1,
	brp_node1 = 8,
	brp_node2 = 42
};

enum BAUD_RATE {
	CAN_BAUD_100000 = 100000,
	CAN_BAUD_125000 = 125000,
	CAN_BAUD_250000 = 250000,
	CAN_BAUD_500000 = 500000
};

void can_init(); 
void can_send(CAN_MESSAGE* message); 
void can_recieve(CAN_MESSAGE* message); 
bool can_has_message();

#define F_OSC 16000000
#define TQ 8 //Set a time quanta

#define MCP_TXB2SIDH 0x51
#define MCP_TXB2SIDL 0x52
#define MCP_TXB2DLC 0x55
#define MCP_TXB2D0 0x56
#define MCP_RXB0SIDL 0x61
#define MCP_RXB0DLC 0x65
#define MCP_RXB0D0 0x66
#define MCP_RXB1SIDL 0x72
#define MCP_RXB1DLC 0x75
#define MCP_RXB1D0 0x76

#define MCP_TXB0D0 0x36

#define MCP_TXB0SIDL 0x32
#define MCP_TXB0SIDH 0x31
#define MCP_TXB0DLC 0x35

#define MCP_RXM0 0x20
#define MCP_RXM1 0x40

#define MCP_RXB0SIDH	0x61 
#define MCP_RXB0SIDL    0x62

#define MCP_RXB1SIDH	0x71
#define MCP_RXB1SIDL    0x72
#define MCP_RXB0DLC     0x65
#define MCP_RXB0D0      0X66
#define MCP_RXB1DLC     0x75
#define MCP_RXB1D0      0X76





