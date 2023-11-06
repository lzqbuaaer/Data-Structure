#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct ch{
    int ans;
    int num;
    struct ch* lchild,* rchild;
}factor;
typedef factor* ptrf;
char turn(ptrf a)
{
    if(a->num==-1) return '+';
    else if(a->num==-2) return '-';
    else if(a->num==-3) return '*';
    else if(a->num==-4) return '/';
    else return a->num+48;
}
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
    ptrf t[100],a,b,c;
    int p=-1;
    for(int i=0;op[i]!=-7;i++)
    {
        if(op[i]>0)
        {
            p++;
            t[p]=(ptrf)malloc(sizeof(factor));
            t[p]->ans=t[p]->num=op[i];
            t[p]->lchild=t[p]->rchild=NULL;
        }
        else{
            switch (op[i])
            {
                case -1:
                a=t[p--];
                b=t[p];
                c=(ptrf)malloc(sizeof(factor));
                c->ans=b->ans+a->ans;
                c->num=-1;
                c->lchild=b;
                c->rchild=a;
                t[p]=c;
                break;
                case -2:
                a=t[p--];
                b=t[p];
                c=(ptrf)malloc(sizeof(factor));
                c->ans=b->ans-a->ans;
                c->num=-2;
                c->lchild=b;
                c->rchild=a;
                t[p]=c;
                break;
                case -3:
                a=t[p--];
                b=t[p];
                c=(ptrf)malloc(sizeof(factor));
                c->ans=b->ans*a->ans;
                c->num=-3;
                c->lchild=b;
                c->rchild=a;
                t[p]=c;
                break;
                case -4:
                a=t[p--];
                b=t[p];
                c=(ptrf)malloc(sizeof(factor));
                c->ans=b->ans/a->ans;
                c->num=-4;
                c->lchild=b;
                c->rchild=a;
                t[p]=c;
                break;
            }
        }
    }
    char x=turn(t[0]),y=turn(t[0]->lchild),z=turn(t[0]->rchild);
    printf("%c %c %c\n%d",x,y,z,t[0]->ans);
    return 0;
}