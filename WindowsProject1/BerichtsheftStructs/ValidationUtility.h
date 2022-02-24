#include <string>

namespace validationUtility {
	bool isValid(const std::string& datestring);
	bool IsEmpty(const std::string& datestring);
	bool isFormatInvalid(const std::string& datestring);
	bool isOutofRange(const std::string& datestring);
	bool isLeapYear(const std::string& datestring);
}

