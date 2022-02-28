#include <string>

namespace validationUtility {
	bool isValid(const std::string& datestring);
	bool IsEmpty(const std::string& datestring);
	bool isFormatValid(const std::string& datestring);
	bool isOutofRange(const std::string& datestring);
	bool isLeapYear(const std::string& datestring);

	enum FailureState
	{
		empty,
		valid,
		parser_invalid_format,
		out_of_range
	};

	FailureState GetFailureState(const std::string & datestring);
}

