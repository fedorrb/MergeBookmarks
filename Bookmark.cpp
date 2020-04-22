#include "StdAfx.h"
#include "Bookmark.h"

//constructor
Bookmark::Bookmark(wstring str)
{
	SetSourceStr(str);
}
//initialize
void Bookmark::SetSourceStr(wstring str)
{
	sourceStr = str;
	SplitSourceStr();
}
//divide the input period into parts href, folder, bmDate
void Bookmark::SplitSourceStr()
{
	folder.clear();
	href.clear();
	bmDate.clear();
	recordType = OTHER;
	wstring folder_key(L"</H3>");//папка
	size_t end = sourceStr.rfind(folder_key);
	size_t beg = wstring::npos;
	if(end != wstring::npos)
	{
		beg = sourceStr.rfind(L">", end);
		if(beg != wstring::npos && beg < end)
		{
			folder = sourceStr.substr(beg + 1, end - beg - 1);
			recordType = HEAD_BEG;
		}
	}

	if(recordType == OTHER) {
		wstring end_key(L"</DL><p>");//head end
		beg = sourceStr.find(end_key);
		if(beg != wstring::npos)
		{
			recordType = HEAD_END;
		}
	}

	if(recordType == OTHER) {
		wstring href_key(L"<DT><A HREF=");//url
		wstring date_key(L" ADD_DATE=");//date
		beg = sourceStr.find(href_key);
		if(beg != wstring::npos)
		{
			beg = beg + href_key.length() + 1;
			end = sourceStr.find(date_key);
			if(end != wstring::npos && end > beg)
			{
				href = sourceStr.substr(beg, end - beg - 1);
				beg = end + date_key.length() + 1;
				bmDate = sourceStr.substr(beg, 10);
				recordType = HREF;
			}
		}
	}
}
//
wstring Bookmark::GetSourceStr()
{
	return this->sourceStr;
}
//
wstring Bookmark::GetFolder()
{
	return this->folder;
}
//
wstring Bookmark::GetHref()
{
	return this->href;
}
//is there a folder name
bool Bookmark::IsFolderEmpty()
{
	return(folder.empty());
}
bool Bookmark::IsHrefEmpty()
{
	return(href.empty());
}
//
void Bookmark::SetFolderName(wstring str)
{
	folder = str;
}
//destructor
Bookmark::~Bookmark(void)
{
}

bool operator== (const Bookmark &b1, const Bookmark &b2)
{
	return (b1.href == b2.href);
}

bool operator< (const Bookmark& b1, const Bookmark& b2)
{
	if (b1.folder < b2.folder)
	{
		return true;
	} else if (b1.folder == b2.folder)
	{
		if (b1.href < b2.href)
			return true;
		else
			return false;
	}
	else
		return false;
}