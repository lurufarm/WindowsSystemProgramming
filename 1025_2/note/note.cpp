// note.cpp
// 1. 입력 시 메모장을 여는 프로그램

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum
{
	notepad = 1,
	EXIT
};

DWORD Input();

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("notepad.exe");

	SetCurrentDirectory(_T("C:\\Windows\\system32"));

	DWORD sel;
	while (true)
	{
		sel = Input();

		if (sel == EXIT)
			return 0;

		ZeroMemory(&pi, sizeof(pi));
		CreateProcess(
			NULL, command, NULL, NULL,
			TRUE, 0, NULL, NULL, &si, &pi);

		return 0;
	}
}

DWORD Input()
{
	DWORD sel;
	_fputts(_T("-----Menu----- \n"), stdout);
	_fputts(_T("num 1 : Notepad\n"), stdout);
	_fputts(_T("num 2 : Exit\n"), stdout);

	wscanf_s(_T("%d"), &sel);

	return sel;
}
