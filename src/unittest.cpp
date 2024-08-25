#include "unittest.h"


int main()
{
	Cpu cpu;

	for (int i = 0; i < 500; ++i)
	{
		//json data = openFile("v1/01.json");
		json data = openFile("v1/" + jsonFiles[i]);  //"v1/09.json"
		unitTest(data, cpu);
		std::cout << "hello" << std::endl;
	}
	return 0;
}
