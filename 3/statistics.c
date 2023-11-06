#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct Word{
    char w[100];
    int cnt;
}word;
typedef word* wptr;
int cmp(const void*p1,const void*p2)
{
    wptr a=(wptr)p1,b=(wptr)p2;
    if(strcmp(a->w,b->w)>0) return 1;
    else return -1;
}
int main()
{
    FILE *in=fopen("article.txt","r");
    word sta[1000];
    int p=0;
    char s[100],c;
    while(fscanf(in,"%c",&c)!=EOF)
    {
        if(isalpha(c))
        {
            c=tolower(c);
            int t=0;
            s[t++]=c;
            while(1)
            {
                fscanf(in,"%c",&c);
                if(!isalpha(c))
                break;
                c=tolower(c);
                s[t++]=c;
            }
            s[t++]='\0';
            int flag=0;
            for(int i=0;i<p;i++)
            {
                if(strcmp(s,sta[i].w)==0)
                {
                    flag=1;
                    sta[i].cnt++;
                }
            }
            if(!flag)
            {
                sta[p].cnt=1;
                strcpy(sta[p].w,s);
                p++;
            }
        }
    }
    qsort(sta,p,sizeof(word),cmp);
    for(int i=0;i<p;i++)
    printf("%s %d\n",sta[i].w,sta[i].cnt);
    return 0;
}