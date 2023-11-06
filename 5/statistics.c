#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct node{
    int num;
    char word[100];
    struct node *left,*right;
}node;
typedef node* pnode;
void get(char* s,FILE *in)
{
    int i=0;
    char c='\0';
    while ((c=fgetc(in)) !=EOF)
    {
        if(isalpha(c))
        break;
    }
    while(isalpha(c))
    {
        if(isupper(c))
        c^=32;
        s[i++]=c;
        c=fgetc(in);
    }
    s[i]='\0';
}
pnode insert(pnode T,char *s)
{
    if(T==NULL)
    {
        T=(pnode)malloc(sizeof(node));
        T->left=T->right=NULL;
        T->num=1;
        strcpy(T->word,s);
    }
    else if(strcmp(T->word,s)==0)
    T->num++;
    else if(strcmp(T->word,s)<0)
    T->right=insert(T->right,s);
    else
    T->left=insert(T->left,s);
    return T;
}
void order(pnode T)
{
    if(T->left!=NULL)
    order(T->left);
    printf("%s %d\n",T->word,T->num);
    if(T->right!=NULL)
    order(T->right);
}
int main()
{
    FILE *in=fopen("article.txt","r");
    pnode T=NULL,p;
    char s[100];
    while(1)
    {
        get(s,in);
        if(s[0]=='\0')
        break;
        T=insert(T,s);
    }
    p=T;
    for(int i=1;i<=3&&p!=NULL;i++,p=p->right)
    {
        printf("%s ",p->word);
    }
    printf("\n");
    order(T);
    return 0;
}