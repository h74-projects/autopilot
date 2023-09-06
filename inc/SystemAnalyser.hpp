#ifndef SYSTEM_ANALYSER_HPP
#define SYSTEM_ANALYSER_HPP

#include <string>

namespace util {
class SystemAnalyser {
public: 
	SystemAnalyser();

	virtual void RunCommand(const char * command);
	virtual void DisplayOutput();
	virtual ~SystemAnalyser();

private:
	std::string outputStore;
	void StoreOutput(std::string result);
};

} // namespace util


#endif // SYSTEM_ANALYSER_HPP
