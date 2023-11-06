#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef  struct Oper{
    int op,pos;
    char str[520];
}oper;
oper a[50];
void insert(char *s,int pos,char *str)
{
    char s1[520];
    strcpy(s1,s+pos);
    s[pos]='\0';
    strcat(s,str);
    strcat(s,s1);
}
void delete(char*s,int pos,int len)
{
    char s1[520];
    strcpy(s1,s+pos+len);
    s[pos]='\0';
    strcat(s,s1);
}
int main()
{
    char s[520];
    gets(s);
    int n,p=-1;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%s",&a[i].op,&a[i].pos,a[i].str);
        p++;
    }
    while(1)
    {
        scanf("%d",&n);
        if(-1==n)
        break;
        else if(1==n)
        {
            p++;
            a[p].op=1;
            scanf("%d%s",&a[p].pos,a[p].str);
            insert(s,a[p].pos,a[p].str);
        }
        else if(2==n)
        {
            p++;
            a[p].op=2;
            int len;
            scanf("%d%d",&a[p].pos,&len);
            strncpy(a[p].str,s+a[p].pos,len);
            delete(s,a[p].pos,len);
        }
        else if(3==n)
        {
            if(a[p].op==1)
            delete(s,a[p].pos,strlen(a[p].str));
            else
            insert(s,a[p].pos,a[p].str);
            p--;
        }
    }
    printf("%s",s);
    return 0;
}