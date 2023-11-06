#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXVER  512
#define INFINITY   32767
int edges[MAXVER],p=0;
int cnt=0;
int weights[MAXVER][MAXVER];
int name[MAXVER][MAXVER];
int edges[MAXVER]={0};
void Prim(int  weights[][ MAXVER], int n, int src, int edges[ ])
{ //weights为权重数组、n为顶点个数、src为最小树的第一个顶点、edge为最小生成树边
    int minweight [MAXVER], min;
    int i, j, k;
    for(i=0; i<n; i++){  //初始化相关数组
        minweight[i] = weights[src][i];  //将src顶点与之有边的权值存入数组
        edges[i]  = src;  //初始时所有顶点的前序顶点设为src，(src,i）
    }
    minweight[src]  = 0;   //将第一个顶点src顶点加入生成树
    for(i=1; i< n; i++){
        min = INFINITY;
        for(j=0, k=0;  j<n; j++)
            if(minweight[j] !=0 && minweight[j] < min) {  //在数组中找最小值，其下标为k
                min = minweight[j];  k = j;
            }
        minweight[k] = 0;  //找到最小树的一个顶点
        for(j=0;  j<n; j++) 
            if(minweight[j] != 0 && weights[k][j] < minweight[j] ) {  
                minweight[j] = weights[k][j];    //将小于当前权值的边(k,j)权值加入数组中
                edges[j] =k;   //将边(j,k)信息存入边数组中
            }
    }
}
int cmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}

int main(){
    int n,e,id,vi,vj,w;
    scanf("%d%d",&n,&e);
    while(e--){
        scanf("%d%d%d%d",&id,&vi,&vj,&w);
        name[vi][vj]=name[vj][vi]=id;
        weights[vi][vj]=weights[vj][vi]=w;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        if(i!=j&&weights[i][j]==0){
            weights[i][j]=INFINITY;
            weights[j][i]=INFINITY;
        }
    }
    Prim(weights,n,0,edges);
    int order[MAXVER];
    for(int i=1;i<n;i++){
        cnt+=weights[i][edges[i]];
        order[p++]=name[i][edges[i]];
    }
    printf("%d\n",cnt);
    qsort(order,n-1,sizeof(int),cmp);
    for(int i=0;i<n-1;i++)
    printf("%d ",order[i]);
    return 0;
}
