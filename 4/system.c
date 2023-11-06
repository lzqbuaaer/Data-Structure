#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct People{
    int need,time,ans;
}people;
typedef struct Win{
    int num,need;
}win;
int main()
{
    int n,t=0,c=3,f=0,r=-1;
    people q[90000];
    win wdw[5]={-1,0,-1,0,-1,0,-1,0,-1,0};
    scanf("%d",&n);
    int a[500];
    for(int i=1;i<=n;i++)
    scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=a[i];j++)
        {
            r++;
            scanf("%d",&q[r].need);
            q[r].time=i;
        }
        while(c<5&&(r-f+1)>=c*7)
        c++;
        for(int k=0;k<c;k++)
        {
            if(wdw[k].need==0)
            {
                if(f<=r)
                {
                    wdw[k].num=f;                
                    wdw[k].need=q[f].need-1;
                    q[f].ans=t-q[f].time+1;
                    f++;
                }
            }
            else wdw[k].need--;
        }
        t++;
        while(c>3&&r-f+1<c*7)
        c--;
    }
    while(r>=f)
    {
        for(int k=0;k<c;k++)
        {
            if(wdw[k].need==0)
            {
                if(f<=r)
                {
                    wdw[k].num=f;                
                    wdw[k].need=q[f].need-1;
                    q[f].ans=t-q[f].time+1;
                    f++;
                }
            }
            else wdw[k].need--;
        }
        t++;
        while(c>3&&r-f+1<c*7)
        c--;
    }
    for(int i=0;i<=r;i++)
    printf("%d : %d\n",i+1,q[i].ans);
    return 0;
}