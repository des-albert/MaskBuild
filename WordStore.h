
#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

#define WORDFILE	L"words.txt"
#define MASKFILE	L"maskWords.txt"

class WordStore
{

public:
	WordStore();
	~WordStore();
	bool Open();
	void Close();
	bool Sort();

private:

	int size = 0;

	char* map = NULL;
	char* next = NULL;

	HANDLE hFile = NULL;
	HANDLE hMap = NULL;

	fstream fileMask;

	int wordCount = 0;

};

