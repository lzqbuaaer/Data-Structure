#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char*find(char*s,char*a)
{
    int i=0;
    for(i=0;i<strlen(s);i++)
    {
        if(tolower(s[i])==a[0])
        {
            for(int j=i+1,k=1;k<strlen(a);j++,k++)
            {
                if(tolower(s[j])!=a[k])
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
    FILE *in=fopen("filein.txt","r");
    FILE *out=fopen("fileout.txt","w");
    char s[100],a[100],b[100],d[100];
    char *p=NULL;
    gets(a);
    gets(b);
    for(int i=0;i<strlen(a);i++)
    tolower(a[i]);
    int la=strlen(a),lb=strlen(b);
    while(fgets(s,100,in)!=NULL)
    {
        p=find(s,a);
        while(p!=NULL)
        {
            strcpy(d,p+la);
            strcpy(p,b);
            strcat(s,d);
            p=find(s,a);
        }
        fputs(s,out);
    }
    fclose(in);
    fclose(out);
    return 0;
}
