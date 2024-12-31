#include "ErrorLogger.h"
#include "FileSystem.h"
#include "StringConverter.h"
#include <stdarg.h>   
#include <ctime>

#include "consoleapi.h"

#define LOGGERFOLDER ".\\Log\\"


const std::string g_ErrTypes[ERRTYPE::_ERRTYPETOTAL] =
{ "[ INFO ] ",  "[ Error ] ", "[ Warning ] ", "[ Exception ] " };

ErrorLogger::ErrorLogger()
{

}

ErrorLogger::ErrorLogger(std::string pFileName)
{
	Folder = LOGGERFOLDER;
	FileName = pFileName + "_" + GetSysTimeToString() + ".txt";
	FullPath = Folder + FileName;
	CreateLogFileAndFolder();
}

ErrorLogger::ErrorLogger(std::string pFolder, std::string pFileName)
{
	Folder = pFolder;
	FileName = pFileName + "_" + GetSysTimeToString() + ".txt";
	FullPath = Folder + FileName;
	CreateLogFileAndFolder();
}

void ErrorLogger::CreateLogFileAndFolder()
{
	if (!FileSystem::isDirExist(StringConverter::StringToWide(Folder)))
	{
		FileSystem::CreateDir(StringConverter::StringToWide(Folder));
	}
	
	fs.open(FullPath, std::fstream::out);
	if (fs.is_open())
	{
		fs.close();
	}
}

void ErrorLogger::Log(ERRTYPE type, const char *format, ...)
{
	fs.open(FullPath, std::fstream::out | std::fstream::app);
	if (!fs.is_open())
		return;

	va_list ap;
	va_start(ap, format);
	int bytes_written = vsnprintf(buf, sizeof(buf), format, ap);
	va_end(ap);

	fs << GetSysTimeLog().c_str() << g_ErrTypes[type].c_str() << buf << std::endl;
	fs.close();
}

void ErrorLogger::LogHRESULT(ERRTYPE type, HRESULT hr, std::string message)
{
	_com_error error(hr);
	_bstr_t bstrt(error.ErrorMessage());
	fs.open(FullPath, std::fstream::out | std::fstream::app);
	if (!fs.is_open())
		return;

	std::string str = message + "-> HRESULT : ";
	fs << GetSysTimeLog().c_str() << g_ErrTypes[type].c_str() << str.c_str() << bstrt << std::endl;
	fs.close();
}

void ErrorLogger::MsgBoxLog(std::string message)
{
	std::string error_message = "Error: " + message;
	MessageBoxA(NULL, error_message.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::MsgBoxLog(HRESULT hr, std::string message)
{
	_com_error error(hr);
	_bstr_t bstrt(error.ErrorMessage());

	std::wstring error_message = L"Error: " + 
		StringConverter::StringToWide(message) + L"\n" + 
		static_cast<std::wstring>(bstrt);

	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

void ErrorLogger::MsgBoxLog(HRESULT hr, std::wstring message)
{
	_com_error error(hr);
	_bstr_t bstrt(error.ErrorMessage());
	std::wstring error_message = L"Error: " + 
		message + L"\n" + 
		static_cast<std::wstring>(bstrt);

	MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
}

std::string ErrorLogger::GetSysTimeToString()
{
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);

	std::string l_time =
		std::to_string(now->tm_year + 1900) + "_" +
		std::to_string(now->tm_mon + 1) + "_" +
		std::to_string(now->tm_mday) + "_" +
		std::to_string(now->tm_hour) + "_" +
		std::to_string(now->tm_min) + "_" +
		std::to_string(now->tm_sec);

	return l_time;
}

std::string ErrorLogger::GetSysTimeLog()
{
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);

	std::string l_time = 
		std::to_string(now->tm_year + 1900) + "/" +
		std::to_string(now->tm_mon + 1) + "/" +
		std::to_string(now->tm_mday) + " " +
		std::to_string(now->tm_hour) + ":" +
		std::to_string(now->tm_min) + ":" +
		std::to_string(now->tm_sec)+ " ";

	return l_time;
}

void ErrorLogger::LogFileShouldBeDelete(int days)
{
	std::wstring folderpath = StringConverter::StringToWide(Folder);
	std::vector<std::wstring> l_list = FileSystem::getSortFilesNameByDate(folderpath, L".txt");

	if (l_list.size() != 0)
	{
		std::tm *NearTime = FileSystem::getFileBuiltTime(l_list[0]);
		int nearday = NearTime->tm_mday;
		int nearmon = NearTime->tm_mon;
		std::tm *FarTime = FileSystem::getFileBuiltTime(l_list[l_list.size() - 1]);
		int farday = FarTime->tm_mday;
		int farmon = FarTime->tm_mon;
		int calculateDays = (nearmon - farmon) * 30 + (nearday - farday);

		if (calculateDays >= days )
		{
			FileSystem::RemoveDir(folderpath);
			Sleep(500);
			CreateLogFileAndFolder();
		}
	}
	
}

void ErrorLogger::Release()
{
	if (fs.is_open())
	{
		fs.close();
	}
}
//////////////////////////////////////////////////////////////////////////

ConsoleLogger::ConsoleLogger()
{
	AllocConsole();
	freopen("CONOUT$", "w+", stdout); // CONIN$ stdin
	setlocale(LC_ALL, ""); // wchar_t enable
}

ConsoleLogger &ConsoleLogger::GetIns()
{
	static ConsoleLogger l_ins;
	return l_ins;
}

void ConsoleLogger::ConsolePrint(ERRTYPE type, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	std::string str = g_ErrTypes[type] + std::string(format)  + "\n";
	vprintf(str.c_str(), ap);
	va_end(ap);
	
}
