#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int main()
{
    char s[1000];
    int sym[500],op[500];
    gets(s);
    int num,p1=-1,p2=-1;
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==' ')
        continue;
        else if(isalnum(s[i]))
        {
            num=s[i]-'0';
            while(isalnum(s[i+1]))
            {
                num=num*10+s[i+1]-'0';
                i++;
            }
            op[++p1]=num;
        }
        else if(s[i]=='+'||s[i]=='-')
        {
            while(p2>=0&&sym[p2]!=-5)
            {
                op[++p1]=sym[p2];
                p2--;
            }
            if(s[i]=='+') sym[++p2]=-1;
            else sym[++p2]=-2;
        }
        else if(s[i]=='*'||s[i]=='/')
        {
            while(p2>=0&&sym[p2]!=-5&&sym[p2]!=-1&&sym[p2]!=-2)
            {
                op[++p1]=sym[p2];
                p2--;
            }
            if(s[i]=='*') sym[++p2]=-3;
            else sym[++p2]=-4;
        }
        else if(s[i]=='(')
        sym[++p2]=-5;
        else if(s[i]==')')
        {
            while(p2>=0&&sym[p2]!=-5)
            {
                op[++p1]=sym[p2];
                p2--;
            }
            p2--;
        }
        else if(s[i]=='=')
        {
            while(p2>=0)
            {
                op[++p1]=sym[p2];
                p2--;
            }
            op[++p1]=-7;
        }
    }
    double ans[500],a,b;
    int p=-1;
    for(int i=0;op[i]!=-7;i++)
    {
        if(op[i]>=0)
        ans[++p]=op[i];
        else{
            switch (op[i])
            {
                case -1:
                a=ans[p--];
                b=ans[p--];
                ans[++p]=b+a;
                break;
                case -2:
                a=ans[p--];
                b=ans[p--];
                ans[++p]=b-a;
                break;
                case -3:
                a=ans[p--];
                b=ans[p--];
                ans[++p]=b*a;
                break;
                case -4:
                a=ans[p--];
                b=ans[p--];
                ans[++p]=b/a;
                break;
            }
        }
    }
    printf("%.2lf",ans[0]);
    return 0;
}