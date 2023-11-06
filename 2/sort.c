#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char s[105][2][25],t[105][2][25];
int main()
{
    int n,m=0,sum=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%s",s[i][0],s[i][1]);
        m=0;
        for(int j=1;j<i;j++)
        {
            if(strcmp(s[i][1],s[j][1])==0)
            {
                s[i][0][0]='0';
                break;
            }
            else if(strcmp(s[i][0],s[j][0])==0)
            m++;
        }
        if(s[i][0][0]=='0')
        continue;
        else if(m)
        {
            strcpy(t[sum][0],s[i][0]);
            strcpy(t[sum][1],s[i][1]);
            int f=strlen(t[sum][0]);
            t[sum][0][f++]='_';
            t[sum][0][f++]=m+'0';
            t[sum][0][f++]='\0';
            sum++;
        }
        else
        {
            strcpy(t[sum][0],s[i][0]);
            strcpy(t[sum][1],s[i][1]);
            sum++;
        }
    }
    for(int i=0;i<sum;i++)
    {
        for(int j=i+1;j<sum;j++)
        {
            if(strcmp(t[i][0],t[j][0])>0)
            {
                char p[25];
                strcpy(p,t[i][0]);
                strcpy(t[i][0],t[j][0]);
                strcpy(t[j][0],p);
                strcpy(p,t[i][1]);
                strcpy(t[i][1],t[j][1]);
                strcpy(t[j][1],p);
            }
        }
    }
    for(int i=0;i<sum;i++)
    printf("%s %s\n",t[i][0],t[i][1]);
    return 0;
}