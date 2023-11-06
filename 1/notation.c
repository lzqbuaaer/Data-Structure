#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char s[100000];
int main()
{
    scanf("%s",s);
    char*p=strstr(s,".");
    int dis=p-s;
    if(dis>1||(dis==1&&s[0]!='0'))
    {
        printf("%c.",s[0]);
        for(int i=1;s[i]!='\0';i++)
        {
            if(s[i]!='.')
            printf("%c",s[i]);
        }
        printf("e%d",dis-1);
    }
    else{
        int i;
        for(i=0;;i++)
        {
            if('0'<s[i]&&s[i]<='9')
            break;
        }
        int a=i;
        printf("%c",s[i++]);
        if(s[i]!='\0')
        printf(".");
        while(s[i]!='\0')
        printf("%c",s[i++]);
        printf("e-%d",a-1);
    }
    return 0;
}