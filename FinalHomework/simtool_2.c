#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

//stop words相关函数
#define MAX_CHILD 26            // 一个结点最多有26个孩子，对应英文字母
#define MAX_WORD_LEN 200      // 最长单词长度为200

// 定义字典树的结构体
typedef struct TrieNode {
    struct TrieNode* child[MAX_CHILD];  // 孩子节点
    int is_word_end;                    // 标记是否为一个单词结尾
} TrieNode;

// 创建一个新节点
TrieNode* create_node() {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    if (node != NULL) {
        node->is_word_end = 0;  // 初始化为非单词结尾
        for (int i = 0; i < MAX_CHILD; i++) {
            node->child[i] = NULL;
        }
    }
    return node;
}

// 向字典树插入一个单词
void insert(TrieNode** root, char* word) {
    int i = 0, index = 0;
    TrieNode* cur = *root;
    while (word[i]) {  // 对单词中的每个字符做处理
        index = word[i] - 'a';
        if (cur->child[index] == NULL) {  // 如果该字符对应的孩子节点不存在，则新建此节点
            cur->child[index] = create_node();
        }
        cur = cur->child[index];  // 移动指针
        i++;
    }
    cur->is_word_end = 1;  // 标记为单词结尾
}

// 在字典树中查找一个单词
int search(TrieNode* root, char word[]) {
    int i = 0, index = 0;
    TrieNode* cur = root;
    while (word[i]) {  // 对单词中的每个字符做处理
        index = word[i] - 'a';
        if (cur->child[index] == NULL) {  // 如果该字符对应的孩子节点不存在，则单词不存在
            return 0;
        }
        cur = cur->child[index];  // 移动指针
        i++;
    }
    return (cur != NULL && cur->is_word_end);  // 如果该单词结尾节点存在，则单词存在
}

//统计词频所需字典树以及堆排序函数
#define MAX_WORDS 10000000 // 最大单词数量

//字典树结构体
typedef struct wTrieNode {
    int count; // 记录单词出现次数
    char w[200];
    struct wTrieNode *child[26]; // 指向子节点的指针数组（a-z）
} wTrieNode;

// 创建一个新的字典树节点
wTrieNode* createTrieNode() {
    wTrieNode* node = (wTrieNode*) malloc(sizeof(wTrieNode));
    node->count = 0;
    for(int i = 0; i < 26; i++) {
        node->child[i] = NULL;
    }
    node->w[0]='\0';
    return node;
}

// 将单词插入到字典树中
void winsert(wTrieNode** root, char* word) {
    int i = 0, index = 0;
    wTrieNode* cur = *root;
    while (word[i]) {  // 对单词中的每个字符做处理
        index = word[i] - 'a';
        if (cur->child[index] == NULL) {  // 如果该字符对应的孩子节点不存在，则新建此节点
            cur->child[index] = createTrieNode();
            strcpy(cur->child[index]->w,cur->w);
            cur->child[index]->w[i]=index+'a';
            cur->child[index]->w[i+1]='\0';
        }
        cur = cur->child[index];  // 移动指针
        i++;
    }
    cur->count++; // 记录单词出现次数
}

//在字典树中查找单词次数
int wsearch(wTrieNode** root, char* word){
    int i = 0, index = 0;
    wTrieNode* cur = *root;
    while (word[i]) {  // 对单词中的每个字符做处理
        index = word[i] - 'a';
        if (cur->child[index] == NULL) {
            return 0;
        }
        cur = cur->child[index];  // 移动指针
        i++;
    }
    return cur->count;
}

// 堆节点结构体
typedef struct HeapNode {
    char word[MAX_WORD_LEN];
    int count;
} HeapNode;

// 堆结构体
typedef struct Heap {
    int size;
    HeapNode *array;
} Heap;

// 创建一个新的堆
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->size = 0;
    heap->array = (HeapNode*) malloc(capacity * sizeof(HeapNode));
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
void swap(HeapNode* a,HeapNode* b){
    HeapNode t;
    t.count=a->count;
    strcpy(t.word,a->word);
    a->count=b->count;
    strcpy(a->word,b->word);
    b->count=t.count;
    strcpy(b->word,t.word);
}

