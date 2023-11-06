#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>
clock_t start,end;
#define MAX_WORD_LEN 200      // 最长单词长度为200

int ptr=0;//字典树数量
int weight[20000];//article中每篇权重向量
char fingerprint[20000][400];//article中每篇指纹
char hash[20000][400];//hash表
char samname[30];
int name[10000][10000];
typedef struct nam{
    int a,b;
}nam;
nam arti[1000000];

int stop_tree[1000000][26];//stopwprds字典树
int pt=0;
int stop_exist[1000000];//是否存在
void stop_insert(char*s){//停用词插入
    int i=0,p=0;
    while(s[i]){
        int c=s[i]-'a';
        if(stop_tree[p][c]==0)
        stop_tree[p][c]=++pt;
        p=stop_tree[p][c];
        i++;
    }
    stop_exist[p]=1;
}
int stop_find(char*s){//停用词查找
    int i=0,p=0;
    while(s[i]){
        int c=s[i]-'a';
        if(stop_tree[p][c]==0)
        return 0;
        p=stop_tree[p][c];
        i++;
    }
    return stop_exist[p];
}

int tal_tree[1000000][26];//article字典树
int ptal=0;
int tal_exist[1000000];//是否存在
typedef struct tnode{
    char word[100];
    int count;
}tnode;
tnode tal_w[1000000];
void tal_insert(char*s){//article插入
    int i=0,p=0;
    while(s[i]){
        int c=s[i]-'a';
        if(tal_tree[p][c]==0)
        tal_tree[p][c]=++ptal;
        p=tal_tree[p][c];
        i++;
    }
    if(tal_exist[p]){
        tal_w[p].count++;
    }
    else{
        tal_exist[p]=1;
        tal_w[p].count=1;
        strcpy(tal_w[p].word,s);
    }
}
int tal_find(char*s){//article查找
    int i=0,p=0;
    while(s[i]){
        int c=s[i]-'a';
        if(tal_tree[p][c]==0)
        return 0;
        p=tal_tree[p][c];
        i++;
    }
    return p;
}

int key_tree[1000000][26];//key字典树
int pk=0;
int key_exist[1000000];//是否存在
void key_insert(char*s,int order){//关键词插入
    int i=0,p=0;
    while(s[i]){
        int c=s[i]-'a';
        if(key_tree[p][c]==0)
        key_tree[p][c]=++pk;
        p=key_tree[p][c];
        i++;
    }
    key_exist[p]=order;
}
int key_find(char*s){//关键词查找
    int i=0,p=0;
    while(s[i]){
        int c=s[i]-'a';
        if(key_tree[p][c]==0)
        return 0;
        p=key_tree[p][c];
        i++;
    }
    return key_exist[p];
}
// 堆节点结构体
typedef struct HeapNode {
    char word[MAX_WORD_LEN];
    int count;
} HeapNode;

// 堆结构体
typedef struct Heap {
    int size;
    HeapNode **array;
} Heap;

// 创建一个新的堆
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->size = 0;
    heap->array = (HeapNode**) malloc(capacity * sizeof(HeapNode*));
    return heap;
}

//qsort比较函数,先比频率，再按字典序
int cmp(const void* a,const void* b){
    HeapNode x=*(HeapNode*)a,y=*(HeapNode*)b;
    if(x.count<y.count) return 1;
    else if(x.count>y.count) return -1;
    else{
        if(strcmp(x.word,y.word)<0) return -1;
        else return 1;
    }
}

//比较函数
int cmp1(HeapNode* a,HeapNode* b){//a<b return 1,a>b return -1
    HeapNode x=*a,y=*b;
    if(x.count<y.count) return 1;
    else if(x.count>y.count) return -1;
    else{
        if(strcmp(x.word,y.word)<0) return -1;
        else return 1;
    }
}

//交换函数
void swap(HeapNode** a,HeapNode** b){
    HeapNode* t=*a;
    *a=*b;
    *b=t;
}

