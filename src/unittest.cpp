#include "unittest.h"


int main()
{
	Cpu cpu;

	for (int i = 10; i < 25; ++i)
	{
		//json data = openFile("v1/01.json");
		json data = openFile("v1/" + jsonFiles[i]);  //"v1/09.json"
		unitTest(data, cpu);
	}
	

	return 0;
}
