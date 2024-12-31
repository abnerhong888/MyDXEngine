#include "StringConverter.h"

std::wstring StringConverter::StringToWide(std::string str)
{
	std::wstring wide_string(str.begin(), str.end());
	return wide_string;
}
std::string StringConverter::WideToString(std::wstring str)
{
	std::string l_striing(str.begin(), str.end());
	return l_striing;
}