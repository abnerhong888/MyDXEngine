#ifndef __DEFINED_H__ 
#define __DEFINED_H__ 

#include <string>
#include <fstream>
#include <comdef.h>

enum ERRTYPE
{
	_INFO,
	_ERROR, 
	_WARNING,
	_EXCEPTION,
	_ERRTYPETOTAL
};

class ErrorLogger
{
public:
	explicit ErrorLogger();
	explicit ErrorLogger(std::string pFileName);
	ErrorLogger(std::string pFolder, std::string pFileName);
	void Log(ERRTYPE type, const char *format, ...);
	void LogHRESULT(ERRTYPE type, HRESULT hr, std::string message);
	void LogFileShouldBeDelete(int days);
	static void MsgBoxLog(std::string message);
	static void MsgBoxLog(HRESULT hr, std::string message);
	static void MsgBoxLog(HRESULT hr, std::wstring message);
	
	void Release();
protected:
	std::string GetSysTimeToString();
	std::string GetSysTimeLog();
	void CreateLogFileAndFolder();
private:
	char buf[2048];
	std::string FileName;
	std::string Folder;
	std::string FullPath;
	std::wfstream fs;
};



class ConsoleLogger
{
public:
	ConsoleLogger();
	static ConsoleLogger &GetIns();
	void ConsolePrint(ERRTYPE type, const char *format, ...);
};

#endif //__DEFINED_H__

#define D_LOGFILE_DELETE_DAYS 1


#if defined(_DEBUG)
#define D_CONSOLE
#endif

#if defined(D_CONSOLE)
#define INFOPRINT(f_, ...) ( ConsoleLogger::GetIns().ConsolePrint(ERRTYPE::_INFO, (f_), ##__VA_ARGS__) )
#define EERRORPRINT(f_, ...) ( ConsoleLogger::GetIns().ConsolePrint(ERRTYPE::_ERROR, (f_), ##__VA_ARGS__) )
#define WARNINGPRINT(f_, ...) ( ConsoleLogger::GetIns().ConsolePrint(ERRTYPE::_WARNING, (f_), ##__VA_ARGS__) )
#define EXCEPTIONPRINT(f_, ...) ( ConsoleLogger::GetIns().ConsolePrint(ERRTYPE::_EXCEPTION,(f_), ##__VA_ARGS__) )
#else
#define INFOPRINT(f_, ...) {}
#define EERRORPRINT(f_, ...) {}
#define WARNINGPRINT(f_, ...) {}
#define EXCEPTIONPRINT(f_, ...) {}
#endif


