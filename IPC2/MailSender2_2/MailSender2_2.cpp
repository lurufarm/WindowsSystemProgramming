// MailSender2_2.cpp
// 핸들의 상속 확인용 예제. 자식 프로세스

#pragma warning(disable:4996)

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot;
	TCHAR message[50];
	DWORD bytesWritten; // number of bytes write

	// 핸들을 얻는 코드 --
	//FILE* file = _tfopen(_T("..\\InheritableHandle.txt"), _T("rt"));
	FILE* file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
	while (file == nullptr)
	{
		//file = _tfopen(_T("..\\InheritableHandle.txt"), _T("rt"));
		file = _tfopen(_T("InheritableHandle.txt"), _T("rt"));
	}

	_ftscanf(file, _T("%d"), &hMailSlot);
	fclose(file);
	_tprintf(_T("Inheritable Handle : %d\n"), hMailSlot);
	// ------------------

	while (true)
	{
		_fputts(_T("MY CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		if (!WriteFile(hMailSlot, message, _tcslen(message) * sizeof(TCHAR),
			&bytesWritten, NULL))
		{
			_fputts(_T("Unable to write!\n"), stdout);
			CloseHandle(hMailSlot);
			return 1;
		}

		if (!_tcscmp(message, _T("exit")))
		{
			_fputts(_T("Good Bye!\n"), stdout);
			break;
		}
	}
	CloseHandle(hMailSlot);
	return 0;

}