#include <Windows.h>
#include <stdio.h>
int main()
{
	HANDLE hFile = CreateFile(TEXT("data.txt"), // ���ϸ�
		GENERIC_WRITE | GENERIC_READ, // ����
		0, //���� ���� ���
		0,//���� �����(�� �κ��� ������ Ŀ�� ��ü)
		CREATE_NEW,//���ο� ���� ����

		//#define CREATE_NEW          1 // �����ϸ� ����
		//#define CREATE_ALWAYS       2 // ������ ���� (������ �� ������ ����)
		//#define OPEN_EXISTING       3 // �����ϸ� ����
		//#define OPEN_ALWAYS         4 // ������ ����(������ ���� ����, ������ �� ���� �״�� ����)
		//#define TRUNCATE_EXISTING   5 // ������ ����, ���� �� ���� ����

		FILE_ATTRIBUTE_ARCHIVE,
		0);
	if (hFile == INVALID_HANDLE_VALUE) //INVALID_HANDLE_VALUE
	{
		printf("���� ���� ����\n");
	}
	CloseHandle(hFile); // Ŀ�� ��ü �ڵ��� �ݴ� API

	return 0;
}