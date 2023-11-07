// anonymous_pipe.cpp
// 이름 없는 파이프의 기본 원리 파악

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

	// 파이프 생성

	CreatePipe(&hReadPipe, &hWritePipe, NULL, 0);

	// 파이프의 한쪽 끝을 이용한 데이터 송신
	WriteFile(hWritePipe, sendString, lstrlen(sendString) * sizeof(TCHAR),
		&bytesWritten, NULL);
	_tprintf(_T("string send : %s \n"), sendString);

	// 파이프의 다른 한 쪽 끝을 이용한 데이터 수신
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