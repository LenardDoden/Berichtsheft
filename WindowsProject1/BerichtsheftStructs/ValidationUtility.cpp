#include "ValidationUtility.h"
#include <regex>
#include <iostream>


enum FailureState
	{
		empty,
		valid,
		parser_invalid_format,
		out_of_range
	};


std::regex regex_date("(\\d{4})-(\\d{2})-(\\d{2})");
std::smatch match;

std::time_t t = std::time(0);
std::tm* now = std::localtime(&t);
int datumaktuell = now->tm_year + 1900;

bool validationUtility::isDayWayToLarge(const std::string & datestring)
{
	std::regex regex_date("(\\d{4})-(\\d{2})-(\\d{2})");
	std::smatch match;

	std::string input = datestring;

	if (std::regex_match(input, match, regex_date))
	{
		if (std::stoi(match[3]) > 31)
		{
			return true;
		}

		return false;
	}

	return false;
}

bool validationUtility::isMonthWayToLarge(const std::string & datestring)
{
	std::regex regex_date("(\\d{4})-(\\d{2})-(\\d{2})");
	std::smatch match;

	std::string input = datestring;

	if (std::regex_match(input, match, regex_date))
	{
		if (std::stoi(match[2]) > 12)
		{
			return true;
		}

		return false;
	}

	return false;
}

//IsLeapYear
bool validationUtility::isLeapYear(const std::string & datestring)
{
	std::regex regex_date("(\\d{4})-(\\d{2})-(\\d{2})");
	std::smatch match;

	std::string input = datestring;

	if (std::regex_match(input, match, regex_date))
	{

		if (std::stoi(match[1]) % 400 == 0 || std::stoi(match[1]) % 4 == 0 && std::stoi(match[1]) % 100 != 0)
		{
			return true;
			std::cout << "Schaltjahr!" << std::endl;
		}
		return false;
	}
	return  false;
}

//GetFailureState
FailureState GetFailureState(const std::string & datestring)
{
	return FailureState::empty;
	return FailureState::out_of_range;
	return FailureState::parser_invalid_format;

	std::string input = datestring;

	if (std::regex_match(input, match, regex_date))
	{
		return FailureState::valid;
	}

	std::runtime_error{ "Falsches Format! Bitte nochmal in folgendem Format eingeben: (YYYY-MM-DD)" };
}


//isValid
bool validationUtility::isValid(const std::string & datestring)
{

	const auto failurestate = FailureState();
	
	return GetFailureState(datestring) == valid;

}

//isEmpty
bool validationUtility::isEmpty(const std::string& datestring)
{
	if (datestring.length() == 0)
	{
		return true;
	}

	return false;
}


//isFormatInvalid
bool validationUtility::isFormatValid(const std::string& datestring)
{
	std::string input = datestring;

	if (std::regex_match(input, match, regex_date))
	{
		return true;
	}
	throw std::runtime_error{ "Falsches Format! Bitte nochmal in folgendem Format eingeben: (YYYY-MM-DD)" };
}

//isOutofrange
bool validationUtility::isInRange(const std::string& datestring)
{
	int minimalertag = 28;

	std::string input = datestring;

	std::regex regex_date("(\\d{4})-(\\d{2})-(\\d{2})");
	std::smatch match;
	
	//dict für anzahl tage dazu passende und monate

	/*
	//Schaltjahr
	if (isLeapYear(datestring) == true)
	{
		minimalertag = 29;
	}
	*/
	if (std::regex_match(input, match, regex_date))
	{
		if (std::stoi(match[2]) > 0 
		&& std::stoi(match[2]) < 13)
		{
			if (std::stoi(match[3]) > 0 &&
				std::stoi(match[3]) < 32)
			{
				if (std::stoi(match[1]) >= 2020
					&& (std::stoi(match[1]) <= datumaktuell))
				{
					return true;
				}
				return false;
			}
			return false;
		}
		return false;

	}
	return false;
	std::runtime_error{ "Ungültig" };
}


		/*
		if (std::stoi(match[3]) > 0 &&
		std::stoi(match[3]) < 32)
		{
			std::cout << "Tag passt nicht, nicht zwischen 01 und 31" << std::endl;
			return true;
		}

		if (std::stoi(match[1]) >= 2020 
		&& (std::stoi(match[1]) <= datumaktuell))
		{
			std::cout << "Jahrezahl passt nicht, nicht zwischen 2020 und " + datumaktuell << std::endl;
			return true;
		}
		*/
 

//bool validationUtility::isValid(const std::string& datestring)
//{
//	std::regex regex_date("(\\d{4})-(\\d{2})-(\\d{2})");
//
//	std::string input = datestring;
//	std::smatch match;
//
//	std::time_t t = std::time(0);
//	std::tm* now = std::localtime(&t);
//	int datumaktuell = now->tm_year + 1900;
//	bool format;
//
//
//	if (std::regex_match(input, match, regex_date)) {
//		std::cout << match[1] << " " << match[2] << " " << match[3] << "\n" << "\n";
//		if (std::stoi(match[1]) % 400 == 0 || std::stoi(match[1]) % 4 == 0 && std::stoi(match[1]) % 100 != 0)
//
//
//		{
//			std::cout << "Schaltjahr!" << std::endl;
//			format = true;
//		}
//		else
//		{
//			std::cout << "kein Schaltjahr" << std::endl;
//			format = false;
//		}
//
//		if (std::stoi(match[2]) > 0 && std::stoi(match[2]) < 13)
//		{
//			std::cout << "Monat passt" << std::endl;
//			format = true;
//		}
//		else
//		{
//			std::cout << "Monat passt nicht, nicht zwischen 01 und 12" << std::endl;
//			format = false;
//		}
//
//		if (std::stoi(match[3]) > 0 && std::stoi(match[3]) < 32)
//		{
//			std::cout << "Tag passt" << std::endl;
//			format = true;
//		}
//		else
//		{
//			std::cout << "Tag passt nicht, nicht zwischen 01 und 31" << std::endl;
//			format = false;
//		}
//
//		if (std::stoi(match[1]) >= 2020 && (std::stoi(match[1]) <= datumaktuell))
//		{
//			std::cout << "Datum passt" << std::endl;
//			format = true;
//		}
//		else
//		{
//			std::cout << "Jahrezahl passt nicht, nicht zwischen 2020 und " + datumaktuell << std::endl;
//			format = false;
//		}
//	}
//
//	else
//	{
//		std::cout << "Falsches Format! Bitte nochmal in folgendem Format eingeben: (YYYY-MM-DD)";
//		format = false;
//	}
//
//	if (format = false)
//	{
//		return true;
//	}
//
//
//
//	else
//	{
//		return false;
//	}
//}