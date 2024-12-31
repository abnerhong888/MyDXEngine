
#ifndef __STRINGCONVERTER_H__
#define __STRINGCONVERTER_H__

#include <string>

class StringConverter
{
public:
	static std::wstring StringToWide(std::string str);
	static std::string WideToString(std::wstring str);
};

#endif