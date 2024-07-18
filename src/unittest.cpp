#include "unittest.h"


int main()
{
	Cpu cpu;

	for (int i = 0; i < 99; ++i)
	{
		json data = openFile("v1/" + jsonFiles[i]);  //"v1/09.json"
		unitTest(data, cpu);
	}
	

	return 0;
}
