#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;




int main()
{
	std::ifstream f("tests/00.json");
	if (!f.is_open()) {
		std::cerr << "Unable to open file!" << std::endl;
		return 1;
	}
	json data = json::parse(f);
	auto name = data[0]["initial"]["a"];
	std::cout << name << std::endl;
	return 0;
}
