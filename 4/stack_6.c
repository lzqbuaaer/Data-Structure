#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct queue{
    int num;
    char a[100][25];
}que;
int main()
{
    int n,p=-1,p1=-1;
    char str[25],s[15][25];
    que list[50];
    while(scanf("%d",&n)!=EOF)
    {
        if(8==n)
        {
            scanf("%s",str);
            p1++;
            strcpy(s[p1],str);
            int f=0;
            for(int i=0;i<=p;i++)
            {
                if(strcmp(list[i].a[0],s[p1])==0)
                break;
            }
            if(0==f)
            {
                p++;
                strcpy(list[p].a[0],s[p1]);
                list[p].num=1;
            }
            if(p1>=1)
            {
                int ff=0;
                for(int i=0;i<=p;i++)
                {
                    if(strcmp(list[i].a[0],s[p1-1])==0)
                    {
                        ff=1;
                        int fff=0;
                        for(int j=1;j<=list[i].num;j++)
                        {
                            if(strcmp(list[i].a[j],s[p1])==0)
                            fff=1;
                        }
                        if(fff) break;
                        strcpy(list[i].a[list[i].num],s[p1]);
                        list[i].num++;
                        break;
                    }
                }
            }
        }
        else if(0==n)
        p1--;
    }
    for(int i=0;i<=p;i++)
    {
        if(list[i].num>1)
        {
            printf("%s:",list[i].a[0]);
            for(int j=1;j<list[i].num;j++)
            {
                printf("%s",list[i].a[j]);
                if(j<list[i].num-1)
                printf(",");
            }
            printf("\n");
        }
    }
    return 0;
}
