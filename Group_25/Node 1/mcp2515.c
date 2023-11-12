#include "mcp2515.h"

//taken from lecture slides 

bool mcp2515_init(){ 

	SPI_init();
	mcp2515_reset();
	
	uint8_t value = mcp2515_read(MCP_CANSTAT);
	
	
	if((value & MODE_MASK) != MODE_CONFIG){
		return true;
	}
	
	return false;
}

uint8_t mcp2515_read(uint8_t address){
	cs_low();
	cs_on(); //Lowering CS pin
	
	SPI_write(MCP_READ); //Read instruction from the SPI instruction set 
	SPI_write(address); //Entering the address 
	uint8_t data = SPI_read();  //retrieving the data from address	
	cs_low();

		
	return data; 
}

void mcp2515_write(uint8_t address, uint8_t data){
	
	cs_low();
	cs_on(); //Lowering CS pin
	
	SPI_write(MCP_WRITE); //Write instruction from the SPI instruction set 
	SPI_write(address); 
	SPI_write(data); 
	
	cs_low();
	
}

void mcp2515_reset(void){
	cs_low();
	cs_on(); //Lowering the CS pin
	
	
	SPI_write(MCP_RESET); 
	
	cs_low(); //Raising the CS pin
}

void mcp2515_request_to_send(void){
	
	cs_low();
	cs_on(); //Lowering CS pin
	
	SPI_write(MCP_RTS_TX0);
	
	cs_low(); //Raising CS pin
}

uint8_t mcp2515_read_status(void){
	
	cs_low();
	cs_on(); //Lowering CS pin

	SPI_write(MCP_READ_STATUS); 
	uint8_t status = SPI_read(); 
	
	cs_low(); //Raising CS pin
	
	return status; 
}


void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
	
	cs_low();
	cs_on();
	
	SPI_write(MCP_BITMOD); 
	SPI_write(address);
	SPI_write(mask);
	SPI_write(data);
	
	cs_low(); //Raising CS pin
}
