#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int coe;
    int pow;
    struct Node* next;
};
typedef struct Node node;
typedef struct Node* nodeptr;
int main()
{
    nodeptr list1=NULL,list2=NULL,p=NULL,q=NULL,p0=NULL,ret=NULL;
    ret=(nodeptr)malloc(sizeof(node));
    ret->coe=0;
    ret->pow=0;
    ret->next=NULL;
    int c,po;
    char a;
    do{//将第一个多项式存入链表
        scanf(" %d %d%c",&c,&po,&a);
        q=(nodeptr)malloc(sizeof(node));//创建一个结点
        q->coe=c;
        q->pow=po;
        q->next=NULL;
        if(list1==NULL)
        list1=p=q;
        else{//更新p
            p->next=q;
            p=p->next;
        }
    }
    while(a!='\n');
    do{//将第二个多项式存入链表
        scanf(" %d %d%c",&c,&po,&a);
        q=(nodeptr)malloc(sizeof(node));//创建一个结点
        q->coe=c;
        q->pow=po;
        q->next=NULL;
        if(list2==NULL)
        list2=p=q;
        else{//更新p
            p->next=q;
            p=p->next;
        }
    }
    while(a!='\n');
    for(nodeptr i=list1;i!=NULL;i=i->next)
    {
        for(nodeptr j=list2;j!=NULL;j=j->next)
        {
            nodeptr ans;
            ans=(nodeptr)malloc(sizeof(node));
            ans->coe=(i->coe)*(j->coe);
            ans->pow=i->pow+j->pow;
            ans->next=NULL;
            for(p=ret;p!=NULL;p0=p,p=p->next)
        {
            if(ans->pow>p->pow){//将q插到p前
                if(p==ret)
                {
                    ret=ans;
                    ans->next=p;
                    break;
                }
                else
                {
                    p0->next=ans;
                    ans->next=p;
                    break;
                }
            }
            else if(ans->pow==p->pow){//合并同类项
                p->coe+=ans->coe;
                break;
            }
            else if(p->next==NULL){//将q插入结尾
                p->next=ans;
                break;
            }
        }
        }
    }
    for(p=ret;p!=NULL;p=p->next)//打印结果
    {
        if(p->coe!=0)
        printf("%d %d ",p->coe,p->pow);
    }
    return 0;
}