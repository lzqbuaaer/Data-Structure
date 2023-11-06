#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int main()
{
    char s[100],a[100];
    int b[30]={0};
    FILE *in=fopen("encrypt.txt","r");
    FILE *out=fopen("output.txt","w");
    gets(a);
    for(int i=0;i<strlen(a);i++)
    {
        if(b[a[i]-'a']==0)
        b[a[i]-'a']++;
        else{
            for(int j=i;j<strlen(a);j++)
            a[j]=a[j+1];
            i--;
        }
    }
    int m=strlen(a);
    for(int i=25;i>=0;i--)
    {
        if(!b[i])
        a[m++]='a'+i;
    }
    while(fgets(s,100,in)!=NULL)
    {
        for(int i=0;i<strlen(s);i++)
        {
            if(isalpha(s[i]))
            s[i]=a[s[i]-'a'];
        }
        fputs(s,out);
    }
    return 0;
}