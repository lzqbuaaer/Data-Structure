#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int main()
{
    int s[105]={0},front=-1,a;
    while(scanf("%d",&a)!=EOF)
    {
        if(a==1)
        {
            scanf("%d",&a);
            if(front<100)
            s[++front]=a;
            else
            printf("error ");
        }
        else if(a==0)
        {
            if(front!=-1)
            {
                printf("%d ",s[front]);
                s[front]=0;
                front--;
            }
            else 
            printf("error ");
        }
        else if(a==-1)
        break;
    }
    return 0;
}