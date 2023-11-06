#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct  edge{ 
       int  adjvex;
       struct edge *next;
}Elink;
typedef struct ver{
       int  vertex;
       Elink *link;
}Vlink;
Vlink graph[150];
void insert(int m,int n){
    if(graph[m].vertex==0){
            graph[m].link=(Elink*)malloc(sizeof(Elink));
            graph[m].link->next=NULL;
            graph[m].link->adjvex=n;
            graph[m].vertex++;
        }
        else{
            graph[m].vertex++;
            Elink* i,*j=graph[m].link;
            for(i=graph[m].link;i!=NULL;j=i,i=i->next){
                if(i->adjvex>n)
                break;
            }
            if(i==graph[m].link){
                Elink* t=(Elink*)malloc(sizeof(Elink));
                t->next=i;
                t->adjvex=n;
                graph[m].link=t;
            }
            else if(i!=NULL){
                Elink* t=(Elink*)malloc(sizeof(Elink));
                t->next=i;
                t->adjvex=n;
                j->next=t;
            }
            else{
                Elink* t=(Elink*)malloc(sizeof(Elink));
                t->next=NULL;
                t->adjvex=n;
                j->next=t;
            }
        }
}
void DFS(Vlink *G, int v,int *Visited)
{
    Elink  *p;
    Visited[v] = 1; //标识某顶点被访问过
    printf("%d ",v);
    for(p = G[v].link; p !=NULL;  p=p->next)
         if( !Visited[p->adjvex] )
             DFS(G, p->adjvex,Visited);
}
int q[1000];
int f=0,b=0;
void BFS(Vlink *G, int v,int* Visited)
{
    Elink  *p;
    Visited[v] = 1; //标识某顶点已入队
    q[b++]=v;
    while(f!=b){
         v = q[f++];  //取出队头元素
         printf("%d ",v); //访问当前顶点
         for(p=G[v].link; p!=NULL; p=p->next ) //访问该顶点的每个邻接顶点
             if( !Visited[p->adjvex] ) {
                    Visited[p->adjvex] = 1; //标识某顶点入队
                    q[b++]=p->adjvex;
           }
     }
}

int main(){
    int m,n,N,T;
    scanf("%d%d",&N,&T);
    for(int i=0;i<=100;i++){
        graph[i].vertex=0;
    }
    while(T--){
        scanf("%d%d",&m,&n);
        insert(m,n);
        insert(n,m);
    }
    scanf("%d",&m);
    int visited[150]={0};
    DFS(graph,0,visited);
    printf("\n");
    int v1[150]={0};
    BFS(graph,0,v1);
    printf("\n");
    int v2[150]={0};
    v2[m]=1;
    DFS(graph,0,v2);
    printf("\n");
    int v3[150]={0};
    v3[m]=1;
    f=b=0;
    BFS(graph,0,v3);
    return 0;
}