#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct Enter{
    int num;
    char path[1000];
}enter;
typedef struct People{
    int num,cnt;
}people;
int cmp1(const void* a,const void* b)
{
    enter* x=(enter*)a,* y=(enter*)b;
    int lx=strlen(x->path),ly=strlen(y->path);
    if(lx<ly) return -1;
    else if(lx>ly) return 1;
    else{
        int i=strcmp(x->path,y->path);
        if(i>0) return 1;
        else return -1;
    }
}
int cmp2(const void* a,const void* b)
{
    people* x=(people*)a,* y=(people*)b;
    if(x->cnt<y->cnt) return 1;
    else if(x->cnt>y->cnt) return -1;
    else if(x->num<y->num) return -1;
    else return 1;
}
int main()
{
    enter etr[1000];
    char branch[1000][1000];
    branch[100][0]='\0';
    int r,s1,s2,s3,s,p=0;
    while(scanf("%d",&r))
    {
        if(r==-1) break;
        scanf("%d%d",&s1,&s2);
        int l=strlen(branch[r]);
        if(s2<0)
        {
            strcpy(branch[s1],branch[r]);
            branch[s1][l]='1';
            if(s1<100)
            {
                etr[p].num=s1;
                strcpy(etr[p].path,branch[s1]);
                p++;
            }
        }
        else{
            scanf("%d",&s3);
            if(s3>0)
            {
                scanf("%d",&s);
                strcpy(branch[s1],branch[r]);
                strcpy(branch[s2],branch[r]);
                strcpy(branch[s3],branch[r]);
                branch[s1][l]='1';
                branch[s2][l]='2';
                branch[s3][l]='3';
                if(s1<100)
                {
                    etr[p].num=s1;
                    strcpy(etr[p].path,branch[s1]);
                    p++;
                }
                if(s2<100)
                {
                    etr[p].num=s2;
                    strcpy(etr[p].path,branch[s2]);
                    p++;
                }
                if(s3<100)
                {
                    etr[p].num=s3;
                    strcpy(etr[p].path,branch[s3]);
                    p++;
                }
            }
            else 
            {
                strcpy(branch[s1],branch[r]);
                strcpy(branch[s2],branch[r]);
                branch[s1][l]='1';
                branch[s2][l]='3';
                if(s1<100)
                {
                    etr[p].num=s1;
                    strcpy(etr[p].path,branch[s1]);
                    p++;
                }
                if(s2<100)
                {   
                    etr[p].num=s2;
                    strcpy(etr[p].path,branch[s2]);
                    p++;
                }
            }
        }
    }
    qsort(etr,p,sizeof(etr[0]),cmp1);
    people order[1000];
    int p1=0,a,b;
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        order[p1].num=a;
        order[p1].cnt=b;
        p1++;
    }
    qsort(order,p1,sizeof(order[0]),cmp2);
    for(int i=0;i<p;i++)
    {
        printf("%d->%d\n",order[i].num,etr[i].num);
    }
    return 0;
}
// 100 101 102 103 -1
// 103 3 4 5 -1
// 102 104 -1
// 101 6 7 8 -1
// 104 1 2 -1
// -1
// 5 1001
// 2 895
// 4 2850
// 1 3250
// 8 1860
// 3 795
// 7 1200
// 6 985