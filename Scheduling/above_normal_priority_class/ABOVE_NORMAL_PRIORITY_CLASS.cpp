// ABOVE_NORMAL_PRIORITY_CLASS.cpp
// 두 개의 자식 프로세스를 생성하는 부모 프로세스

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO siNORMAL = { 0, };
	PROCESS_INFORMATION piNORMAL = { 0, };
	TCHAR command1[] = _T("NORMAL_PRIORITY_CLASS.exe");
	
	STARTUPINFO siBELOW = { 0, };
	PROCESS_INFORMATION piBELOW = { 0, };
	TCHAR command2[] = _T("BELOW_NORMAL_PRIORITY_CLASS.exe");

	siNORMAL.cb = sizeof(siNORMAL);
	siBELOW.cb = sizeof(siBELOW);

	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
	
	CreateProcess(NULL, command1, NULL, NULL, TRUE,
		0, NULL, NULL, &siNORMAL, &piNORMAL);
	
	CreateProcess(NULL, command2, NULL, NULL, TRUE,
		0, NULL, NULL, &siBELOW, &piBELOW);

	while (true)
	{
		//for (DWORD i = 0; i < 10000; i++)
		//	for (DWORD i = 0; i < 10000; i++);
	
		Sleep(10);

		_fputts(_T("ABOVE_NORMAL_PRIORITY_CLASS Process\n"), stdout);
	}

	return 0;
	
}