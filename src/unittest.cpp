#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <cpu.h>
using json = nlohmann::json;




int main()
{
	std::ifstream f("v1/09.json");
	if (!f.is_open()) {
		std::cerr << "Unable to open file!" << std::endl;
		return 1;
	}
	json data = json::parse(f);
	//auto name = data[0]["initial"]["a"];

	Cpu cpu;

	
	for(int idx = 0; idx <100; ++idx)
	{
		uint16_t memidx = 0;
		cpu.r.a = data[idx]["initial"]["a"];
		cpu.r.b = data[idx]["initial"]["b"];
		cpu.r.c = data[idx]["initial"]["c"];
		cpu.r.d = data[idx]["initial"]["d"];
		cpu.r.e = data[idx]["initial"]["e"];
		cpu.r.f = data[idx]["initial"]["f"];
		cpu.r.h = data[idx]["initial"]["h"];
		cpu.r.l = data[idx]["initial"]["l"];
		cpu.pc = data[idx]["initial"]["pc"];
		cpu.sp = data[idx]["initial"]["sp"];
		memidx = data[idx]["initial"]["ram"][0][0];
		cpu.memory[memidx] = data[idx]["initial"]["ram"][0][1];
		
		//cpu.ADD_HL_r16(cpu.r.bc);
		cpu.cycle();

		if (cpu.r.a != data[idx]["final"]["a"])
			std::cout << "a is wrong at test " << idx << std::endl;
		if (cpu.r.b != data[idx]["final"]["b"])
			std::cout << "b is wrong at test " << idx << std::endl;
		if (cpu.r.c != data[idx]["final"]["c"])
			std::cout << "c is wrong at test " << idx << std::endl;
		if (cpu.r.d != data[idx]["final"]["d"])
			std::cout << "d is wrong at test " << idx << std::endl;
		if (cpu.r.e != data[idx]["final"]["e"])
			std::cout << "f is wrong at test " << idx << std::endl;
		if (cpu.r.f != data[idx]["final"]["f"])
			std::cout << "f is wrong at test " << idx << std::endl;
		if (cpu.r.h != data[idx]["final"]["h"])
			std::cout << "h is wrong at test " << idx << std::endl;
		if (cpu.r.l != data[idx]["final"]["l"])
			std::cout << "l is wrong at test " << idx << std::endl;
		if (cpu.pc != data[idx]["final"]["pc"])
			std::cout << "pc is wrong at test " << idx << std::endl;
		if (cpu.sp != data[idx]["final"]["sp"])
			std::cout << "sp is wrong at test " << idx << std::endl;
			int x = 4;
	}

	return 0;
}