//向堆中插入新的节点
void insertToHeap(Heap* heap,int s,HeapNode new){
    if(s>heap->size){//如果堆没有满
        heap->array[heap->size]=(HeapNode*)malloc(sizeof(HeapNode));
        heap->array[heap->size]->count=new.count;
        strcpy(heap->array[heap->size]->word,new.word);
        heap->size++;
        int i=heap->size-1;
        while(i&&cmp1(heap->array[i],heap->array[(i-1)/2])>0){//小顶堆，上浮
            swap(&heap->array[i],&heap->array[(i-1)/2]);
            i=(i-1)/2;
        }
        return ;
    }
    else{//堆满
        if(cmp1(&new,heap->array[0])<0){//如果比堆顶元素大，需要下沉，否则不变
            heap->array[0]->count=new.count;//将new放到堆顶
            strcpy(heap->array[0]->word,new.word);
            int i=0;
            while(i<heap->size){//下沉
                if((i*2+1)>=heap->size){//没有儿子
                    return;
                }
                else if((i*2+1)==(heap->size-1)){//只有左儿子
                    if(cmp1(heap->array[i],heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                    }
                    return;
                }
                else if(cmp1(heap->array[i*2+1],heap->array[i*2+2])>0){//和左儿子比较
                    if(cmp1(heap->array[i],heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                        i=i*2+1;
                    }
                    else return;
                }
                else{//和右儿子比较
                    if(cmp1(heap->array[i],heap->array[i*2+2])<0){
                        swap(&heap->array[i],&heap->array[i*2+2]);
                        i=i*2+2;
                    }
                    else return;
                }
            }
        }
        return;
    }
}

//字典树遍历并将元素加入堆中
void traverseTrieNode(int root,Heap* heap,int s){
    if(tal_exist[root]){
        HeapNode t;
        t.count=tal_w[root].count;
        strcpy(t.word,tal_w[root].word);
        insertToHeap(heap,s,t);
    }
    for(int i=0;i<26;i++){
        if(tal_tree[root][i]==0)
        continue;
        traverseTrieNode(tal_tree[root][i],heap,s);
    }
}

//堆排序
void Heapsort(Heap* heap){
    int s=heap->size-1;
    while(s>0){
        swap(&heap->array[0],&heap->array[s]);//先将堆顶最小的元素与堆末尾元素互换
        s--;
        int i=0;
        while(i<s){//下沉
                if((i*2+1)>s){//没有儿子
                    break;
                }
                else if((i*2+1)==s){//只有左儿子
                    if(cmp1(heap->array[i],heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                    }
                    break;
                }
                else if(cmp1(heap->array[i*2+1],heap->array[i*2+2])>0){//和左儿子比较
                    if(cmp1(heap->array[i],heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                        i=i*2+1;
                    }
                    else break;
                }
                else{//和右儿子比较
                    if(cmp1(heap->array[i],heap->array[i*2+2])<0){
                        swap(&heap->array[i],&heap->array[i*2+2]);
                        i=i*2+2;
                    }
                    else break;
                }
            }
    }
}

void insert(char*s,int*exist){
    int i=0,p=0;
    while(s[i]){
        int c=s[i]-'a';
        p=tal_tree[p][c];
        i++;
    }
    exist[p]++;
}

//汉明距离
int hanmingdis(char* p1,char *p2,int m){
    int ans=0;
    for(int i=0;i<m;i++){
        if(p1[i]!=p2[i])
        ans++;
    }
    return ans;
}


int main(int argc,char **argv){
    // 命令行输入
    // int M=0,N=0;
    // int len1=strlen(argv[1]);
    // for(int i=0;i<len1;i++){
    //     N=N*10+argv[1][i]-'0';
    // }
    // int len2=strlen(argv[2]);
    // for(int i=0;i<len2;i++){
    //     M=M*10+argv[2][i]-'0';
    // }
    int n,m;
    scanf("%d%d",&n,&m);//终端输入//特征向量长度n，指纹长度m
    start=clock();
    // n=N;//命令行输入
    // m=M;
    FILE* result_file;//输出文件
    if((result_file=fopen("result.txt","w"))==NULL){//打开stopwords文件
        printf("%s open failed!\n","result_file");
        return -1;
    }
    //读入停用词
    FILE* stopwords_file;
    if((stopwords_file=fopen("stopwords.txt","r"))==NULL){//打开stopwords文件
        printf("%s open failed!\n","stopwords.txt");
        return -1;
    }
    char word[100];
    while(fscanf(stopwords_file,"%s",word)!=EOF){//将每一个stopword插入
        stop_insert(word);
    }

    //读入hash表
    FILE* hash_file;
    if((hash_file=fopen("hashvalue.txt","r"))==NULL){
        printf("%s open failed!\n","hashvalue.txt");
        return -1;
    }
    for(int i=0;i<n;i++)
    fscanf(hash_file,"%s",hash[i]);
    
    //读入已有文件并计算网页指纹
    char c;
    FILE* article_file;
    if((article_file=fopen("article.txt","r"))==NULL){
        printf("%s open failed!\n","article.txt");
        return -1;
    }
    int a,b;
    fscanf(article_file,"%d-%d",&a,&b);
    name[a][b]=ptr;
    arti[ptr].a=a;
    arti[ptr].b=b;
    char s[200];
    while((c=fgetc(article_file))!=EOF){
        while(c!='\f'){//一篇文章结束进行一次计算
            if(isalpha(c)){
                if(isupper(c))
                c^=32;
                int p=1;
                s[0]=c;
                while((c=fgetc(article_file))!=EOF){//将一个单词读入s中
                    if(isupper(c))
                    c^=32;
                    else if(!isalpha(c))
                    break;
                    s[p++]=c;
                }
                s[p]='\0';//让s结尾
                if(stop_find(s)==0){//stopwords中没有这个单词
                    tal_insert(s);
                }
            }
            if((c=fgetc(article_file))==EOF)
            break;//读入下一个字符
        }
        ptr++;//新一篇
        fscanf(article_file,"%d-%d",&a,&b);
        name[a][b]=ptr;
        arti[ptr].a=a;
        arti[ptr].b=b;
    }
    end=clock();
    printf("%lf\n",((double)(end-start))/CLK_TCK);
    Heap* heap=createHeap(n*2);//创建堆排序所用堆
    traverseTrieNode(0,heap,n+1);//导入元素，保留最大的n个
    // qsort(heap->array,n,sizeof(heap->array[0]),cmp);//对前n个单词快速排序
    Heapsort(heap);//对前n个单词堆排序
    // for(int i=0;i<n;i++)
    // fprintf(result_file,"%s:%d\n",heap->array[i]->word,heap->array[i]->count);
    for(int i=0;i<n;i++){//把关键词插入关键词树
        key_insert(heap->array[i]->word,i+1);
    }
    end=clock();
    printf("%lf\n",((double)(end-start))/CLK_TCK);

    rewind(article_file);//再读一遍
    int ct=0;//文章计数器
    while((c=fgetc(article_file))!=EOF){
        int artweight[100000]={0};
        while(c!='\f'){//一篇文章结束进行一次计算
            if(isalpha(c)){
                if(isupper(c))
                c^=32;
                int p=1;
                s[0]=c;
                while((c=fgetc(article_file))!=EOF){//将一个单词读入s中
                    if(isupper(c))
                    c^=32;
                    else if(!isalpha(c))
                    break;
                    s[p++]=c;
                }
                s[p]='\0';//让s结尾
                int r=key_find(s);//是关键词
                if(r){
                    artweight[r-1]++;
                }
            }
            if((c=fgetc(article_file))==EOF)
            break;//读入下一个字符
        }
        int sign[1000]={0};
        for(int j=0;j<m;j++){//计算sign
            for(int k=0;k<n;k++){
                sign[j]+=artweight[k]*(hash[k][j]*2-97);
            }
        }
        for(int j=0;j<m;j++){
            fingerprint[ct][j]=48+(sign[j]>0);
        }
        ct++;
    }
    end=clock();
    printf("%lf\n",((double)(end-start))/CLK_TCK);
    //对sample文件进行操作
    FILE* sample_file;
    if((sample_file=fopen("sample.txt","r"))==NULL){
        printf("%s open failed!\n","hashvalue.txt");
        return -1;
    }
    int cnt=1,sa,sb;//记数
    fscanf(sample_file,"%s",samname);
    fscanf(sample_file,"%d-%d",&sa,&sb);
    while((c=fgetc(sample_file))!=EOF){
        while(c!='\f'){//一篇文章结束进行一次计算
            if((c=fgetc(sample_file))==EOF)
            break;
            }

        int d[4][100000],f[4]={0},h;//储存符合要求文章
        for(int i=0;i<ptr;i++){
            h=hanmingdis(fingerprint[i],fingerprint[name[sa][sb]],m);
            if(h<4){
                d[h][f[h]]=i;
                f[h]++;
            }
        }
        fprintf(result_file,"%s\n",samname);
        for(int i=0;i<4;i++){
            if(f[i]==0) continue;
            fprintf(result_file,"%d:",i);
            for(int j=0;j<f[i];j++){
                fprintf(result_file,"%d-%d ",arti[d[i][j]].a,arti[d[i][j]].b);
            }
            fprintf(result_file,"\n");
        }
        cnt++;//新一篇
        fscanf(sample_file,"%s",samname);
        fscanf(sample_file,"%d-%d",&sa,&sb);
    }
    end=clock();
    printf("%lf\n",((double)(end-start))/CLK_TCK);
    return 0;
}
