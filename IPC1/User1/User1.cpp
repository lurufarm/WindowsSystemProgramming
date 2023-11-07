#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define SLOT_NAME_USER1_RECEIVE _T("\\\\.\\mailslot\\mailbox_user1_receive")
#define SLOT_NAME_USER2_RECEIVE _T("\\\\.\\mailslot\\mailbox_user2_receive")

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hMailSlot_Receive_User1;
	HANDLE hMailSlot_Send_User2;
	TCHAR messageBox[50];
	DWORD bytesRead;
	TCHAR message[50];
	DWORD bytesWritten;

	// User1�� ���� ���� ���� (�޴� ���� ����)
	hMailSlot_Receive_User1 = CreateMailslot
	(
		SLOT_NAME_USER1_RECEIVE,
		0,
		MAILSLOT_WAIT_FOREVER,
		NULL
	);

	// User2�� ���� ���� ���� (������ ���� ����)
	hMailSlot_Send_User2 = CreateFile(
		SLOT_NAME_USER2_RECEIVE,
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// ���� ���� ���� �� ���� ���� ó��

	if (hMailSlot_Receive_User1 == INVALID_HANDLE_VALUE)
	{
		_fputts(_T("Unable to create mailslot for receiving in User1!\n"), stdout);
		return 1;
	}

	while (hMailSlot_Send_User2 == INVALID_HANDLE_VALUE)
	{
		hMailSlot_Send_User2 = CreateFile(
			SLOT_NAME_USER2_RECEIVE,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}

	// �޽��� ���� �� �۽�

	while (true)
	{
		_fputts(_T("User1 CMD>"), stdout);
		_fgetts(message, sizeof(message) / sizeof(TCHAR), stdin);

		if (!_tcscmp(message, _T("exit\n")))
		{
			_fputts(_T("Good Bye!\n"), stdout);
			WriteFile(hMailSlot_Send_User2, _T("Good Bye!\n"), _tcslen(_T("Good Bye!\n")) * sizeof(TCHAR), &bytesWritten, NULL);
			break;
		}
		// User2���� �޽��� �۽�
		WriteFile(hMailSlot_Send_User2, message, _tcslen(message) * sizeof(TCHAR), &bytesWritten, NULL);

		// User2�κ��� �޽��� ����
		ReadFile(hMailSlot_Receive_User1, messageBox, sizeof(TCHAR) * 50, &bytesRead, NULL);
		messageBox[bytesRead / sizeof(TCHAR)] = 0; // NULL���� ����
		_fputts(messageBox, stdout);


	}

	CloseHandle(hMailSlot_Receive_User1);
	CloseHandle(hMailSlot_Send_User2);
	return 0;
}

