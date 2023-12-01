// MUTEX_WAIT_ABANDONED.cpp 
// WAIT_ABANDONED에 대한 설명

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

LONG gTotalCount = 0;
HANDLE hMutex;

unsigned int WINAPI IncreaseCountOne(LPVOID lpPram)
{
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;
	return 0;
}

unsigned int WINAPI IncreaseCountTwo(LPVOID lpPram)
{
	DWORD dwWaitResult = 0;
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);
	
	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0:
		ReleaseMutex(hMutex);
		break;
	case WAIT_ABANDONED:
		_tprintf(_T("WAIT_ABANDONED\n"));
		break;
	}

	gTotalCount++;

	ReleaseMutex(hMutex);
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadIDOne;
	DWORD dwThreadIDTwo;

	HANDLE hThreadOne;
	HANDLE hThreadTwo;

	hMutex = CreateMutex(NULL, FALSE, NULL);

	if (hMutex == NULL)
		_tprintf(_T("CreateMutex error:%d"), GetLastError());

	// 무례한 스레드
	hThreadOne = (HANDLE)_beginthreadex(
		NULL, 0, IncreaseCountOne, NULL,
		0, (unsigned*)&dwThreadIDOne);
	
	hThreadTwo = (HANDLE)_beginthreadex(
		NULL, 0, IncreaseCountTwo, NULL,
		CREATE_SUSPENDED, (unsigned*)&dwThreadIDTwo);

	Sleep(1000);
	ResumeThread(hThreadTwo);

	WaitForSingleObject(hThreadTwo, INFINITE);
	_tprintf(_T("total count:%d\n"), gTotalCount);

	CloseHandle(hThreadOne);
	CloseHandle(hThreadTwo);
	CloseHandle(hMutex);

}