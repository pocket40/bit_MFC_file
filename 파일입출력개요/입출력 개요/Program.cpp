#include <Windows.h>
#include <stdio.h>
#include <locale.h>
void WriteData()
{
    WCHAR name[10] = TEXT("홍길동");
    int num = 27;
    int age = 20;
    WCHAR addr[256] = TEXT("대한민국 근처에 있을 것 같은 율도국 어느 동굴");
    HANDLE hFile = CreateFile(TEXT("data.txt"), //파일명
        GENERIC_WRITE,//목적
        0, //파일 공유 모드
        0, //보안 기술자(이 부분이 있으면 커널 개체)
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("파일 열기 실패\n");
    }
    DWORD dw;
    WriteFile(hFile, name, sizeof(name), &dw, 0); //3번째 인자 &dw 몇버퍼가 저장되었는지 확인하기 위한 인자, 4번째 인자 문제가있을때 모니터링 하기 위한 인자

    CloseHandle(hFile);//커널 개체 핸들을 닫는 API
}
void ReadData()
{
    WCHAR name[10] = TEXT("");
    int num = 27;
    int age = 20;
    WCHAR addr[256] = TEXT("대한민국 근처에 있을 것 같은 율도국 어느 동굴");
    HANDLE hFile = CreateFile(TEXT("data.txt"), //파일명
        GENERIC_WRITE | GENERIC_READ,//목적
        0, //파일 공유 모드
        0, //보안 기술자(이 부분이 있으면 커널 개체)
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("파일 읽기 실패\n");
    }
    DWORD dw;
    ReadFile(hFile, name, sizeof(name), &dw, 0);
    ReadFile(hFile, &num, sizeof(num), &dw, 0);
    ReadFile(hFile, &age, sizeof(age), &dw, 0);
    ReadFile(hFile, addr, sizeof(addr), &dw, 0);
    CloseHandle(hFile);//커널 개체 핸들을 닫는 API
    WCHAR buf[1000];
    wprintf(buf, TEXT("abc 이름:%s 번호:%d 나이:%d 주소:%s\n"), name, num, age, addr);
    _wsetlocale(LC_ALL, L"korean");
    wprintf(buf);

}
int main()
{
    WriteData();
    ReadData();
    return 0;
}