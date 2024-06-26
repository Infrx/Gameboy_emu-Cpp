#pragma once
#include <cstdint>
#include <iostream>
#include "register.h"



class Cpu
{
public:
	uint8_t opcode{0};
	uint8_t cb_opcode{0};
	uint8_t memory[65536];
	bool prefixFlag;
	void fetchOpcode();
	void decodeOpcode(uint8_t opcode, uint8_t cb_opcode, bool prefixFlag);
	void executeOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q);
	void executeCBOpcode(uint8_t x, uint8_t y, uint8_t z, uint8_t p, uint8_t q);
	
private:
	uint8_t mem_read(const uint16_t adr);
	void mem_write(const uint16_t adr, uint8_t value);
	Registers r;

};