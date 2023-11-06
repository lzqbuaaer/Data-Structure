#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXNUM 512	 //地铁最大站数
#define MAXLEN 100	//地铁站名的最大长度
#define INFINITY 32767
typedef struct station{ //车站信息
    char sname[MAXLEN];  	//车站名
    int ischange; 		 //是否为换乘站，0-否，1-换乘
}station;
typedef struct weight{
    int wei; 		//两个站间的权重，即相差站数，缺省为1
    int lno;  		//两个顶点所在的线号
}weight;
station BGvertex[MAXNUM];  		//地铁网络图顶点数组
weight BGweights[MAXNUM][MAXNUM]; 	//网络图权重数组，邻接矩阵
int Vnum = 0; 	//实际地铁总站数
int search(char *s){
    for(int i=0;i<Vnum;i++){
        if(strcmp(s,BGvertex[i].sname)==0)
        return i;
    }
    return -1;
}
int addVertex(station st){
    int a=search(st.sname);
    if(a>=0) return a;
    else{
        BGvertex[Vnum].ischange=st.ischange;
        strcpy(BGvertex[Vnum].sname,st.sname);
        Vnum++;
        return Vnum-1;
    }
}
int Spath[MAXNUM];
int Sweight[MAXNUM],wfound[MAXNUM];
void Dijkstra(int v0){
    int i,j,v,minweight;
    for(i=0;i<Vnum;i++){
        Sweight[i]=BGweights[v0][i].wei; 
        Spath[i]=v0;
    }  //初始化数组Sweight和Spath
    Sweight[v0]=0;  
    wfound[v0]=1;  
     for(i=0;i<Vnum-1;i++) {  //迭代VNUM-1次
        minweight=INFINITY;
        for(j=0;j<Vnum;j++)   //找到未标记的最小权重值顶点 
            if(!wfound[j]&&(Sweight[j]<minweight)){
                v=j; 
                minweight=Sweight[v];
            }
        wfound[v]=1;	//标记该顶点为已找到最短路径
        for(j=0;j<Vnum;j++) //找到未标记顶点且其权值大于v的权值+(v,j)的权值，更新其权值
            if(!wfound[j]&&(minweight+BGweights[v][j].wei<Sweight[j])){
                Sweight[j]=minweight+BGweights[v][j].wei;
                Spath[j]=v;  //记录前驱顶点
            }
    } 
}
int main(){
    FILE *fp=fopen("bgstations.txt","r");
    int snum,lno,lnum,v1,v2;
    station st;
    fscanf(fp,"%d",&snum);
    for(int i=0;i<snum;i++){
        fscanf(fp,"%d%d",&lno,&lnum);
        v1=v2=-1;
        for(int j=0;j<lnum;j++){
            fscanf(fp,"%s%d",st.sname,&st.ischange);
            v2=addVertex(st);
            if(v1!=-1){
                BGweights[v1][v2].wei=BGweights[v2][v1].wei=1;
                BGweights[v1][v2].lno=BGweights[v2][v1].lno=lno;
            }
            v1=v2;
        }
    }
    for(int i=0;i<Vnum;i++){
        for(int j=0;j<Vnum;j++){
            if(i!=j&&BGweights[i][j].wei==0)
            BGweights[i][j].wei=INFINITY;
        }
    }
    char s[100],d[100];
    scanf("%s%s",s,d);
    int v0=search(s);
    Dijkstra(v0);
    int end=search(d);
    int ans[512];
    int p=0,i=0;
    ans[p++]=end;
    int pend=end;
    end=Spath[end];
    while(end!=v0){
        i++;
        if(BGvertex[end].ischange&&BGweights[pend][end].lno!=BGweights[Spath[end]][end].lno){
            BGweights[ans[p-1]][end].wei=BGweights[end][ans[p-1]].wei=i;
            BGweights[ans[p-1]][end].lno=BGweights[end][ans[p-1]].lno=BGweights[ans[p-1]][Spath[ans[p-1]]].lno;
            i=0;
            ans[p++]=end;
        }
        pend=end;
        end=Spath[end];
    }
    ans[p]=v0;
    BGweights[ans[p]][ans[p-1]].wei=BGweights[ans[p-1]][ans[p-1]].wei=i+1;
    BGweights[ans[p]][ans[p-1]].lno=BGweights[ans[p-1]][ans[p-1]].lno=BGweights[ans[p-1]][Spath[ans[p-1]]].lno;
    for(int i=p;i>0;i--){
        printf("%s-%d(%d)-",BGvertex[ans[i]].sname,BGweights[ans[i]][ans[i-1]].lno,BGweights[ans[i]][ans[i-1]].wei);
    }
    printf("%s",BGvertex[ans[0]].sname);
    return 0;
}