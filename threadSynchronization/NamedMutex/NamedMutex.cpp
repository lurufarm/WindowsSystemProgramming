// NamedMutex.cpp
// named mutex의 역할 이해

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <process.h>

HANDLE hMutex;
DWORD dwWaitResult;

void ProcessBaseCtiricalSection()
{
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

	switch (dwWaitResult)
	{
	case WAIT_OBJECT_0: // 스레드가 뮤텍스를 소유하였다.
		_tprintf(_T("thread got mutex! \n"));
		break;
	case WAIT_TIMEOUT: // Time Out 발생
		_tprintf(_T("timer expired! \n"));
		break;
	case WAIT_ABANDONED: // 뮤텍스 반환이 적절히 이뤄지지 않음
		return;
	}

	for (size_t i = 0; i < 5; i++)
	{
		_tprintf(_T("Thread Running!\n"));
		Sleep(10000);
	}

	ReleaseMutex(hMutex);
}

int _tmain(int argc, TCHAR* argv[])
{
#if 0
	hMutex = CreateMutex(
		NULL,
		FALSE,
		_T("NamedMutex")); // named mutex
#else
	hMutex = OpenMutex(
		MUTEX_ALL_ACCESS,	// 접근 권한 요청
		FALSE,				// 핸들 상속하지 않겠다.
		_T("NamedMutex"));	// 뮤텍스 오브젝트 이름
#endif

	if (hMutex == NULL)
	{
		_tprintf(_T("CreateMutex error: %d\n"), GetLastError());
		return -1;
	}

	ProcessBaseCtiricalSection();

	CloseHandle(hMutex);
	return 0;
}