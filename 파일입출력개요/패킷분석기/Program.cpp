//패킷 파일 헤더 및 패킷 헤더 분석한 코드
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
    printf("Snap 길이:%#X\n", pfh->snap_len);
    printf("Link Type:%d\n", pfh->link_type);
    printf("Pcap 파일 헤더 분석 성공\n");
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
    printf("\t캡쳐 길이:%d\t", ph->cap_len);
    printf("패킷 길이:%d\n", ph->pac_len);
}
void Parsing(HANDLE hFile)
{
    PFHeader pfh;
    if (ParsingPCapFileHeader(hFile, &pfh) == 0)
    {
        printf("Pcap 파일 헤더 분석에서 문제가 발생하였습니다.\n");
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
    HANDLE hFile = CreateFile(TEXT("demo.pcap"), //파일명
        GENERIC_READ,//목적
        0, //파일 공유 모드
        0, //보안 기술자(이 부분이 있으면 커널 개체)
        OPEN_EXISTING,
        FILE_ATTRIBUTE_ARCHIVE,
        0);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("파일 열기 실패\n");
    }
    else
    {
        Parsing(hFile);
    }

    CloseHandle(hFile);//커널 개체 핸들을 닫는 API    
    return 0;
}