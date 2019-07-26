#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<taos.h>

int main(int argc,char *argv[])
{
    taos_init();

    TAOS *taos = taos_connect("127.0.0.1","root","taosdata",NULL,0);
    if(taos == NULL)
    {
        printf("failed to connect to server, reason:%s\n",taos_errstr(taos));
        exit(1);
    }
    return 0;
}
