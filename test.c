#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<taos.h>

#define TABLE_COUNT 100000
#define ROW_COUNT 1000
int main(int argc,char *argv[])
{
    taos_init();

    TAOS *taos = taos_connect("127.0.0.1","root","taosdata",NULL,0);
    if(taos == NULL)
    {
        printf("failed to connect to server, reason:%s\n",taos_errstr(taos));
        exit(1);
    }

    if (taos_query(taos, "create database db cache 8192 ablocks 2 tblocks 1000 tables 10000") != 0)
    {
        printf("failed to create database, reason:%s\n",taos_errstr(taos));
        exit(1);
    }

    taos_query(taos,"use db");

    char sql[65000] = "create table vehicles(ts timestamp, longitude bigint, latitude bigint, altitude int, direction int, velocity int) tags(card int, model binary(10))";
    if(taos_query(taos,sql) != 0)
    {
        printf("failed to create stable, reason:%s\n",taos_errstr(taos));
        exit(1);
    }

    int begin = time(NULL);
    for(int table = 0; table < TABLE_COUNT; table++)
    {
        sprintf(sql,"create table v%d using vehicles tags(%d, 't%d')",table,table,table);
        if(taos_query(taos,sql) != 0)
        {
            printf("failed to create table t%d,reason:%s\n",table,taos_errstr(taos));
            exit(1);
        }

        for(int loop = 0; loop < 44; loop++)
        {
            int len = sprintf(sql,"insert into v%d values",table);
            for(int row = 0; row < ROW_COUNT; row++)
            {
                len += sprintf(sql + len, "(%ld,%d,%d,%d,%d,%d)", 1561910400000L + 60000L * (row + loop * 1000L), row, row, row, row, row);
            }
            if(taos_query(taos,sql) != 0)
            {
                printf("falied to insert table t%d,reason:%s\n",table,taos_errstr(taos));
            }
        }
    }

    int end = time(NULL);
    printf("insert finished,time spend %d seconds\n",end - begin);
    return 0;
}
