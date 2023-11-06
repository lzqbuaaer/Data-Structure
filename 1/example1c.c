#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char s[10000],a[10000],b[1000];
int c[1000];
int main()
{
    gets(a);
    int i,j;
    for(i=j=0;a[i]!='\0';i++)
    {
        if(a[i]!=' ')
        s[j++]=a[i];
    }
    s[j]='\0';
    int k=0,num=0,ans=0;
    j=0;
    for(i=0;i<=strlen(s)-1;i++)
    {
        if(s[i]=='=')
        break;
        else if(s[i]=='+'||s[i]=='-')
        b[j++]=s[i];
        else if(isdigit(s[i]))
        {
            num=s[i]-48;
            while(isdigit(s[i+1]))
                num=num*10+s[++i]-48;
            c[k++]=num;
            num=0;
        }
        else if(s[i]=='*')
        {
            num=s[++i]-48;
            while(isdigit(s[i+1]))
                num=num*10+s[++i]-48;
            c[k-1]*=num;
            num=0;
        }
        else if(s[i]=='/')
        {
            num=s[++i]-48;
            while(isdigit(s[i+1]))
                num=num*10+s[++i]-48;
            c[k-1]/=num;
            num=0;
        }
    }
    ans=c[0];
    for(i=1,j=0;i<k;i++,j++)
    {
        if(b[j]=='+')
        ans+=c[i];
        else ans-=c[i];
    }
    printf("%d",ans);
    return 0;
}