#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define max(a,b) a>b?a:b
typedef struct infor{
    int num;
    char name[25];
    int seat;
}inf;
int cmp1(const void* a,const void* b){
    inf x=*(inf*)a,y=*(inf*)b;
    if(x.seat<y.seat) return -1;
    else if(x.seat>y.seat) return 1;
    else{
        if(x.num<y.num) return -1;
    else return 1;
    }
}
int cmp2(const void* a,const void* b){
    inf x=*(inf*)a,y=*(inf*)b;
    if(x.num<y.num) return -1;
    else return 1;
}
int main(){
    inf stu[200];
    int f[200]={0};
    FILE* in=fopen("in.txt","r");
    FILE* out=fopen("out.txt","w");
    int tal;
    scanf("%d",&tal);
    for(int i=0;i<tal;i++){
        fscanf(in,"%d %s %d",&stu[i].num,stu[i].name,&stu[i].seat);
        f[stu[i].seat]=1;
    }
    qsort(stu,tal,sizeof(stu[0]),cmp1);
    int m=stu[tal-1].seat;
    int q=max(tal,m);
    int p=tal-1;
    for(int i=1;i<q;i++){
        if(f[i]==0){
            if(stu[p].seat>i)
            stu[p--].seat=i;
            else break;
        }
    }
    qsort(stu,tal,sizeof(stu[0]),cmp1);
    m=0;
    for(int i=0;i<tal;i++)
    m=max(m,stu[i].seat);
    int sta=1;
    for(int i=0;i<tal;i++){
        if(stu[i].seat==sta)
        sta++;
        else{
            stu[i].seat=m+1;
            m++;
        }
    }
    qsort(stu,tal,sizeof(stu[0]),cmp2);
    for(int i=0;i<tal;i++){
        fprintf(out,"%d %s %d\n",stu[i].num,stu[i].name,stu[i].seat);
    }
    return 0;
}