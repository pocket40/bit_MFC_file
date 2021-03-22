#include <stdio.h>
#include <stdlib.h>
typedef struct _Data Data;
struct _Data
{
	int a;
	char b[4];
	int c;
};
#define BUF2DATA(buf) ((Data*) buf)

char buffer[4096];

void SendData()
{
	Data data = { 4,"um",27 };
	Data* pdata = BUF2DATA(buffer);
	*pdata = data;
}
void RecvData()
{
	Data* pdata = BUF2DATA(buffer);
	printf("%d %s %d\n", pdata->a, pdata->b, pdata->c);
}
int main()
{
	SendData();
	RecvData();
	system("pause");
	return 0;
}