//向堆中插入新的节点
void insertToHeap(Heap* heap,int s,HeapNode new){
    if(s>heap->size){//如果堆没有满
        heap->array[heap->size].count=new.count;
        strcpy(heap->array[heap->size].word,new.word);
        heap->size++;
        int i=heap->size-1;
        while(i&&cmp1(&heap->array[i],&heap->array[(i-1)/2])>0){//小顶堆，上浮
            swap(&heap->array[i],&heap->array[(i-1)/2]);
            i=(i-1)/2;
        }
        return ;
    }
    else{//堆满
        if(cmp1(&new,&heap->array[0])<0){//如果比堆顶元素大，需要下沉，否则不变
            heap->array[0].count=new.count;//将new放到堆顶
            strcpy(heap->array[0].word,new.word);
            int i=0;
            while(i<heap->size){//下沉
                if((i*2+1)>=heap->size){//没有儿子
                    return;
                }
                else if((i*2+1)==(heap->size-1)){//只有左儿子
                    if(cmp1(&heap->array[i],&heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                    }
                    return;
                }
                else if(cmp1(&heap->array[i*2+1],&heap->array[i*2+2])>0){//和左儿子比较
                    if(cmp1(&heap->array[i],&heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                        i=i*2+1;
                    }
                    else return;
                }
                else{//和右儿子比较
                    if(cmp1(&heap->array[i],&heap->array[i*2+2])<0){
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
void traverseTrieNode(struct wTrieNode* node,Heap* heap,int s){
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (node->child[i] != NULL) {
            traverseTrieNode(node->child[i],heap,s);
        }
    }
    if(node->count>0){
        HeapNode t;
        t.count=node->count;
        strcpy(t.word,node->w);
        insertToHeap(heap,s,t);
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
                    if(cmp1(&heap->array[i],&heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                    }
                    break;
                }
                else if(cmp1(&heap->array[i*2+1],&heap->array[i*2+2])>0){//和左儿子比较
                    if(cmp1(&heap->array[i],&heap->array[i*2+1])<0){
                        swap(&heap->array[i],&heap->array[i*2+1]);
                        i=i*2+1;
                    }
                    else break;
                }
                else{//和右儿子比较
                    if(cmp1(&heap->array[i],&heap->array[i*2+2])<0){
                        swap(&heap->array[i],&heap->array[i*2+2]);
                        i=i*2+2;
                    }
                    else break;
                }
            }
    }
}

//汉明距离
int hanmingdis(char* p1,char *p2,int m){
    int ans=0;
    for(int i=0;i<m;i++){
        ans+=(!(p1[i]==p2[i]));
    }
    return ans;
}

wTrieNode* root;//总字典树
wTrieNode* dic[200000];//article每篇字典树
char name[200000][30];//每篇名字
int ptr=0;//字典树数量
int weight[200000];//article中每篇权重向量
char fingerprint[200000][5000];//article中每篇指纹
char hash[200000][5000];//hash表


int main(int argc,char **argv){
    //命令行输入
    int M=0,N=0;
    int len1=strlen(argv[1]);
    for(int i=0;i<len1;i++){
        N=N*10+argv[1][i]-'0';
    }
    int len2=strlen(argv[2]);
    for(int i=0;i<len2;i++){
        M=M*10+argv[2][i]-'0';
    }
    FILE* result_file;//输出文件
    if((result_file=fopen("result.txt","w"))==NULL){//打开stopwords文件
        printf("%s open failed!\n","result_file");
        return -1;
    }
    //读入停用词
    TrieNode* stop_words=create_node();//创建一个空字典树，储存停用词
    FILE* stopwords_file;
    if((stopwords_file=fopen("stopwords.txt","r"))==NULL){//打开stopwords文件
        printf("%s open failed!\n","stopwords.txt");
        return -1;
    }
    char word[100];
    while(fscanf(stopwords_file,"%s",word)!=EOF){//将每一个stopword插入
        insert(&stop_words,word);
    }

    //读入hash表
    FILE* hash_file;
    if((hash_file=fopen("hashvalue.txt","r"))==NULL){
        printf("%s open failed!\n","hashvalue.txt");
        return -1;
    }
    int n,m;
    // scanf("%d%d",&n,&m);//终端输入//特征向量长度n，指纹长度m
    n=N;//命令行输入
    m=M;
    for(int i=0;i<n;i++)
    fscanf(hash_file,"%s",hash[i]);

    //读入已有文件并计算网页指纹
    char c;
    FILE* article_file;
    if((article_file=fopen("article.txt","r"))==NULL){
        printf("%s open failed!\n","article.txt");
        return -1;
    }
    root=createTrieNode();//创建总字典树
    fscanf(article_file,"%s",name[0]);
    while((c=fgetc(article_file))!=EOF){
        dic[ptr]=createTrieNode();
        while(c!='\f'){//一篇文章结束进行一次计算
            if(isalpha(c)){
                if(isupper(c))
                c^=32;
                char s[200];
                int p=1;
                s[0]=c;
                while((c=fgetc(article_file))!=EOF){//将一个单词读入s中
                    if(!isalpha(c))
                    break;
                    if(isupper(c))
                    c^=32;
                    s[p++]=c;
                }
                s[p]='\0';//让s结尾
                if(search(stop_words,s)==0){//stopwords中没有这个单词
                    winsert(&root,s);
                    winsert(&dic[ptr],s);
                }
            }
            if((c=fgetc(article_file))==EOF)
            break;//读入下一个字符
        }
        ptr++;//新一篇
        fscanf(article_file,"%s",name[ptr]);
    }
    Heap* heap=createHeap(n*3);//创建堆排序所用堆
    traverseTrieNode(root,heap,n+1);//导入元素，保留最大的n个
    // qsort(heap->array,n,sizeof(heap->array[0]),cmp);//对前n个单词快速排序
    Heapsort(heap);//对前n个单词堆排序
    // for(int i=0;i<n;i++)
    // printf("%s:%d\n",heap->array[i].word,heap->array[i].count);

    for(int i=0;i<ptr;i++){//对每篇处理,计算指纹
        for(int j=0;j<n;j++){
            weight[j]=wsearch(&dic[i],heap->array[j].word);
            // printf("%d ",weight[j]);
        }
        int sign[5000]={0};
        for(int j=0;j<m;j++){//计算sign
            for(int k=0;k<n;k++){
                if(hash[k][j]=='1')
                sign[j]+=weight[k];
                else
                sign[j]-=weight[k];
            }
        }
        for(int j=0;j<m;j++){
            if(sign[j]>0)
            fingerprint[i][j]='1';
            else
            fingerprint[i][j]='0';
        }
    }
    // for(int i=0;i<ptr;i++){
    //     for(int j=0;j<m;j++){
    //         printf("%d ",fingerprint[i][j]);
    //     }
    //     printf("  %d\n",i+1);
    // }

    //对sample文件进行操作
    FILE* sample_file;
    if((sample_file=fopen("sample.txt","r"))==NULL){
        printf("%s open failed!\n","hashvalue.txt");
        return -1;
    }
    int cnt=1;//记数
    while((c=fgetc(sample_file))!=EOF){
        wTrieNode* sam=createTrieNode();
        while(c!='\f'){//一篇文章结束进行一次计算
            if(isalpha(c)){
                if(isupper(c))
                c^=32;
                char s[200];
                int p=1;
                s[0]=c;
                while((c=fgetc(sample_file))!=EOF){//将一个单词读入s中
                    if(!isalpha(c))
                    break;
                    if(isupper(c))
                    c^=32;
                    s[p++]=c;
                }
                s[p]='\0';//让s结尾
                if(search(stop_words,s)==0){//stopwords中没有这个单词
                    winsert(&sam,s);
                }
            }
            c=fgetc(sample_file);//读入下一个字符
        }
        int samWeight[100000];//权重向量
        for(int i=0;i<n;i++){
            samWeight[i]=wsearch(&sam,heap->array[i].word);
            // printf("%s:%d\n",heap->array[i].word,samWeight[i]);
        }
        int sign[5000]={0};
        for(int j=0;j<m;j++){//计算sign
            for(int k=0;k<n;k++){
                if(hash[k][j]=='1')
                sign[j]+=samWeight[k];
                else
                sign[j]-=samWeight[k];
            }
        }
        char print[5000];
        for(int j=0;j<m;j++){
            if(sign[j]>0)
            print[j]='1';
            else
            print[j]='0';
        }
        int d[4][100000];//储存符合要求文章
        int f[4]={0};//记录数量
        for(int i=0;i<ptr;i++){
            int h=hanmingdis(fingerprint[i],print,m);
            if(h<4){
                d[h][f[h]]=i;
                f[h]++;
            }
        }
        fprintf(result_file,"Sample-%d\n",cnt);
        for(int i=0;i<4;i++){
            if(f[i]==0) continue;
            fprintf(result_file,"%d:",i);
            for(int j=0;j<f[i];j++){
                fprintf(result_file,"%s ",name[d[i][j]]);
                // fprintf(result_file,"1-%d ",d[i][j]+1);
            }
            fprintf(result_file,"\n");
        }
        cnt++;//新一篇
    }
    return 0;
}


