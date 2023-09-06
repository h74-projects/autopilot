#include <iostream>
#include <memory>
#include "SystemAnalyser.hpp"

namespace util {

SystemAnalyser::SystemAnalyser()
{
}

void SystemAnalyser::RunCommand(const char * command)
{
	std::array<char, 128> buffer;
	std::string result;
	
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	StoreOutput(result);
}

void SystemAnalyser::StoreOutput(std::string result)
{
	outputStore = result;
}

void SystemAnalyser::DisplayOutput()
{
	std::cout << outputStore << std::endl;
}

SystemAnalyser::~SystemAnalyser()
{
}

} // namespace util
