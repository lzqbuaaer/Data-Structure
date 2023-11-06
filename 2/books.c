#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct Book{
    char name[60];
    char author[25];
    char press[35];
    char date[15];
    struct Book *next;
} book;
typedef struct Book* bptr;
char*find(char*s,char*a)
{
    int i=0;
    for(i=0;i<strlen(s);i++)
    {
        if(tolower(s[i])==tolower(a[0]))
        {
            for(int j=i+1,k=1;k<strlen(a);j++,k++)
            {
                if(tolower(s[j])!=tolower(a[k]))
                break;
                else{
                    if(k==strlen(a)-1)
                    return &s[i];
                }
            }
        }
    }
    return NULL;
}
int main()
{
    FILE *in=fopen("books.txt","r");
    FILE *out=fopen("ordered.txt","w");
    char f[60];
    bptr s=NULL,list=NULL;
    s=(bptr)malloc(sizeof(book));
    while(fscanf(in,"%s%s%s%s",s->name,s->author,s->press,s->date)!=EOF)
    {
        if(list==NULL)
        {
            list=(bptr)malloc(sizeof(book));
            strcpy(list->name,s->name);
            strcpy(list->author,s->author);
            strcpy(list->press,s->press);
            strcpy(list->date,s->date);
            list->next=NULL;
        }
        else
        {
            bptr t=(bptr)malloc(sizeof(book));
            strcpy(t->name,s->name);
            strcpy(t->author,s->author);
            strcpy(t->press,s->press);
            strcpy(t->date,s->date);
            t->next=NULL;
            for(bptr q=list,q0;q!=NULL;q0=q,q=q->next)
            {
                if(strcmp(q->name,t->name)>0)
                {
                    if(q==list)
                    {                       
                        t->next=q;
                        list=t;                    
                    }
                    else
                    {
                        q0->next=t;
                        t->next=q;
                    }
                    break;
                }
                else if(q->next==NULL)
                {
                    q->next=t;
                    t->next=NULL;
                    break;
                }
            }
        }
    }
    int n;
    while(1)
    {
        scanf("%d",&n);
        if(1==n)
        {
            scanf("%s%s%s%s",s->name,s->author,s->press,s->date);
            if(list==NULL)
            {
                list=(bptr)malloc(sizeof(book));
                strcpy(list->name,s->name);
                strcpy(list->author,s->author);
                strcpy(list->press,s->press);
                strcpy(list->date,s->date);
                list->next=NULL;
            }
            else
            {
                bptr t=(bptr)malloc(sizeof(book));
                strcpy(t->name,s->name);
                strcpy(t->author,s->author);
                strcpy(t->press,s->press);
                strcpy(t->date,s->date);
                t->next=NULL;
                for(bptr q=list,q0=NULL;q!=NULL;q0=q,q=q->next)
                {
                    if(strcmp(q->name,s->name)>0)
                    {
                        if(q==list)
                        {                       
                            t->next=list;
                            list=t;                    
                        }                      
                        else
                        {
                            q0->next=t;
                            t->next=q;
                        }
                        break;
                    }
                    else if(q->next==NULL)
                    {
                        q->next=t;
                        t->next=NULL;
                        q=t;
                    }
                }
            }
        }
        else if(2==n)
        {
            scanf("%s",f);
            for(bptr q=list;q!=NULL;q=q->next)
            {
                if(find(q->name,f)!=NULL)
                printf("%-50s %-20s %-30s %-10s\n",q->name,q->author,q->press,q->date);
            }
        }
        else if(3==n){
            scanf("%s",f);
            for(bptr q=list,q0=list;q!=NULL;q0=q,q=q->next)
            {
                if(find(q->name,f)!=NULL)
                {
                    if(q==list)
                    {
                        if(list->next=NULL)
                        list=NULL;
                        else
                        list=list->next;
                    }
                    else if(q->next!=NULL)
                    {
                        q0->next=q->next;
                        q=q0;
                    }
                    else{
                        q0->next=NULL;
                        break;
                    }
                }
            }
        }
        else
        break;
    }
    for(bptr q=list;q!=NULL;q=q->next)
    {
        fprintf(out,"%-49s %-19s %-29s %-9s\n",q->name,q->author,q->press,q->date);
    }
    return 0;
}