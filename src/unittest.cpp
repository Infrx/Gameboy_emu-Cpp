#include "unittest.h"


int main()
{
	Cpu cpu;
	auto buffer = cpu.readROM("roms/" + blaargRoms[1]);
	for (int i = 0; i<buffer.size(); i++)
	{
		cpu.memory[i] = buffer[i];
		std:
	}
	cpu.writeLog();
	while(true)
	{
		cpu.cycle();
		cpu.writeLog();
	}
	/*
	for (int i = 0; i < 500; ++i)
	{
		//json data = openFile("v1/01.json");
		json data = openFile("v1/" + jsonFiles[i]);  //"v1/09.json"
		unitTest(data, cpu);
		cpu.writeLog();
	}
	*/


	return 0;
}
