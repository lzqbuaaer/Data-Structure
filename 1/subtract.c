#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char a[100],b[100],c[100],d[100];
int ans;
void invert(char *str)
{
    int i,j,k;
    for(i=0,j=strlen(str)-1;i<j;i++,j--)
    {
        k=str[i];
        str[i]=str[j];
        str[j]=k;
    }
}
int compare(char*a,char*b)
{
    if(strlen(a)>strlen(b))
    return 1;
    else if(strlen(a)<strlen(b))
    return -1;
    char*p=a+strlen(a)-1,*q=b+strlen(b)-1;
    while(p!=(a-1))
    {
        if(*p>*q)
        return 1;
        else if(*p<*q)
        return -1;
        p--;
        q--;
    }
    return 0;
}
int main()
{
    int i=0,j=0;
    scanf("%s",a);
    scanf("%s",b);
    char*p=a;
    while(*p=='0')
    p++;
    while(*p!='\0')
    c[i++]=*(p++);
    p=b;
    while(*p=='0')
    p++;
    while(*p!='\0')
    d[j++]=*(p++);
    invert(c);
    invert(d);
    int comp=compare(c,d);
    if(comp>0)
    {
        for(i=0;i<strlen(d);i++)
        {
            ans=c[i]-d[i];
            if(ans<0)
            {
                ans+=10;
                c[i]=ans+48;
                c[i+1]--;
                j=i+1;
                while(c[j]<'0')
                {
                    c[j]+=10;
                    j++;
                    c[j]--;
                }
            }
            else 
            c[i]=ans+48;
        }
        for(i=strlen(c)-1;i>=0;i--)
        {
            if(c[i]!='0')
            break;
        }
        for(i;i>=0;i--)
        printf("%c",c[i]);
    }
    else if(comp<0)
    {
         for(i=0;i<strlen(c);i++)
        {
            ans=d[i]-c[i];
            if(ans<0)
            {
                ans+=10;
                d[i]=ans+48;
                d[i+1]--;
                j=i+1;
                while(d[j]<'0')
                {
                    d[j]+=10;
                    j++;
                    d[j]--;
                }
            }
            else 
            d[i]=ans+48;
        }
        for(i=strlen(d)-1;i>=0;i--)
        {
            if(d[i]!='0')
            break;
        }
        printf("-");
        for(i;i>=0;i--)
        printf("%c",d[i]);
    }
    else 
    printf("0");
    return 0;
}