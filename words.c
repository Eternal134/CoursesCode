/*
    本程序中共使用线性顺序表、链表、哈希表的开放地址法、哈希表的链地址法和二叉排序树的存储结构
    每种存储结构都有三种处理方法：创建、打印输出和检索，函数名称的关键词分别带有Creat、Print、Search
    每种存储结构的所有功能都封装在带有关键词Function的函数中
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX 1000
#define HashMax 30

typedef struct
{   //表示每个单词的出现频率
    char word[30];
    int sum;
}WordData;

typedef struct LNode
{   //表示链表的节点
    WordData word_data;
    struct LNode *next;
}LNode;

typedef struct HNode
{   //表示哈希表的存储单元
    WordData word_data;
    int flag;
}HNode;

int ListGetWords(WordData words[])
{   //从文件中读取文章并统计词频保存到顺序表
    FILE *fp;
    if((fp = fopen("InFile.txt", "r")) == NULL)
    {   //打开文件
        printf("open file failed");
        exit(0);
    }
    int i = 0, flag = 1, j = 0, k, s = 0;        //flag = 1时表示读取单词, = 2时代表一个单词读取结束，s表示不同单词的总数
    char c;     //从文件读取字符暂时保存到c中
    char w[30];     //将读取的单词暂存到w中
    w[0] = 0;      //w的首字符置为0
    while(!feof(fp))
    {   //遍历文件
        c = fgetc(fp);
        if(c == ' ' || c == ',' || c == '.' || c == '\n' || c == '\\')
        {   
            if(flag == 1)
            {   //如果前一时刻正在录入单词，表示一个单词的结束
                flag = 2;
            }
            else    
            {   //否则什么也不做
                flag = 0;
            }           
        }
        else
        {   //如果c不是特殊符号，表示现在是录入单词状态
            flag = 1;
        }
        if(flag == 1)
        {   //录入单词状态
            w[i] = c;
            i ++;
            w[i] = 0;   //字符床结尾置为0
        }
        else if(flag == 2)
        {   //如果一个单词刚录入结束，
            strlwr(w);      //将这个单词转换成小写
            for(k = 0; k < s; k ++)
            {   //遍历顺序表，看这个单词是否已存在
                if(strcmp(words[k].word, w) == 0)
                {   //如果已经存在，将该单词的总数+1
                    words[k].sum ++;
                    i = 0;      //i置为0，表示顺序表中已有该单词
                    break;
                }
            }
            if(i)
            {   //如果i不为0，将该单词放到一个新的储存空间中
                s ++;
                strcpy(words[s-1].word, w);
                words[s-1].sum ++;
                i = 0;
            }
            
        }
    }
    fclose(fp);
    return s;
}

int Partition(WordData words[], int low, int high)
{   //快速排序中返回枢轴位置，见教材《数据结构》P245
    WordData word;
    word = words[low];
    char pivotkey[30];
    strcpy(pivotkey, word.word);
    while(low < high)
    {
        while(low < high && strcmp(words[high].word, pivotkey) >= 0)
        {
            high --;
        }
        words[low] = words[high];
        while(low < high && strcmp(words[low].word, pivotkey) <= 0)
        {
            low ++;
        }
        words[high] = words[low];
    }
    words[low] = word;
    return low;
}

void QuickListSort(WordData words[], int low, int high)
{   //快速排序
    int pivotloc;
    if(low < high)
    {
        pivotloc = Partition(words, low, high);
        QuickListSort(words, low, pivotloc - 1);
        QuickListSort(words, pivotloc + 1, high);
    }
}

void PrintList(WordData words[], int words_sum)
{   //打印顺序表中储存的信息
    int i;
    for (i = 0; i < words_sum; i++)
    {
        printf("%-15s%d\n", words[i].word, words[i].sum);       
    }
}

WordData SearchList(WordData words[], int words_sum, char word[])
{   //顺序表中的折半查找，《数据结构》P193
    int low = 0, high = words_sum, mid;
    while(low <= high)
    {
        mid = (low + high) / 2;
        if(strcmp(words[mid].word, word) == 0)
        {
            return words[mid];
        }
        else if(strcmp(words[mid].word, word) > 0)
        {
            high = mid - 1;
        }
        else 
        {
            low = mid + 1;
        }
    }
    //如果没有找到，返回这个空变量
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

LNode *CreatLinkList(WordData words[], int words_sum)
{   //根据顺序表的内容创建链表
    LNode *rear, *p;
    LNode *W = (LNode *)malloc(sizeof(LNode));
    rear = W;
    int i;
    for(i = 0; i <= words_sum; i ++)
    {
        p = (LNode *)malloc(sizeof(LNode));
        p->word_data = words[i];
        rear->next = p;
        rear = p;
        rear->next = NULL;
    }
    return W;
}

void PrintLinkList(LNode *W)
{   //打印链表中的信息
    LNode *p;
    for(p = W->next; p->next; p = p->next)
    {
        printf("%-15s%d\n", p->word_data.word, p->word_data.sum);
    }
}

WordData SearchLinkList(LNode *W, char word[])
{   //顺序查找链表
    LNode *p = W;
    for(;p->next; p = p->next)
    {
        if(strcmp(p->word_data.word, word) == 0)
        {
            return p->word_data;
        }
    }
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

void FunctionLinkList(WordData words[], int words_sum)
{
    LNode *W = CreatLinkList(words, words_sum);     //定义链表
    char fs[20];
    int f;    
    while(1)    
    {
        printf("\n$链表$  请选择功能：\n1、查看词频统计结果\n2、查找单词\n0、上一步\n>> ");
        gets(fs);       //用字符串接收输入
        if(strlen(fs) != 1)
        {   //如果输出字符串的长度不为1，肯定违法
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        f = fs[0] - '0';    //将字符转化为数字
        if(f < 0 || f > 2)
        {   //如果这个数字不在0和2之间，也违法
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        switch(f)
        {
            case 1:

                printf("\n$链表$  文章中出现的单词及其频率如下：\n");
                printf("单词         总数  \n");
                PrintLinkList(W);
                break;

            case 2:

                printf("\n$链表$  输入你想要查找的单词：\n>> ");
                char word[30];
                gets(word);
                WordData search_result;     //接收查找的结果
                search_result = SearchLinkList(W, word);
                if(search_result.sum != 0)
                {
                    printf("\n单词%s在文章中出现的次数是%d次\n", word, search_result.sum);
                }
                else
                {
                    printf("\n单词%s不存在！\n", word);
                }
                break;

            case 0:

                printf("\n");
                return ;
        }
    }
}

void FunctionList(WordData words[], int words_sum)
{   
    char fs[20];    
    int f;
    while(1)
    {
        printf("\n$顺序表$  请选择功能：\n1、查看词频统计结果\n2、查找单词\n0、上一步\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 2)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        switch(f)
        {
            case 1:
                
                printf("\n$顺序表$  文章中出现的单词及其频率如下：\n");
                printf("单词         总数  \n");
                PrintList(words, words_sum);
                break;

            case 2:

                printf("\n$顺序表$  输入你想要查找的单词：\n>> ");
                char word[20];
                WordData search_result;
                // getchar();
                gets(word);
                search_result = SearchList(words, words_sum , word);
                if(search_result.sum != 0)
                {
                    printf("\n单词%s在文章中出现的次数是%d次\n", word, search_result.sum);
                }
                else
                {
                    printf("\n单词%s不存在！\n", word);
                }
                break;

            case 0:

                printf("\n");
                return ;
        }
    } 
}

typedef struct HashLinkNode
{   //链地址法哈希表的节点
    WordData word;
    HashLinkNode *next;
}HashLinkNode;

int Hash(char word[])
{   //根据字符串的首字母计算哈希值，与'a'的差就是哈希值
    int hash;
    hash = word[0] - 'a';   
    return hash;
}

void CreatLinkHash(WordData words[], int words_sum, HashLinkNode H[])
{   //创建链地址法哈希表
    int i, hash;
    HashLinkNode *h, *p = (HashLinkNode *)malloc(sizeof(HashLinkNode));
    for(i = 0; i < HashMax; i ++)
    {   // 哈希表初始化
        H[i].next = NULL;
    }
    for(i = 0; i < words_sum; i ++)
    {   //把顺序表中的元素储存到链地址哈希表中
        h = (HashLinkNode *)malloc(sizeof(HashLinkNode));
        h->word = words[i];
        h->next = NULL;
        hash = Hash(words[i].word);
        for(p = &H[hash]; p->next; p = p->next)
        {
            ;
        }
        p->next = h;
        h->next = NULL;
    }
}

void PrintLinkHash(HashLinkNode H[])
{
    int i;
    HashLinkNode *h;
    for(i = 0; i < HashMax; i ++)
    {
        for(h = H[i].next; h; h = h->next)
        {
            printf("%-15s%d\n", h->word.word, h->word.sum);
        }
    }
}

WordData SearchLinkHash(HashLinkNode H[], char word[])
{   //根据要找的字符串的哈希值检索哈希表
    int hash = Hash(word);
    HashLinkNode *h;
    for(h = &H[hash]; h; h = h->next)
    {
        if(strcmp(word, h->word.word) == 0)
        {
            return h->word;
        }
    }
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

void CreatHashList(WordData words[], int words_sum, HNode HL[])
{   //创建开放地址法哈希表，用二次探测法处理冲突，《数据结构》P223
    int i, j, h;
    for(i = 0; i <= MAX; i ++)
    {   //初始化哈希表
        HL[i].flag = 0;
        HL[i].word_data.sum = 0;
    }
    for(i = 0; i <= words_sum; i ++)
    {
        h = Hash(words[i].word);
        if(HL[h].flag == 0)
        {
            HL[h].word_data = words[i];
            HL[h].flag = 1;
        }
        else
        {
            for(j = 1; j < sqrt(MAX); j ++)
            {   //二次探测法处理冲突
                h = int(h + pow(-1, i+1) * pow(i, 2) + MAX) % MAX;
                if(HL[h].flag == 0)
                {
                    HL[h].word_data = words[i];
                    HL[h].flag = 1;
                    break;
                }
                h = int(h + pow(-1, i) * pow(i, 2) + MAX) % MAX;
                if(HL[h].flag == 0)
                {
                    HL[h].word_data = words[i];
                    HL[h].flag = 1;
                    break;
                }
            }
        }
    }
}

void PrintHashList(HNode HL[])
{   
    int i;
    for(i = 0; i < MAX; i ++)
    {
        if(HL[i].word_data.sum)
        {
            printf("%-15s%d\n", HL[i].word_data.word, HL[i].word_data.sum);
        }
    }
}

WordData SearchHashList(HNode HL[], char word[])
{
    int i;
    for(i = 0; i < MAX; i ++)
    {
        if(strcmp(HL[i].word_data.word, word) == 0)
        {
            return HL[i].word_data;
        }
    }
    WordData word_null;
    word_null.sum = 0;
    return word_null;
}

void FunctionHash(WordData words[], int words_sum)
{   
    char fs[20];
    int f, flag = 0;
    while(1)
    {
        printf("\n请选择哈希表的冲突处理方法：\n1、开放地址法\n2、链地址法\n0、上一步\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 2)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        switch(f)
        {
            case 1:
                //选择开放地址法哈希表
                HNode HL[MAX];
                CreatHashList(words, words_sum, HL);
                while(1)
                {
                    printf("\n$开放地址法哈希表$  请选择功能：\n1、查看词频统计结果\n2、查找单词\n0、上一步\n>> ");
                    gets(fs);
                    if(strlen(fs) != 1)
                    {
                        printf("\n无效输入，请重新选择：\n");
                        continue;
                    }
                    f = fs[0] - '0';
                    if(f < 0 || f > 2)
                    {
                        printf("\n无效输入，请重新选择：\n");
                        continue;
                    }
                    switch(f)
                    {
                        case 1:
                            
                            printf("\n$开放地址法哈希表$  文章中出现的单词及其频率如下：\n");
                            printf("单词         总数  \n");
                            PrintHashList(HL);
                            break;

                        case 2:

                            printf("\n$开放地址法哈希表$  输入你想要查找的单词：\n>> ");
                            char word[20];
                            WordData search_result;
                            gets(word);
                            search_result = SearchHashList(HL, word);
                            if(search_result.sum != 0)
                            {
                                printf("\n单词%s在文章中出现的次数是%d次\n", word, search_result.sum);
                            }
                            else
                            {
                                printf("\n单词%s不存在！\n", word);
                            }
                            break;

                        case 0:
                            
                            flag = 1;
                            break;
                    }
                    if(flag)
                    {
                        break;
                    }
                }
                break;     //case1   

            case 2:
                //选择链地址法哈希表
                flag = 0;
                HashLinkNode H[HashMax];
                CreatLinkHash(words, words_sum, H);        //创建链地址法哈希表
                while(1)
                {
                    printf("\n$链地址法哈希表$  请选择功能：\n1、查看词频统计结果\n2、查找单词\n0、上一步\n>> ");
                    gets(fs);
                    if(strlen(fs) != 1)
                    {
                        printf("\n无效输入，请重新选择：\n");
                        continue;
                    }
                    f = fs[0] - '0';
                    if(f < 0 || f > 2)
                    {
                        printf("\n无效输入，请重新选择：\n");
                        continue;
                    }
                    switch(f)
                    {
                        case 1:
                            
                            printf("\n$链地址法哈希表$  文章中出现的单词及其频率如下：\n");
                            printf("单词         总数  \n");
                            PrintLinkHash(H);
                            break;

                        case 2:

                            printf("\n$链地址法哈希表$  输入你想要查找的单词：\n>> ");
                            char word[20];
                            WordData search_result;
                            gets(word);
                            search_result = SearchLinkHash(H, word);
                            if(search_result.sum != 0)
                            {
                                printf("\n单词%s在文章中出现的次数是%d次\n", word, search_result.sum);
                            }
                            else
                            {
                                printf("\n单词%s不存在！\n", word);
                            }
                            break;

                        case 0:
                            
                            flag = 1;
                            break;
                    }//switch
                    if(flag)
                    {
                        break;
                    }
                }//while
                break;  //case2

            case 0:

                return ;
            
        }//switch1
    }//while
}

typedef struct BSTNode
{   //二叉树节点
    WordData word;
    struct BSTNode *lchild, *rchild;
}BSTNode, *BSTree;

BSTree InsertBST(BSTree T, WordData word)
{   //二叉树的插入算法，《数据结构》P201
    BSTNode *S;
    if(!T)
    {
        S = (BSTNode *)malloc(sizeof(BSTNode));
        S->word = word;
        S->lchild = S->rchild = NULL;
        T = S;
        return T;
    }
    else if(strcmp(word.word, T->word.word) > 0)
    {
        T->rchild = InsertBST(T->rchild, word);
    }
    else if(strcmp(word.word, T->word.word) < 0)
    {
        T->lchild = InsertBST(T->lchild, word);
    }
}

BSTree CreatBST(WordData words[], int words_sum)
{   //创建二叉排序树
    BSTree T = NULL;
    int i;
    for(i = 0; i <= words_sum; i ++)
    {
        if(words[i].sum)
        {
            T = InsertBST(T, words[i]);
        }       
    }
    return T;
}

void PrintBST(BSTree T)
{
    if (T)
    {
        PrintBST(T->lchild); 
        printf("%-15s%d\n", T->word.word, T->word.sum);
        PrintBST(T->rchild);
    }
}

BSTNode *SearchBST(BSTree T, char word[])
{   //二叉树的递归查找，《数据结构》P199
    if(!T || !strcmp(word, T->word.word))
    {
        return T;
    }
    else if(strcmp(T->word.word, word) > 0)
    {
        return SearchBST(T->lchild, word);
    }
    else if(strcmp(T->word.word, word) < 0)
    {
        return SearchBST(T->rchild, word);
    }
}

void FunctionBST(WordData words[], int words_sum)
{
    BSTree T = CreatBST(words, words_sum);
    char fs[20];
    int f;
    while(1)
    {
        printf("\n$二叉排序树$  请选择功能：\n1、查看词频统计结果\n2、查找单词\n0、上一步\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 2)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        switch(f)
        {
            case 1:
                
                printf("\n$二叉排序树$  文章中出现的单词及其频率如下：\n");
                printf("单词         总数  \n");
                PrintBST(T);
                break;

            case 2:

                printf("\n$二叉排序树$  输入你想要查找的单词：\n>> ");
                char word[20];
                BSTNode *t;
                gets(word);
                t = SearchBST(T, word);
                if(t)
                {
                    printf("\n单词%s在文章中出现的次数是%d次\n", t->word.word, t->word.sum);
                }
                else
                {
                    printf("\n单词%s不存在！\n", word);
                }
                break;

            case 0:

                printf("\n");
                return ;
        }
    }
}

int main()
{
    WordData words[MAX];
    int words_sum, f;
    char fs[20];
    words_sum = ListGetWords(words);
    printf("文章\"InFile\"的词频统计完成！\n");
    QuickListSort(words, 0, words_sum - 1);
    while(1)
    {
        printf("\n选择要使用的存储结构：\n1、顺序表\n2、链表\n3、二叉排序树\n4、哈希表\n0、退出\n>> ");
        gets(fs);
        if(strlen(fs) != 1)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        f = fs[0] - '0';
        if(f < 0 || f > 4)
        {
            printf("\n无效输入，请重新选择：\n");
            continue;
        }
        switch(f)
        {
            case 1:

                FunctionList(words, words_sum);
                break;

            case 2:

                FunctionLinkList(words, words_sum);
                break;

            case 3:

                FunctionBST(words, words_sum);
                break;

            case 4:

                FunctionHash(words, words_sum);
                break;

            case 0:

                return 0;
        }
    }
}