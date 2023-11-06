#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int a[25][25];
int main()
{
    int i,j,f=0;
    for(i=1;i<=19;i++)
    {
        for(j=1;j<=19;j++)
        scanf("%d",&a[i][j]);
    }
    for(i=1;i<=19;i++)
    {
        for(j=1;j<=16;j++)
        {
            if(a[i][j])
            {
                if(a[i][j]==a[i][j+1]&&a[i][j+1]==a[i][j+2]&&a[i][j+2]==a[i][j+3])
                {
                    if(2<=j&&j<=15)
                    {
                        if(a[i][j-1]==0||a[i][j+4]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else if(j==1)
                    {
                        if(a[i][j+4]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else if(j==16)
                    {
                        if(a[i][j-1]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                }
            }
        }
    }
    for(j=1;j<=19;j++)
    {
        for(i=1;i<=16;i++)
        {
            if(a[i][j])
            {
                if(a[i+1][j]==a[i][j]&&a[i+2][j]==a[i+1][j]&&a[i+2][j]==a[i+3][j])
                {
                    if(2<=i&&i<=15)
                    {
                        if(a[i-1][j]==0||a[i+4][j]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else if(i==1)
                    {
                        if(a[i+4][j]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else if(i==16)
                    {
                        if(a[i-1][j]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                }
            }
        }
    }
    for(i=1;i<=16;i++)
    {
        for(j=1;j<=16;j++)
        {
            if(a[i][j])
            {
                if(a[i][j]==a[i+1][j+1]&&a[i+1][j+1]==a[i+2][j+2]&&a[i+2][j+2]==a[i+3][j+3])
                {
                    if((2<=j&&j<=15)&&(2<=i&&i<=15))
                    {
                        if(a[i-1][j-1]==0||a[i+4][j+4]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else if(j==1||i==1)
                    {
                        if(i==16||j==16)
                        break;
                        else if(a[i+4][j+4]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else if(j==16||i==16)
                    {
                        if(a[i-1][j-1]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                }
            }
        }
    }
    for(i=1;i<=16;i++)
    {
        for(j=4;j<=19;j++)
        {
            if(a[i][j])
            {
                if(a[i][j]==a[i+1][j-1]&&a[i+1][j-1]==a[i+2][j-2]&&a[i+2][j-2]==a[i+3][j-3])
                {
                    if((5<=j&&j<=19)&&(2<=i&&i<=15))
                    {
                        if(a[i-1][j+1]==0||a[i+4][j-4]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else if(j==19||i==1)
                    {
                        if(j==4||i==16)
                        break;
                        else if(a[i+4][j-4]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                    else
                    {
                        if(a[i-1][j+1]==0)
                        printf("%d:%d,%d\n",a[i][j],i,j),f=1;
                    }
                }
            }
        }
    }
    if(f==0)
    printf("No\n");
    return 0;
}