#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 50 // 最大单词长度
#define MAX_WORDS 10000 // 最大单词数量
#define MAX_N 10 // 最大输出频率最高的单词数量

// 字典树节点结构体
typedef struct TrieNode {
    int count; // 记录单词出现次数
    struct TrieNode *child[26]; // 指向子节点的指针数组（a-z）
} TrieNode;

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

// 创建一个新的字典树节点
TrieNode* createTrieNode() {
    TrieNode* node = (TrieNode*) malloc(sizeof(TrieNode));
    node->count = 0;
    for(int i = 0; i < 26; i++) {
        node->child[i] = NULL;
    }
    return node;
}

// 将单词插入到字典树中
void insert(TrieNode* root, char* word) {
    TrieNode* node = root;
    int len = strlen(word);
    for(int i = 0; i < len; i++) {
        int index = word[i] - 'a'; // 计算对应字母的下标
        if(node->child[index] == NULL) {
            node->child[index] = createTrieNode(); // 如果这个节点还没有被创建，就创建它
        }
        node = node->child[index]; // 更新节点
    }
    node->count++; // 记录单词出现次数
}

// 堆排序中的堆调整函数
void heapify(Heap* heap, int i) {
    int smallest = i; // 初始化父节点为堆中最小值
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < heap->size && heap->array[left].count < heap->array[smallest].count) {
        smallest = left; // 如果左子节点比父节点小，就让左子节点成为最小值
    }
    if(right < heap->size && heap->array[right].count < heap->array[smallest].count) {
        smallest = right; // 如果右子节点比父节点小，就让右子节点成为最小值
    }
    if(smallest != i) { // 如果最小值不是父节点，就交换二者位置，并递归执行堆调整
        HeapNode temp = heap->array[i];
        heap->array[i] = heap->array[smallest];
        heap->array[smallest] = temp;
        heapify(heap, smallest);
    }
}

// 创建一个新的堆
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->size = 0;
    heap->array = (HeapNode*) malloc(capacity * sizeof(HeapNode));
    return heap;
}

// 向堆中插入新的节点
void insertToHeap(Heap* heap, char* word, int count) {
    HeapNode node;
    strcpy(node.word, word);
    node.count = count;
    heap->array[heap->size] = node;
    heap->size++;
    int i = heap->size - 1;
    while(i && heap->array[(i-1)/2].count > heap->array[i].count) { // 如果新插入的节点比父节点小，就交换二者位置，直到满足堆的性质
        HeapNode temp = heap->array[i];
        heap->array[i] = heap->array[(i-1)/2];
        heap->array[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

// 执行堆排序
void heapSort(Heap* heap, int n) {
    for(int i = (n-1)/2; i >= 0; i--) { // 从最后一个非叶节点开始执行堆调整
        heapify(heap, i);
    }
    for(int i = n-1; i > 0; i--) { // 不断地将堆顶元素和数组末尾元素交换，然后执行堆调整
        HeapNode temp = heap->array[0];
        heap->array[0] = heap->array[i];
        heap->array[i] = temp;
        heap->size--;
        heapify(heap, 0);
    }
}

int main() {
    TrieNode* root = createTrieNode(); // 创建字典树根节点
    char words[MAX_WORDS][MAX_WORD_LEN]; // 存放所有单词的二维字符数组
    int counts[MAX_WORDS]; // 存放所有单词出现的次数的一维数组（和上面的二维字符数组对应）
    int wordCount = 0; // 已经输入的单词数量
    char word[MAX_WORD_LEN]; // 存放用户输入的单个单词
    int n; // 用户要求输出的频率最高的 n 个单词
    printf("请输入单个单词，输入 -1 表示输入结束：\n");
    while(1) {
        scanf("%s", word);
        if(strcmp(word, "-1") == 0) {
            break;
        }
        if(strlen(word) > MAX_WORD_LEN) { // 如果单词长度超过了最大长度，就忽略这个单词
            printf("单词长度过长，已被忽略。\n");
            continue;
        }
        strcpy(words[wordCount], word); // 将这个单词加入到所有单词的二维字符数组中
        insert(root, word); // 将这个单词插入到字典树中
        wordCount++;
    }
    printf("请输入要输出的频率最高的单词数量 n：\n");
    scanf("%d", &n);
    if(n > wordCount) { // 如果 n 大于输入的单词数量，就将 n 赋值为单词数量
        n = wordCount;
    }
    Heap* heap = createHeap(n); // 创建一个大小为 n 的堆
    for(int i = 0; i < wordCount; i++) {
        counts[i] = root->child[words[i][0]-'a']->count; // 用字典树统计所有单词出现的次数
        if(counts[i] > 0) { // 只插入出现至少一次的单词
            insertToHeap(heap, words[i], counts[i]); // 将满足条件的单词加入到堆中
        }
    }
    printf("频率最高的 %d 个单词为：\n", n);
    heapSort(heap, heap->size); // 执行堆排序
    for(int i = 0; i < n; i++) { // 输出前 n 个最高频率的单词
        printf("%d %s\n", heap->array[heap->size-1-i].count, heap->array[heap->size-1-i].word);
    }
    return 0;
}
