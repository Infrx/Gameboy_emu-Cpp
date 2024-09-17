#include "unittest.h"


int main()
{
	MMU mmu([]() {});
	Cpu cpu(mmu);
	mmu = MMU([&cpu]() { cpu.incrementMCycle(); });
	auto buffer = cpu.readROM("roms/" + blaargRoms[2]);
	for (int i = 0; i<buffer.size(); i++)
	{
		cpu.memory[i] = buffer[i];
	}
	//json data = openFile("v1/cd.json");
	//unitTest(data, cpu);
	//cpu.writeLog();
	long int counter{};
	while(true)
	{
		++counter;
		if (counter == 3500000)
			break;
		cpu.writeLog();
		cpu.cycle();


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
