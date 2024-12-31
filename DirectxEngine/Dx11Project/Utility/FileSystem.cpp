#include "FileSystem.h"
#include <filesystem>
#include <algorithm>
#include <iterator>
namespace fs = std::experimental::filesystem;

bool FileSystem::isDirExist(const std::wstring Folder)
{
	return fs::is_directory(Folder);
}

bool FileSystem::isFileExit(const std::wstring File)
{
	return fs::exists(File);
}

int FileSystem::RemoveDir(const std::wstring Folder)
{
	// return N file or directories has been delete recursively
	return static_cast<int>(fs::remove_all(Folder));
}

bool FileSystem::CreateDir(const std::wstring Folder)
{
	return fs::create_directory(Folder);
}

bool FileSystem::RemoveFile(const std::wstring File)
{
	return fs::remove(File);
}

int FileSystem::getFilesCount(const std::wstring Folder)
{
	int cnt = 0;
	fs::directory_iterator it = fs::directory_iterator(Folder);
	for (const auto & entry : fs::directory_iterator(Folder))
	{
		if (!fs::is_directory(entry.path()))
		{
			cnt++;
		}
	}
	return cnt;
}

int FileSystem::getFilesCount(const std::wstring Folder, const std::wstring Filter)
{
	int cnt = 0;
	fs::directory_iterator it = fs::directory_iterator(Folder);
	std::wstring filter(FilterProcess(Filter));
	for (const auto & entry : fs::directory_iterator(Folder))
	{
		if (!fs::is_directory(entry.path()) && 
			entry.path().extension() == filter)
		{
			cnt++;
		}
	}
	return cnt;
}

std::tm *FileSystem::getFileBuiltTime(const std::wstring File)
{
	auto ftime = fs::last_write_time(File);
	std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
	std::tm *time = std::localtime(&cftime);
	return time;
}

std::vector<std::wstring> FileSystem::getFilesName(const std::wstring Folder)
{
	std::vector<std::wstring> l_list;
	fs::directory_iterator it = fs::directory_iterator(Folder);
	for (const auto & entry : fs::directory_iterator(Folder))
	{
		if (!fs::is_directory(entry.path()))
		{
			l_list.emplace_back(entry.path());
		}
	}
	return l_list;
}

std::vector<std::wstring> FileSystem::getFilesName(const std::wstring Folder, const std::wstring Filter)
{
	std::vector<std::wstring> l_list;
	fs::directory_iterator it = fs::directory_iterator(Folder);
	std::wstring filter(FilterProcess(Filter));

	for (const auto & entry : fs::directory_iterator(Folder))
	{
		if (!fs::is_directory(entry.path()) &&
			entry.path().extension() == filter)
		{
			l_list.emplace_back(entry.path());
		}
	}
	return l_list;
}

std::vector<std::wstring> FileSystem::getSortFilesNameByDate(const std::wstring Folder)
{
	std::vector<std::wstring> l_list;
	using myPair = std::pair<std::wstring, std::time_t>;

	fs::directory_iterator it = fs::directory_iterator(Folder);

	std::vector< myPair >l_listNameAndTime;
	for (const auto & entry : fs::directory_iterator(Folder))
	{
		if (!fs::is_directory(entry.path()))
		{
			auto ftime = fs::last_write_time(entry.path());
			std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
			l_listNameAndTime.push_back(std::make_pair(entry.path(), cftime));
		}
	}
	
	auto cmp = [&](myPair t1, myPair t2) ->bool
	{
		return t1.second > t2.second;
	};
	std::sort(l_listNameAndTime.begin(), l_listNameAndTime.end(), cmp);
	// pair to list
	std::transform(
		l_listNameAndTime.begin(), 
		l_listNameAndTime.end(), 
		std::back_inserter(l_list),
		[&](myPair &p) {return p.first; });

	return l_list;
}

std::vector<std::wstring> FileSystem::getSortFilesNameByDate(const std::wstring Folder, const std::wstring Filter)
{
	std::vector<std::wstring> l_list;
	using myPair = std::pair<std::wstring, std::time_t>;

	fs::directory_iterator it = fs::directory_iterator(Folder);

	std::vector< myPair >l_listNameAndTime;

	std::wstring filter(FilterProcess(Filter));

	for (const auto & entry : fs::directory_iterator(Folder))
	{
		if (!fs::is_directory(entry.path()) &&
			entry.path().extension() == filter
			)
		{
			auto ftime = fs::last_write_time(entry.path());
			std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
			l_listNameAndTime.push_back(std::make_pair(entry.path(), cftime));
		}
	}

	auto cmp = [&](myPair t1, myPair t2) ->bool
	{
		return t1.second > t2.second;
	};
	std::sort(l_listNameAndTime.begin(), l_listNameAndTime.end(), cmp);
	// pair to list
	std::transform(
		l_listNameAndTime.begin(),
		l_listNameAndTime.end(),
		std::back_inserter(l_list),
		[&](myPair &p) {return p.first; });

	return l_list;
}

std::wstring FileSystem::FilterProcess(std::wstring pFilter)
{
	std::wstring l_Filter = pFilter;
	std::size_t found = l_Filter.find_first_of(L"*");
	if (found != std::string::npos)
	{
		l_Filter = l_Filter.substr(found + 1, l_Filter.size() - 1);
	}
	return l_Filter;
}

int FileSystem::DeleteFiles(std::vector<std::wstring> lists)
{
	int cnt = 0;
	for (std::wstring path : lists)
	{
		cnt += static_cast<int>(FileSystem::RemoveFile(path));
	}
	return cnt;
}