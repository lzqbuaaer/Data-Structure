#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define NHASH  3001
#define MULT  37
typedef struct Index{
    int start,num;
}index;
typedef struct Node{
    char word[25];
    struct Node* next;
}node;
char words[4000][25];
int sum=0;
index s[30];
node* h[3010];
unsigned int hash(char *str)
{
    unsigned int h=0;
    char *p;
    for(p=str; *p!='\0'; p++)
    h = MULT*h + *p;
    return h % NHASH;
}
int cnt;
int find(char*w,int b,int e){
    cnt++;
    if(b>e){
        cnt--;
        return 0;
    }
    else if(b==e){
        if(strcmp(words[b],w)==0)
        return 1;
        else return 0;
    }
    else{
        int m=(b+e)/2;
        int p=strcmp(words[m],w);
        if(p<0)
        return find(w,m+1,e);
        else if(p>0)
        return find(w,b,m-1);
        else return 1;
    }
}
int main(){
    FILE* dic=fopen("dictionary3000.txt","r");
    for(int i=0;i<26;i++){
        s[i].num=0;
    }
    node* ed[3010];
    for(int i=0;i<3010;i++){
        ed[i]=h[i]=NULL;
    }
    while(fscanf(dic,"%s",words[sum])!=EOF){
        int hans=hash(words[sum]);
        if(h[hans]==NULL){
            h[hans]=(node*)malloc(sizeof(node));
            h[hans]->next=NULL;
            strcpy(h[hans]->word,words[sum]);
            ed[hans]=h[hans];
        }
        else{
            ed[hans]->next=(node*)malloc(sizeof(node));
            ed[hans]=ed[hans]->next;
            ed[hans]->next=NULL;
            strcpy(ed[hans]->word,words[sum]);
        }
        
        int p=words[sum][0]-'a';
        if(s[p].num==0){
            s[p].start=sum;
        }
        s[p].num++;
        sum++;
    }

    char w[25];
    int n,p,ans;
    scanf("%s %d",w,&n);
    switch (n){
        case 1:
        for(int i=0;i<sum;i++){
            cnt++;
            int a=strcmp(w,words[i]);
            if(a>0)
            continue;
            else if(a==0){
                printf("1 %d",cnt);
                break;
            }
            else{
                printf("0 %d",cnt);
                break;
            }
        }
        break;
        case 2:
        ans=find(w,0,sum-1);
        printf("%d %d",ans,cnt);
        break;
        case 3:
        p=w[0]-'a';
        ans=find(w,s[p].start,s[p].start+s[p].num-1);
        printf("%d %d",ans,cnt);
        break;
        case 4:
        p=hash(w);
        ans=0;
        for(node* i=h[p];i!=NULL;i=i->next){
            cnt++;
            if(strcmp(i->word,w)==0){
                ans=1;
                break;
            }
        }
        printf("%d %d",ans,cnt);
    }
    return 0;
}