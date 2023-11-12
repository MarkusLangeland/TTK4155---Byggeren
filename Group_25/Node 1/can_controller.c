#include "can_controller.h"

void can_init(){
	
	mcp2515_init();
		
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, CONFIG<<5);
	
	uint8_t BRP = 4;
	
	//define propagating segement, and baudrate prescaler 
	mcp2515_write(MCP_CNF1, (BRP-1)); //Remove 1 such that the Baudrate prescaler is BRP and not BRP + 1
	mcp2515_write(MCP_CNF2, ((1 << 7) | ((ps1-1) << 3) | (proqSeg-1) ));
	mcp2515_write(MCP_CNF3, 5);

	//set to mode
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, NORMAL<<5);
}

void can_send(CAN_MESSAGE* message){
	mcp2515_write(MCP_TXB0SIDH, message->id / 8);
	mcp2515_write(MCP_TXB0SIDL, (message->id % 8) << 5);
	mcp2515_write(MCP_TXB0DLC, message->data_length);
	
	
	for (uint8_t i = 0; i < message->data_length; ++i) {
		mcp2515_write(MCP_TXB0D0 + i, message->data[i]);
	}
	
	mcp2515_request_to_send();
}


bool can_has_message() {
	return mcp2515_read(MCP_CANINTF) & MCP_RX0IF || mcp2515_read(MCP_CANINTF) & MCP_RX1IF;
}

void can_recieve(CAN_MESSAGE* message){
	if(message == NULL){
		
	}
	
	if (mcp2515_read(MCP_CANINTF) & MCP_RX0IF){
		message->id = (mcp2515_read(MCP_RXB0SIDL) >> 5) + (mcp2515_read(MCP_RXB0SIDH) << 3);
		
		message->data_length = mcp2515_read(MCP_RXB0DLC);
		
		for (int i = 0; i < message->data_length; ++i){
			message->data[i] = mcp2515_read(MCP_RXB0D0 + i);
		}
		return;
	}
	
	if (mcp2515_read(MCP_CANINTF) & MCP_RX1IF){
		message->id = (mcp2515_read(MCP_RXB1SIDL) >> 5) + (mcp2515_read(MCP_RXB1SIDH) << 3);
		
		message->data_length = mcp2515_read(MCP_RXB1DLC);
		
		for (int i = 0; i < message->data_length; ++i){
			message->data[i] = mcp2515_read(MCP_RXB1D0 + i);
		}
		return;
	}
}
