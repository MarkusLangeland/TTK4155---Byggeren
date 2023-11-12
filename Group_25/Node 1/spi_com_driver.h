#pragma once 

void SPI_init(void); 
uint8_t SPI_write(uint8_t cData);
uint8_t SPI_read(void);
void cs_on(void);
void cs_off(void);
