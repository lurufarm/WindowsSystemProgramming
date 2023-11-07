// 명령 프롬프트의 골격
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <TlHelp32.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[]
= _T("'%s'은(는) 실행할 수 있는 프로그램이 아닙니다. \n");

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdReadTokenize(void);
int CmdProcessing(int);
TCHAR* StrLower(TCHAR*);
void ListProcessInfo(void);
void KillProcess(void);


int _tmain(int argc, TCHAR* argv[])
{
	// 한글 입력 가능하도록
	_tsetlocale(LC_ALL, _T("Korean"));

	if (argc > 2)
	{
		for (size_t i = 0; i < argc; i++)
		{
			_tcscpy(cmdTokenList[i - 1], argv[i]);
		}
		CmdProcessing(argc - 1);
	}

	DWORD isExit = NULL;

	while (1)
	{
		int tokenNum = CmdReadTokenize();
		isExit = CmdProcessing(tokenNum);
		if (isExit)
		{
			_fputts(_T("명령어 처리를 종료합니다. \n"), stdout);
			break;
		}
	}

	return 0;
}


// TCHAR int CmdProcessing(void)
// 명령어를 입력 받아서 해당 명령어에 지정되는 기능을 수행한다.
// exit가 입력되면 True를 반환하고, 이는 프로그램의 종료로 이어진다.

int CmdReadTokenize(void)
{
	TCHAR* token;

	_fputts(_T("Best command prompt>> "), stdout);
	_getts_s(cmdString);

	token = _tcstok(cmdString, seps);

	int tokenNum = 0;

	while (token != NULL)
	{
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	return tokenNum;
}

int CmdProcessing(int num)
{
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("start")))
	{
		if (num > 1)
		{
			for (size_t i = 1; i < num; i++)
				_stprintf(optString, _T("%s %s"), optString,
					cmdTokenList[i]);

			_stprintf(cmdStringWithOptions,
				_T("%s %s"), _T("1024.exe"), optString);
		}
		else
			_stprintf(cmdStringWithOptions, _T("%s"),
				_T("1024.exe"));

		isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL,
			TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("echo")))
	{
		for (size_t i = 1; i < num; i++)
		{
			_stprintf(optString, _T("%s %s"), optString,
				cmdTokenList[i]);
		}

		_tprintf(_T("%s\n"), optString);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("lp")))
	{
		ListProcessInfo();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("kp")))
	{
		KillProcess();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("sort")))
	{
		if (!_tcscmp(cmdTokenList[1], _T(">")))
		{
			SECURITY_ATTRIBUTES fileSec = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
			HANDLE hFile = CreateFile(cmdTokenList[2], GENERIC_WRITE, FILE_SHARE_READ,
				&fileSec, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			si.hStdOutput = hFile;
			si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
			si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
			si.dwFlags |= STARTF_USESTDHANDLES;

			isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL,
				TRUE, 0, NULL, NULL, &si, &pi);

			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(hFile);
		}
		else
		{
			isRun = CreateProcess(NULL, cmdTokenList[0], NULL, NULL,
				FALSE, 0, NULL, NULL, &si, &pi);

			WaitForSingleObject(pi.hProcess, INFINITE);
		}

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);

		for (size_t i = 1; i < num; i++)
		{
			_stprintf(cmdStringWithOptions, _T("%s, %s"),
				cmdStringWithOptions, cmdTokenList[i]);
		}

		isRun = CreateProcess(NULL, cmdStringWithOptions,
			NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (!isRun)
			_tprintf(ERROR_CMD, cmdTokenList[0]);
	}

	return 0;

}

// TCHAR* StrLower(TCHAR* pStr)
// 문자열 내 존재하는 모든 대문자를 소문자로 변경한다.
// 변경된 문자열의 포인터를 반환한다.

TCHAR* StrLower(TCHAR* pStr)
{
	TCHAR* ret = pStr;

	while (*pStr)
	{
		if (_istupper(*pStr))
			*pStr = _totlower(*pStr);
		pStr++;
	}
	return ret;
}

void ListProcessInfo(void)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (hProcessSnap == INVALID_HANDLE_VALUE)
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32))
	{
		do
		{
			_tprintf(_T("%5d %25s\n"), pe32.th32ProcessID, pe32.szExeFile);
		} while (Process32Next(hProcessSnap, &pe32));
	}
	CloseHandle(hProcessSnap);
}

void KillProcess(void)
{
	DWORD kpID = 0;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hProcessSnap, &pe32))
	{
		do
		{
			//TCHAR pName[STR_LEN] = { 0, };
			//_tcscpy(pName, StrLower(pe32.szExeFile));
			if (!_tcscmp(StrLower(pe32.szExeFile), cmdTokenList[1]))
			{
				kpID = pe32.th32ProcessID;
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, kpID);
				bool isKill = 0;
				isKill = TerminateProcess(hProcess, -1);
				if (isKill)
				{
					CloseHandle(hProcessSnap);
					CloseHandle(hProcess);
					break;
				}
			}
		} while (Process32Next(hProcessSnap, &pe32));
	}

}
