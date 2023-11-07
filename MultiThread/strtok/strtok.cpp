// strtok.cpp
// 문자열을 토큰으로 나누기
#pragma warning(disable:4996)
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR string[] =
		_T("Hey, get a life!")
		_T("You don't even have two pennies to rub together.");

	TCHAR seps[] = _T(" ,.!"); // 토큰 분리 조건

	TCHAR* token = _tcstok(string, seps);

	while (token != NULL)
	{
		_tprintf(_T("%s\n"), token);
		token = _tcstok(NULL, seps);
	}
	return 0;
}