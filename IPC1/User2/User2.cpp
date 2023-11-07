#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME_USER1_RECEIVE _T("\\\\.\\mailslot\\mailbox_user1_receive")
#define SLOT_NAME_USER2_RECEIVE _T("\\\\.\\mailslot\\mailbox_user2_receive")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot_Receive_User2;
	HANDLE hMailSlot_Send_User1;
	TCHAR messageBox[50];
	DWORD bytesRead;
	TCHAR message[50];
	DWORD bytesWritten;

	// User2의 메일 슬롯 생성 (받는 메일 슬롯)
	hMailSlot_Receive_User2 = CreateMailslot
	(
		SLOT_NAME_USER2_RECEIVE,
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL
	);

	// User1의 메일 슬롯 열기 (보내는 메일 슬롯)
	hMailSlot_Send_User1 = CreateFile(
		SLOT_NAME_USER1_RECEIVE,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// 메일 슬롯 생성 및 열기 오류 처리

	if (hMailSlot_Receive_User2 == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot for receiving in User2!\n"), stdout);
		return 1;
	}

	while (hMailSlot_Send_User1 == INVALID_HANDLE_VALUE)
	{
		hMailSlot_Send_User1 = CreateFile(
			SLOT_NAME_USER1_RECEIVE,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}

	// 메시지 수신 및 송신

	while (true)
	{
		_fputts(_T("User2 CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		if (!_tcscmp(message, _T("exit\n")))
		{
			_fputts(_T("User2: Good Bye!\n"), stdout);
			WriteFile(hMailSlot_Send_User1, _T("Good Bye!\n"), _tcslen(_T("Good Bye!\n")) * sizeof(TCHAR), &bytesWritten, NULL);
			break;
		}

		// User1에게 메시지 송신
		WriteFile(hMailSlot_Send_User1, message, _tcslen(message) * sizeof(TCHAR), &bytesWritten, NULL);

		// User1로부터 메시지 수신
		ReadFile(hMailSlot_Receive_User2, messageBox, sizeof(TCHAR) * 50, &bytesRead, NULL);
		messageBox[bytesRead / sizeof(TCHAR)] = 0; // NULL문자 삽입
		_fputts(messageBox, stdout);
	}

	CloseHandle(hMailSlot_Receive_User2);
	CloseHandle(hMailSlot_Send_User1);
	return 0;
}
