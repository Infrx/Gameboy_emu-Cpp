#pragma once
#include <cstdint>
#include <iostream>
class Cpu
{
public:
	uint8_t opcode{0};
	uint8_t memory[65536];

	void executeOpcode();
	void executeCBOpcode();
private:
	uint8_t mem_read(const uint64_t adr);
	void mem_write(const uint64_t adr, uint8_t value);


};