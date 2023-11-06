#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int n,k,cnt=0;
int s[200];
void adjust(int k[ ],int i,int n)
{
    int j,temp;
    temp=k[i];
    j=2*i+1;
    while(j<n){
        if(j<n-1 && k[j]<k[j+1])
            j++;
        cnt++;
        if(temp>=k[j]) 
            break;
        k[(j-1)/2]=k[j];
        j=2*j+1;
    }
    k[(j-1)/2]=temp;
}
void merge(int x[ ],int tmp[ ],int left,int leftend,int rightend)
{     
    int i=left, j=leftend+1, q=left;
    while(i<=leftend && j<=rightend)
    {
        cnt++;
        if(x[i]<=x[j]) 
            tmp[q++]=x[i++];
        else
            tmp[q++]=x[j++];
    }
    while(i<=leftend)
        tmp[q++]=x[i++];
    while(j<=rightend)
        tmp[q++]=x[j++];
    for(i=left; i<=rightend; i++)
        x[i]=tmp[i];
}
void mSort(int k[], int tmp[], int left, int right)
{
    int center;
    if(left < right){
        center = (left+right)/2;
        mSort(k, tmp, left, center);
        mSort(k, tmp, center+1, right);
        merge(k, tmp, left,center, right);
    }
}
void swap(int*a,int*b){
    int t=*a;
    *a=*b;
    *b=t;
}
void quickSort(int k[ ],int left,int right)
{     
    int i, last;
    if(left<right){
        last=left; 
        for(i=left+1;i<=right;i++){
            cnt++;
            if(k[i]<k[left])
                swap(&k[++last],&k[i]); 
        }
        swap(&k[left],&k[last]);
        quickSort(k,left,last-1); 
        quickSort(k,last+1,right);   
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++)
    scanf("%d",&s[i]);
    if(1==k){//选择排序
        int min=s[0];
        int p=0;
        for(int i=0;i<n-1;i++){
            min=s[i];
            p=i;
            for(int j=i+1;j<n;j++){
                cnt++;
                if(min>s[j])
                min=s[j],p=j;
            }
            int t=s[p];
            s[p]=s[i];
            s[i]=t;
        }
    }
    else if(2==k){//冒泡排序
        int flag=1;
        for(int i=n-1;i>0&&flag==1; i--){
            flag=0;
            for(int j=0;j<i;j++){
                cnt++;
                if(s[j]>s[j+1]){
                    int t=s[j];
                    s[j]=s[j+1];
                    s[j+1]=t;
                    flag=1;
                }
            }
        }
    }
    else if(3==k){//堆排序
        int i,temp;
        for(int i=n/2-1;i>=0;i--)
        adjust(s,i,n);
        for(i=n-1;i>=1;i--){
            temp=s[i];
            s[i]=s[0];
            s[0]=temp;
            adjust(s,0,i);
       }
    }
    else if(4==k){//归并排序
        int *tmp;
        tmp=(int *)malloc(sizeof(int)*n);
        mSort(s,tmp,0,n-1);
        free(tmp);
    }
    else if(5==k){//快速排序
        quickSort(s,0,n-1);
    }
    for(int i=0;i<n;i++)
    printf("%d ",s[i]);
    printf("\n%d",cnt);
    return 0;
}