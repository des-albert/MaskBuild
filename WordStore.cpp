#include "WordStore.h"
#include <cmath>


WordStore::WordStore()
{
	
}

WordStore::~WordStore()
{

}

//*********************************************************************
//
//	Opens the file containing words and creates a memory map
//
//*********************************************************************

bool
WordStore::Open()
{
	cout << "MaskBuild " << endl;

	if ((hFile = CreateFile(WORDFILE,
		GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL)) == INVALID_HANDLE_VALUE)

		return false;

	fileMask.open(MASKFILE, ios::out);

	if (!fileMask) 

		return false;

	size = GetFileSize(hFile, NULL);

	cout << "File Size " << size << endl;

	hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, WORDFILE);

	//	Memory Map the Word File

	if (hMap != 0)
		map = (char*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

	next = map;

	return true;
}

void
WordStore::Close()
{
	UnmapViewOfFile(map);
	CloseHandle(hMap);
	CloseHandle(hFile);
	
	fileMask.close();
}

bool
WordStore::Sort()
{
	
	while (next < map + size) 
	{
		int length = 0;
		int mask = 0;
		char* p;
		char match[30];
		for (p = next; *p != '\r'; p++, length++)
		{
			if (*p < 'a')
				mask |= 1 << int(*p - 'A');
			else
				mask |= 1 << int(*p - 'a');

		}

		if (length > 4) {
			memcpy(match, next, length);
			match[length] = 0;
			fileMask << mask << " " << match << endl;
			++wordCount;
		}
		next += length + 2;
	}

	cout << "Complete - " << wordCount << " words" << endl;
	return true;
}
