#include<stdio.h>
#include<string.h>
#include<ctype.h>
char s[1000000],ans[1000000];
int main()
{
    int i,j;
    scanf("%s",s);
    for(i=j=0;i<strlen(s);i++)
    {
        if(s[i]=='-')
        {
            if((isdigit(s[i-1])&&isdigit(s[i+1]))||isupper(s[i-1])&&isupper(s[i+1])||islower(s[i-1])&&islower(s[i+1]))
            {
                if(s[i-1]<s[i+1])
                {
                    for(int k=s[i-1]+1;k<s[i+1];k++)
                    ans[j++]=k;
                }
                else
                ans[j++]=s[i];
            }
            else
            ans[j++]=s[i];
        }
        else
        ans[j++]=s[i];
    }
    ans[j]='\0';
    printf("%s",ans);
    return 0;
}