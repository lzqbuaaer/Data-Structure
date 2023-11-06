#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
typedef struct  edge{ 
       int  adjvex;
       int weight;
       struct edge *next;
}Elink;
typedef struct ver{
    int  vertex;
    Elink *link;
}Vlink;
Vlink graph[200];
void insert(int w,int m,int n){
    if(graph[m].vertex==0){
            graph[m].link=(Elink*)malloc(sizeof(Elink));
            graph[m].link->next=NULL;
            graph[m].link->adjvex=n;
            graph[m].link->weight=w;
            graph[m].vertex++;
        }
        else{
            graph[m].vertex++;
            Elink* i,*j=graph[m].link;
            for(i=graph[m].link;i!=NULL;j=i,i=i->next){
                if(i->weight>w)
                break;
            }
            if(i==graph[m].link){
                Elink* t=(Elink*)malloc(sizeof(Elink));
                t->next=i;
                t->adjvex=n;
                t->weight=w;
                graph[m].link=t;
            }
            else if(i!=NULL){
                Elink* t=(Elink*)malloc(sizeof(Elink));
                t->next=i;
                t->adjvex=n;
                t->weight=w;
                j->next=t;
            }
            else{
                Elink* t=(Elink*)malloc(sizeof(Elink));
                t->next=NULL;
                t->adjvex=n;
                t->weight=w;
                j->next=t;
            }
        }
}
int n,e,w,i,j;
int q[1000];
int f=0,b=0;
void DFS(Vlink *G, int v,int *Visited)
{
    Elink  *p;
    Visited[v] = 1; //标识某顶点被访问过
    
    for(p = G[v].link; p !=NULL;  p=p->next){
        if( !Visited[p->adjvex] ){
            q[b++]=p->weight;
            if(p->adjvex==n-1){
                for(int i=f;i<b;i++){
                    printf("%d ",q[i]);
                }
                printf("\n");
                b--;
            }
            else 
            DFS(G, p->adjvex,Visited);
        }    
    }
    Visited[v]=0;      
    b--;
}
int main(){
    scanf("%d%d",&n,&e);
    for(int i=0;i<=100;i++){
        graph[i].vertex=0;
    }
    while(e--){
        scanf("%d%d%d",&w,&i,&j);
        insert(w,i,j);
        insert(w,j,i);
    }
    int visit[200]={0};
    DFS(graph,0,visit);
    return 0;
}