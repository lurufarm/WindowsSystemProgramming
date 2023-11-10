// CriticalSectionSyncMutex.cpp 
// 크리티컬 섹션과 뮤텍스 비교

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

#define NUM_OF_GATE 6

LONG gTotalCount = 0;

HANDLE hMutex;

void IncreaseCount()
{
	WaitForSingleObject(hMutex, INFINITE);
	gTotalCount++;
	ReleaseMutex(hMutex);
}

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	for (DWORD i = 0; i < 1000; i++)
	{
		IncreaseCount();
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	DWORD dwThreadID[NUM_OF_GATE];
	HANDLE hThread[NUM_OF_GATE];

	hMutex = CreateMutex(
		NULL, // 디폴트 보안 관리자
		FALSE, // 누구나 소유할 수 있도록
		NULL	// nonamed mutex
	);

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error : %d\n"), GetLastError());
	}

	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		hThread[i] =
			(HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL,
				CREATE_SUSPENDED, (unsigned int*)&dwThreadID[i]);

		if (hThread[i] = NULL)
		{
			_tprintf(_T("Thread creation fault!\n"));
			return -1;
		}
	}

	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		ResumeThread(hThread[i]);
	}

	WaitForMultipleObjects(NUM_OF_GATE, hThread, TRUE, INFINITE);
	_tprintf(_T("total count : %d \n"), gTotalCount);

	for (DWORD i = 0; i < NUM_OF_GATE; i++)
	{
		CloseHandle(hThread[i]);
	}

	CloseHandle(hMutex);
	return 0;
}

