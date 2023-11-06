#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct Memory{
    int address;
    int width;
    struct Memory* next;
}memory;
typedef memory* mptr;
int num(mptr a)
{
    if(a==NULL)
    return 0;
    int cnt=1;
    mptr b=a;
    while(a->next!=b)
    {
        cnt++;
        a=a->next;
    }
    return cnt;
}
mptr find(int ads,mptr ptr)
{
    mptr p=NULL,t=ptr;
    int cnt=900000000;
    if(t->width==ads)
    return ptr;
    else if(t->width>ads)
    {
        cnt=t->width;
        p=ptr;
    }
    t=t->next;
    while(t!=ptr)
    {
        if(t->width==ads)
        return t;
        else if(t->width>ads)
        {
            if(t->width<cnt)
            {
                p=t;
                cnt=t->width;
            }
        }
        t=t->next;
    }
    return p;
}
int main()
{
    int n;
    scanf("%d",&n);
    mptr q,p=(mptr)malloc(sizeof(memory)),s=NULL;
    q=p;
    scanf("%d%d",&(p->address),&(p->width));
    for(int i=1;i<n;i++)
    {
        s=(mptr)malloc(sizeof(memory));
        scanf("%d%d",&(s->address),&(s->width));
        s->next=NULL;
        q->next=s;
        q=q->next;
    }
    q->next=p;
    int ads;
    while(1)
    {
        scanf("%d",&ads);
        if(ads==-1)
        break;
        mptr ptr=find(ads,p);
        if(ptr==NULL)
        continue;
        if(ptr->width>ads)
        {
            ptr->width-=ads;
            p=ptr;
        }
        else{
            if(num(p)>1)
            {
                mptr t=ptr;
                while(t->next!=ptr)
                t=t->next;
                p=t->next=ptr->next;
                free(ptr);
            }
            else 
            {
                p=NULL;
                break;
            }
        }
    }
    if(num(p)>0)
    {
        mptr i=p;
        do{
            printf("%d %d\n",i->address,i->width);
            i=i->next;
        }while(i!=p);
    }
    return 0;
}