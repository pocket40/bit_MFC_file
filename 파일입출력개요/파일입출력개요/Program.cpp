#include <Windows.h>
#include <stdio.h>
int main()
{
	HANDLE hFile = CreateFile(TEXT("data.txt"), // 파일명
		GENERIC_WRITE | GENERIC_READ, // 목적
		0, //파일 공유 모드
		0,//보안 기술자(이 부분이 있으면 커널 개체)
		CREATE_NEW,//새로운 파일 생성

		//#define CREATE_NEW          1 // 존재하면 실패
		//#define CREATE_ALWAYS       2 // 언제나 성공 (존재할 때 내용은 날라감)
		//#define OPEN_EXISTING       3 // 존재하면 성공
		//#define OPEN_ALWAYS         4 // 언제나 성공(없으면 새로 생성, 존재할 때 내용 그대로 보존)
		//#define TRUNCATE_EXISTING   5 // 없으면 실패, 있을 때 내용 날라감

		FILE_ATTRIBUTE_ARCHIVE,
		0);
	if (hFile == INVALID_HANDLE_VALUE) //INVALID_HANDLE_VALUE
	{
		printf("파일 열기 실패\n");
	}
	CloseHandle(hFile); // 커널 개체 핸들을 닫는 API

	return 0;
}