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
int main()
{
    char f[1000];
    bptr s=(bptr)malloc(sizeof(book));
    FILE *in=fopen("books.txt","r");
    while(fscanf(in,"%s%s%s%s",s->name,s->author,s->press,s->date)!=EOF);
    while(gets(f)!=NULL)
    {
        puts(f);
    }
    return 0;
}