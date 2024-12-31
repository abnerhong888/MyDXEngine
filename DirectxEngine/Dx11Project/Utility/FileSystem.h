#ifndef __FILESYSTEM_H__ 
#define __FILESYSTEM_H__ 

#include "time.h"
#include <string>
#include <vector>  
class FileSystem
{
public:
	static bool isDirExist(const std::wstring Folder);
	static bool isFileExit(const std::wstring File);
	static int  RemoveDir(const std::wstring Folder);
	static bool CreateDir(const std::wstring Folder);
	static bool RemoveFile(const std::wstring File);
	static int  getFilesCount(const std::wstring Folder);
	static int  getFilesCount(const std::wstring Folder, const std::wstring Filter);
	static std::tm *getFileBuiltTime(const std::wstring File);
	static std::vector<std::wstring> getFilesName(const std::wstring Folder);
	static std::vector<std::wstring> getFilesName(const std::wstring Folder, const std::wstring Filter);
	static std::vector<std::wstring> getSortFilesNameByDate(const std::wstring Folder);
	static std::vector<std::wstring> getSortFilesNameByDate(const std::wstring Folder, const std::wstring Filter);
	
	static std::wstring FilterProcess(std::wstring pFilter);
	static int DeleteFiles(std::vector<std::wstring> lists);
};

#endif