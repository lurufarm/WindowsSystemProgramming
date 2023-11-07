// anonymous_pipe.cpp
// �̸� ���� �������� �⺻ ���� �ľ�

#pragma warning(disable:4996)
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hReadPipe, hWritePipe; // pipe handle

	TCHAR sendString[] = _T("anonymous pipe");
	TCHAR recvString[100];

	DWORD bytesWritten;
	DWORD byteRead;

	// ������ ����

	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);

	// �������� ���� ���� �̿��� ������ �۽�
	WriteFile(hWritePipe, sendString, lstrlen(sendString) * sizeof(TCHAR),
		&bytesWritten, NULL);
	_tprintf(_T("string send : %s \n"), sendString);

	// �������� �ٸ� �� �� ���� �̿��� ������ ����
	ReadFile(
		hReadPipe, recvString,
		bytesWritten, &byteRead,
		NULL);

	recvString[byteRead / sizeof(TCHAR)] = 0;
	_tprintf(_T("string recv : %s \n"), recvString);

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	
	return 0;
}