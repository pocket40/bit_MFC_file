#include <Windows.h>
#include <stdio.h>
#include <locale.h>
void WriteData()
{
    WCHAR name[10] = TEXT("ȫ�浿");
    int num = 27;
    int age = 20;
    WCHAR addr[256] = TEXT("���ѹα� ��ó�� ���� �� ���� ������ ��� ����");
    HANDLE hFile = CreateFile(TEXT("data.txt"), //���ϸ�
        GENERIC_WRITE,//����
        0, //���� ���� ���
        0, //���� �����(�� �κ��� ������ Ŀ�� ��ü)
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("���� ���� ����\n");
    }
    DWORD dw;
    WriteFile(hFile, name, sizeof(name), &dw, 0); //3��° ���� &dw ����۰� ����Ǿ����� Ȯ���ϱ� ���� ����, 4��° ���� ������������ ����͸� �ϱ� ���� ����

    CloseHandle(hFile);//Ŀ�� ��ü �ڵ��� �ݴ� API
}
void ReadData()
{
    WCHAR name[10] = TEXT("");
    int num = 27;
    int age = 20;
    WCHAR addr[256] = TEXT("���ѹα� ��ó�� ���� �� ���� ������ ��� ����");
    HANDLE hFile = CreateFile(TEXT("data.txt"), //���ϸ�
        GENERIC_WRITE | GENERIC_READ,//����
        0, //���� ���� ���
        0, //���� �����(�� �κ��� ������ Ŀ�� ��ü)
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("���� �б� ����\n");
    }
    DWORD dw;
    ReadFile(hFile, name, sizeof(name), &dw, 0);
    ReadFile(hFile, &num, sizeof(num), &dw, 0);
    ReadFile(hFile, &age, sizeof(age), &dw, 0);
    ReadFile(hFile, addr, sizeof(addr), &dw, 0);
    CloseHandle(hFile);//Ŀ�� ��ü �ڵ��� �ݴ� API
    WCHAR buf[1000];
    wprintf(buf, TEXT("abc �̸�:%s ��ȣ:%d ����:%d �ּ�:%s\n"), name, num, age, addr);
    _wsetlocale(LC_ALL, L"korean");
    wprintf(buf);

}
int main()
{
    WriteData();
    ReadData();
    return 0;
}