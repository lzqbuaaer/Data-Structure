#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct Key{
    char c;
    struct Key* next;
}key;
typedef key* kp;
int sch(kp kw,char ch)
{
    kp t=kw;
    while(t!=NULL)
    {
        if(t->c==ch)
        return 1;
        t=t->next;
    }
    return 0;
}
int main()
{
    FILE *in=fopen("in.txt","r");
    FILE *out=fopen("in_crpyt.txt","w");
    char s[100];
    gets(s);
    kp kw=NULL;
    kp p=kw;
    for(int i=0;i<strlen(s);i++)
    {
        if(!sch(kw,s[i]))
        {
            kp t=(kp)malloc(sizeof(key));
            t->c=s[i];
            t->next=NULL;
            if(kw==NULL)
            p=kw=t;
            else
            {
                p->next=t;
                p=p->next;
            }
        }
    }
    for(char ch=' ';ch<=126;ch++)
    {
        if(!sch(kw,ch))
        {
            kp t=(kp)malloc(sizeof(key));
            t->c=ch;
            t->next=NULL;
            p->next=t;
            p=p->next;
        }
    }
    p->next=kw;
    int num=95,last=kw->c;
    char table[150];
    while(num>1)
    {
        int n=kw->c;
        p->next=kw->next;
        free(kw);
        kw=p->next;
        for(int i=1;i<n;i++,p=kw,kw=kw->next);
        table[n]=kw->c;
        num--;
    }
    table[kw->c]=last;
    char word;
    while(fscanf(in,"%c",&word)!=EOF)
    {
        if(word>=32&&word<=126)
        word=table[word];
        fprintf(out,"%c",word);
    }
    return 0;
}