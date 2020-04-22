// MergeBookmarks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bookmark.h"
#include "bookmarkfile.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 2)
	{
		BookmarkFile bmf1;
		bmf1.SetFileName(argv[1]);
		bmf1.LoadFile();
		bmf1.SortByNameInFolder();
		bmf1.CreateNewFileName();
		bmf1.SaveFile();
	}
	if (argc == 3)
	{
		BookmarkFile bmf1;
		bmf1.SetFileName(argv[1]);
		bmf1.LoadFile();
		bmf1.SortByNameInFolder();

		BookmarkFile bmf2;
		bmf2.SetFileName(argv[2]);
		bmf2.LoadFile();
		bmf2.SortByNameInFolder();

		bmf1.Merge(bmf2);

		bmf1.CreateNewFileName();
		bmf1.SaveFile();
	}

	return 0;
}

