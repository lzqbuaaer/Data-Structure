#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct Ch{
    char c;
    int line;
}ch;
int main()
{
    FILE *in=fopen("example.c","r");
    char op[205],a;
    ch s[205];
    int p1=-1,p2=0,num=1;
    s[0].c='\0';
    while((a=fgetc(in))!=EOF)
    {
        if(a=='\'')
        {
            while((a=fgetc(in))!=EOF)
            {
                if(a=='\n')
                num++;
                else if(a=='\'')
                break;
            }
            continue;
        }   
        else if(a=='\"')
        {
            while((a=fgetc(in))!=EOF)
            {
                if(a=='\n')
                num++;
                else if(a=='\"')
                break;
            }
            continue;
        } 
        else if(a=='\n')
        num++;
        else if(a=='/')
        {
            char an=fgetc(in);
            if(an=='/')
            {
                while((a=fgetc(in))!=EOF)
                {
                    if(a=='\n')
                    {
                        num++;
                        break;
                    }
                }
            }
            else if(an=='*')
            {
                while((a=fgetc(in))!=EOF)
                {
                    if(a=='*')
                    {
                        an=fgetc(in);
                        if(an=='/')
                        break;
                        else if(an=='*')
                        {
                            an=fgetc(in);
                            if(an=='/')
                            break;
                        }
                    }
                    if(a=='\n')
                        num++;
                }
            }
            continue;
        }
                if(a=='(')
                {
                    op[p2++]=a;
                    s[++p1].c=a;
                    s[p1].line=num;
                }
                else if(a=='{')
                {
                    if(s[p1].c=='(')
                    {
                        printf("without maching \'%c\' at line %d",s[p1].c,s[p1].line);
                        return 0;
                    }
                    else
                    {
                        op[p2++]=a;
                        s[++p1].c=a;
                        s[p1].line=num;
                    }
                }
                else if(a==')')
                {
                    op[p2++]=a;
                    if(s[p1].c=='(')
                    {
                        s[p1].c='\0';
                        p1--;
                    }
                    else
                    {
                        printf("without maching \'%c\' at line %d",a,num);
                        return 0;
                    }
                }
                else if(a=='}')
                {
                    op[p2++]=a;
                    if(s[p1].c=='{')
                    {
                        s[p1].c='\0';
                        p1--;
                    }
                    else
                    {
                        printf("without maching \'%c\' at line %d",a,num);
                        return 0;
                    }
                }
    }
    if(p1>=0)
    printf("without maching \'%c\' at line %d",s[p1].c,s[p1].line);
    else
    {
        op[p2]='\0';
        printf("%s",op);
    }
    return 0;
}