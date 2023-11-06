#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node{
    int num,cnt;
    struct node *left,*right;
}node;
typedef node* pnode;
pnode insert(pnode T,int a,int height)
{
    if(T==NULL)
    {
        T=(pnode)malloc(sizeof(node));
        T->num=a;
        T->left=T->right=NULL;
        T->cnt=height;
    }
    else if(T->num>a)
    {
        T->left=insert(T->left,a,height+1);
    }
    else{
        T->right=insert(T->right,a,height+1);
    }
    return T;
}
void order(pnode T)
{
    if(T->left!=NULL)
    order(T->left);
    if(T->left==NULL&&T->right==NULL)
    printf("%d %d\n",T->num,T->cnt);
    if(T->right!=NULL)
    order(T->right);
}
int main()
{
    int n,a;
    pnode T=NULL;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        T=insert(T,a,1);
    }
    order(T);
    return 0;
}