// MailSender2_1.cpp
// 핸들의 상속 확인용 예제. 부모 프로세스

#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailslot;
	TCHAR message[50];
	DWORD bytesWritten; // number of bytes write

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	hMailslot = INVALID_HANDLE_VALUE;

	while (hMailslot == INVALID_HANDLE_VALUE)
	{
		hMailslot = CreateFile(
			SLOT_NAME,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			&sa,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hMailslot != INVALID_HANDLE_VALUE)
			break;

		_fputts(_T("Unable to create mailslot!\n"), stdout);
		//return 1;
	}

	_tprintf(_T("Inheritable Handle : %d \n"), hMailslot);

	//FILE* file = _tfopen(_T("..\\InheritableHandle.txt"), _T("wt"));
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("wt"));
	_ftprintf(file, _T("%d"), hMailslot);
	fclose(file);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("MailSender2_2.exe");

	CreateProcess(NULL, command, NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	while (true)
	{
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		if (!WriteFile(hMailslot, message, _tcslen(message) * sizeof(TCHAR),
			&bytesWritten, NULL))
		{
			_fputts(_T("Unable to write!\n"), stdout);
			CloseHandle(hMailslot);
			return 1;
		}

		if (!_tcscmp(message, _T("exit")))
		{
			_fputts(_T("Good Bye!\n"), stdout);
			break;
		}
	}
	CloseHandle(hMailslot);
	return 0;
}