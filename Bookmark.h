#ifndef BOOKMARK_H
#define BOOKMARK_H
#include "stdafx.h"
#include <cstdlib>
#include <string>

using namespace std;

class Bookmark
{
public:
	enum HEAD3 {OTHER, HEAD_BEG, HREF, HEAD_END};
	Bookmark(wstring str);
	wstring GetSourceStr();
	wstring GetFolder();
	wstring GetHref();
	void SetSourceStr(wstring str);
	void SetFolderName(wstring str);
	bool IsFolderEmpty();
	bool IsHrefEmpty();
	HEAD3 recordType;
	friend bool operator== (const Bookmark &b1, const Bookmark &b2);
	friend bool operator< (const Bookmark &b1, const Bookmark &b2);
public:
	~Bookmark(void);
private:
	void SplitSourceStr();
	wstring sourceStr;
	wstring href;
	wstring folder;
	wstring bmDate;
};
#endif