//��Ŷ ���� ��� �� ��Ŷ ��� �м��� �ڵ�
#include <Windows.h>
#include <stdio.h>
#define PCAP_MAGIC 0xa1b2c3d4

typedef struct PCapFileHeader
{
    unsigned int magic;
    int version;
    int tz;
    int ts;
    int snap_len;
    int link_type;
}PCapFileHeader, PFHeader;

typedef struct PCapHeader
{
    unsigned tm_high;
    unsigned tm_low;
    unsigned cap_len;
    unsigned pac_len;
}PCapHeader, PHeader;

int ParsingPCapFileHeader(HANDLE hFile, PFHeader* pfh)
{
    DWORD dw;

    ReadFile(hFile, pfh, sizeof(PFHeader), &dw, 0);
    if (pfh->magic != PCAP_MAGIC)
    {
        return 0;
    }
    return 1;
}
void ViewPFHeaderInfo(PFHeader* pfh)
{
    printf("version:%#x.%#x\n", LOWORD(pfh->version), HIWORD(pfh->version));
    printf("Time Zone:%d\n", pfh->tz);
    printf("Time Stamps:%d\n", pfh->ts);
    printf("Snap ����:%#X\n", pfh->snap_len);
    printf("Link Type:%d\n", pfh->link_type);
    printf("Pcap ���� ��� �м� ����\n");
}

int ParsingPacket(HANDLE hFile, PHeader* ph)
{
    DWORD dw;
    ReadFile(hFile, ph, sizeof(PHeader), &dw, 0);
    if (dw != sizeof(PHeader))
    {
        return 0;
    }
    void* buffer = malloc(ph->cap_len);
    ReadFile(hFile, buffer, ph->cap_len, &dw, 0);
    free(buffer);
    return 1;
}
void ViewPacket(PHeader* ph, int n)
{
    printf("========= %d th ============\n", n);
    printf("\tĸ�� ����:%d\t", ph->cap_len);
    printf("��Ŷ ����:%d\n", ph->pac_len);
}
void Parsing(HANDLE hFile)
{
    PFHeader pfh;
    if (ParsingPCapFileHeader(hFile, &pfh) == 0)
    {
        printf("Pcap ���� ��� �м����� ������ �߻��Ͽ����ϴ�.\n");
        return;
    }
    ViewPFHeaderInfo(&pfh);

    int n = 1;
    PHeader ph;
    while (true)
    {
        if (ParsingPacket(hFile, &ph) == 0)
        {
            break;
        }
        ViewPacket(&ph, n);
        n++;
    }
}
int main()
{
    HANDLE hFile = CreateFile(TEXT("demo.pcap"), //���ϸ�
        GENERIC_READ,//����
        0, //���� ���� ���
        0, //���� �����(�� �κ��� ������ Ŀ�� ��ü)
        OPEN_EXISTING,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("���� ���� ����\n");
    }
    else
    {
        Parsing(hFile);
    }

    CloseHandle(hFile);//Ŀ�� ��ü �ڵ��� �ݴ� API    
    return 0;
}