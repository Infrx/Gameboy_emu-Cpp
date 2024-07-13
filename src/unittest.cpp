#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

std::ifstream f("v1/00.json");
json data;

int main()
{
	return 0;
}
