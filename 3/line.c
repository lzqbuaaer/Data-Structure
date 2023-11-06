#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct Line
{
    int x1,y1,x2,y2;
    struct Line* link;
} line;
typedef line* lptr;
int len(lptr a)
{
    int cnt=1;
    while(a->link!=NULL)
    {
        cnt++;
        a=a->link;
    }
    return cnt;
}
int main()
{
    lptr list[200];
    int p=0,n,x,y,s,t;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        list[i]=(lptr)malloc(sizeof(line));
        scanf("%d%d%d%d",&(list[i]->x1),&(list[i]->y1),&(list[i]->x2),&(list[i]->y2));
        list[i]->link=NULL;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j)
            continue;
            else{
                if(list[i]->x2==list[j]->x1&&list[i]->y2==list[j]->y1)
                {
                    list[i]->link=list[j];
                }
            }
        }
    }
    int max=0;
    lptr l_max=NULL;
    for(int i=1;i<=n;i++)
    {
        if(max<len(list[i]))
        {
            max=len(list[i]);
            l_max=list[i];
        }
    }
    printf("%d %d %d",max,l_max->x1,l_max->y1);
    return 0;
}