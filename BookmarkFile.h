#ifndef BOOKMARKFILE_H
#define BOOKMARKFILE_H
#include <cstdlib>
#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include <locale>
//#include <codecvt>
#include "bookmark.h"
#include <vector>
#include <algorithm>

using namespace std;

class BookmarkFile
{
public:
	BookmarkFile(void);
	void SetFileName(wstring fileName);
	void CreateNewFileName(wstring fileName = L"");
	bool LoadFile();
	void SaveFile();
	void Merge(BookmarkFile &bf);
	void SortByNameInFolder();
public:
	~BookmarkFile(void);
private:
	void CreateListFolders(std::list<std::wstring>& nameOfFolder);
	void CreateNewFolder(list<Bookmark> &bmList, Bookmark bm);
	wstring fileName;
	list<Bookmark> url;//список закладок
	vector<wstring> folders;
};
#endif