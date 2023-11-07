// PartAdder.cpp
// 전달된 인자 사이의 수 덧셈

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	if (argc != 3)
		return -1;

	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;
	
	for (size_t i = start; i <= end ; i++)
		total += i;
	
	return total;
}