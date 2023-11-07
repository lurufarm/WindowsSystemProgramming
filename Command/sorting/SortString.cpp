// SortString.cpp
// sort 실행파일

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define MAX_STRING_NUM 100
#define MAX_STRING_LEN 256

void SortString(void)
{
	TCHAR stringArr[MAX_STRING_NUM][MAX_STRING_LEN];

	int nStr;
	for (nStr = 0; nStr < MAX_STRING_NUM; nStr++)
	{
		TCHAR* isEOF = _fgetts(stringArr[nStr], MAX_STRING_LEN, stdin);
		if (isEOF == NULL)
			break;			//EOF는 Ctrl+Z임
	}

	TCHAR strTemp[MAX_STRING_LEN];

	for (size_t i = 0; i < nStr; i++)
	{
		for (size_t j = nStr-1; j > i; j--)
		{
			if (_tcscmp(stringArr[j - 1], stringArr[j]) > 0)
			{
				_tcscpy(strTemp, stringArr[j - 1]);
				_tcscpy(stringArr[j - 1], stringArr[j]);
				_tcscpy(stringArr[j], strTemp);
			}
		}
	}

	for (size_t i = 0; i < nStr; i++)
	{
		_fputts(stringArr[i], stdout);
	}
}

int _tmain(int argc, TCHAR* argv[])
{
	SortString();
	return 0;
}