#include <string>

namespace validationUtility {
	bool isValid(const std::string& datestring);
	bool isEmpty(const std::string& datestring);
	bool isFormatValid(const std::string& datestring);
	bool isInRange(const std::string& datestring);
	bool isLeapYear(const std::string& datestring);
	bool isDayWayToLarge(const std::string & datestring);
	bool isMonthWayToLarge(const std::string & datestring);

	/*
	enum FailureState
	{
		empty,
		valid,
		parser_invalid_format,
		out_of_range
	};

	FailureState GetFailureState(const std::string & datestring);
	*/
}

