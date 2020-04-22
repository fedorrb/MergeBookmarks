#include "StdAfx.h"
#include "BookmarkFile.h"

BookmarkFile::BookmarkFile(void)
{
	url.clear();
	fileName.clear();
	folders.clear();
}

BookmarkFile::~BookmarkFile(void)
{
}

void BookmarkFile::SetFileName(wstring fileName)
{
	this->fileName = fileName;
}

void BookmarkFile::CreateNewFileName(wstring fileName)
{
	if(fileName.size())
	{
		this->fileName = fileName;
	}
	else
	{
		size_t end = this->fileName.find_last_of(L".");
		if(end != wstring::npos)
		{
			this->fileName = this->fileName.substr(0, end) + L"_NEW.HTML";
		}
	}
}

bool BookmarkFile::LoadFile()
{
	bool result = false;
	folders.clear();
	size_t pos = 0;
	if(fileName.length() > 3) {
		wifstream bmFile;
		bmFile.open(fileName.c_str());
		if(bmFile.is_open()) {
			wstring str;
			while(getline(bmFile, str))
			{
				Bookmark *bm = new Bookmark(str);
				if((*bm).recordType == (*bm).HEAD_BEG) {
					folders.push_back((*bm).GetFolder());
				}
				if((*bm).recordType == (*bm).HEAD_END) {
					if(folders.size())
						folders.pop_back();
				}
				//if((*bm).recordType == (*bm).HREF) {
					//(*bm).SetFolderName(folder);
				//}
				if ((*bm).IsFolderEmpty())
				{
					//if ((*bm).IsHrefEmpty == false)
					{
						pos = folders.size();
						if(pos)
							(*bm).SetFolderName(folders.at(pos - 1));
					}
				}
				url.push_back(*bm);
			}
			result = true;
			bmFile.close();
		}
	}
	return result;
}

void BookmarkFile::SaveFile()
{
	wofstream bmFile;
	bmFile.open(fileName.c_str());
	list<Bookmark>::iterator it;
	for (it = url.begin(); it != url.end(); ++it)
	{
		bmFile << (*it).GetSourceStr() << endl;
	}
	bmFile.flush();
	bmFile.close();
}

void BookmarkFile::CreateListFolders(std::list<std::wstring>& nameOfFolder)
{
	nameOfFolder.clear();
	list<Bookmark>::iterator it;
	for (it = url.begin(); it != url.end(); ++it)
	{
		if ((*it).IsFolderEmpty() == false)
			nameOfFolder.push_back((*it).GetFolder());
	}
	nameOfFolder.sort();
	nameOfFolder.unique();
}

void BookmarkFile::CreateNewFolder(list<Bookmark>& bmList, Bookmark bm)
{
	list<Bookmark>::iterator it = bmList.end();
	--it;
	--it;
	bmList.insert(it, bm);
	wstring folder = bm.GetFolder();

	Bookmark* bm_beg = new Bookmark(L"		<DL><p>");
	bm_beg->SetFolderName(folder);
	bmList.insert(it, *bm_beg);

	Bookmark* bm_end = new Bookmark(L"		</DL><p>");
	bm_end->SetFolderName(folder);
	bmList.insert(it, *bm_end);	
}

void BookmarkFile::Merge(BookmarkFile &bf_second)
{
	list<Bookmark>::iterator it_second;
	list<Bookmark>::iterator it_first;
	list<wstring>::iterator it_wstr;
	//create a list of folders
	list<wstring> nameOfFolder;
	CreateListFolders(nameOfFolder);
	//copy from the second bookmark file to the first
	for (it_second = bf_second.url.begin(); it_second != bf_second.url.end(); ++it_second)
	{
		it_wstr = find(nameOfFolder.begin(), nameOfFolder.end(), (*it_second).GetFolder());
		if (it_wstr != nameOfFolder.end()) //found
		{
			if ((*it_second).IsFolderEmpty() == false && (*it_second).IsHrefEmpty() == false)
			{
				//find position in first list
				for (it_first = url.begin(); it_first != url.end(); ++it_first)
				{
					if ((*it_second) == (*it_first))
						break;
					if ((*it_first).GetFolder() == (*it_second).GetFolder() &&
						((*it_second) < (*it_first) || (*it_first).recordType == (*it_first).HEAD_END))
					{
						url.insert(it_first, (*it_second));
						break;
					}
				}
			}
		}
		else //folder not found
		{
			if ((*it_second).GetFolder().length() && (*it_second).recordType == (*it_second).HEAD_BEG)
			{
				CreateNewFolder(this->url, (*it_second));
				nameOfFolder.push_back((*it_second).GetFolder());
			}
		}
	}
}

void BookmarkFile::SortByNameInFolder()
{
	list<Bookmark> urlInFolder;
	list<Bookmark>::iterator it;
	list<Bookmark>::iterator it_mark;
	list<wstring> nameOfFolder;
	CreateListFolders(nameOfFolder);
	list<wstring>::iterator itOfFolder;
	//pass through all folders. create a list for each folder. sort
	for (itOfFolder = nameOfFolder.begin(); itOfFolder != nameOfFolder.end(); ++itOfFolder)
	{
		urlInFolder.clear();
		for (it = url.begin(); it != url.end();) {
			if ((*it).GetFolder() == (*itOfFolder) && (*it).IsHrefEmpty() == false)
			{
				urlInFolder.push_back((*it));
				it = url.erase(it);
				it_mark = it;
			}
			else
				++it;
		}
		urlInFolder.sort();
		urlInFolder.unique();
		it = it_mark;
		url.insert(it, urlInFolder.begin(), urlInFolder.end());
	}
}