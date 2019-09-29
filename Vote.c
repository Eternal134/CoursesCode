#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Player
{
    int serial, votes, rank;
    char name[15];
}Player;

Player *InitPlayers(int sum)
{
    Player *players = (Player *)malloc(sum * sizeof(Player));
    printf("请输入各位选手的序号和姓名：\n");
    int ser, i;
    char name[15];
    Player player;
    for(i = 0; i < sum; i ++)
    {
        scanf("%d", &(players + i)->serial);
        getchar();
        gets((players + i)->name);
        (players + i)->votes = 0;
    }
    return players;
}

void Vote(Player *players)
{
    printf("请输入喜欢的选手的序号为Ta投票：输入0表示投票结束\n");
    int ser = 1;
    while(ser)
    {
        scanf("%d", &ser);
        (players + ser - 1)->votes ++;
    }
}

void SelectSort(Player *players, int sum)
{   //选择排序
    Player *p;
    Player temp;
    int i, j, max;
    for(i = 0; i < sum; i ++)
    {
        max = i;
        for(j = i + 1; j < sum; j ++)
        {
            if((players + j)->votes > (players + max)->votes)
            {
                max = j;
            }
        }
        temp = *(players + i);
        *(players + i) = *(players + max);
        *(players + max) = temp;
        if(i == 0 || (players + i)->votes != (players + i - 1)->votes)
        {
            (players + i)->rank = i + 1;
        }
        else
        {
            (players + i)->rank = (players + i - 1)->rank;
        }
    }
}

void BubbleSort(Player *players, int sum)
{   //冒泡排序
    int flag = 1, i ,j ,m = sum;
    Player player;
    while ((m > 0) && (flag))
    {
        flag = 0;
        for(j = 0; j <= m; j ++)
            if((players + j)->votes < (players + j + 1)->votes)
            {
                flag = 1;
                player = *(players + j);
                *(players + j) = *(players + j + 1);
                *(players + j + 1) = player;
            }
            -- m;
    }
    for(i = 0; i < sum; i ++)
    {
        if(i == 0 || (players + i)->votes != (players + i - 1)->votes)
        {
            (players + i)->rank = i + 1;
        }
        else
        {
            (players + i)->rank = (players + i - 1)->rank;
        }
    }
}

int Partition(Player *players, int low, int high)
{
    Player player;
    player = *(players + low);
    int vote = player.votes;
    while (low < high)
    {
        while(low < high && (players + high)->votes <= vote)
        {
            high --;
        }
        *(players + low) = *(players + high);
        while(low < high && (players + low)->votes >= vote)
        {
            low ++;
        }
        *(players + high) = *(players + low);
    }
    *(players + low) = player;
    return low;
}

void QuickSort(Player *players, int low, int high)
{   //快速排序
    int pivotloc;
    if(low < high)
    {
        pivotloc = Partition(players, low, high);
        QuickSort(players, low, pivotloc - 1);
        QuickSort(players, pivotloc + 1, high);
    }
    for(int i = 0; i < high; i ++)
    {
        if(i == 0 || (players + i)->votes != (players + i - 1)->votes)
        {
            (players + i)->rank = i + 1;
        }
        else
        {
            (players + i)->rank = (players + i - 1)->rank;
        }
    }
}

void Print(Player *players, int sum)
{   //输出选手的排名信息
    int i;
    printf("选手的排名信息如下：\n");
    for(i = 0; i < sum; i ++)
    {
        switch((players + i)->rank)
        {
            case 1:
                if(i == 0 || (players + i)->rank != (players + i - 1)->rank)
                {
                    printf("冠军：%d号选手%s\t%d票", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d号选手%s\t%d票", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;

            case 2:
                if((players + i)->rank != (players + i - 1)->rank)
                {
                    printf("\n亚军：%d号选手%s\t%d票", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d号选手%s\t%d票", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;

            case 3:
                if((players + i)->rank != (players + i - 1)->rank)
                {
                    printf("\n季军：%d号选手%s\t%d票", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d号选手%s\t%d票", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;

            default:
                if((players + i)->rank != (players + i - 1)->rank)
                {
                    printf("\n第%d名：%d号选手%s\t%d票", (players + i)->rank, (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                else
                {
                    printf("\t%d号选手%s\t%d票", (players + i)->serial, (players + i)->name, (players + i)->votes);
                }
                break;
        }
    }
}

int main()
{
    Player *players;
    printf("参赛选手的总人数为：");
    int sum;
    scanf("%d", &sum);
    players = InitPlayers(sum);
    Vote(players);
    int f;
    printf("\n选择排序方法：\n\t1.选择排序\n\t2.冒泡排序\n\t3.快速排序\n");
    scanf("%d", &f);
    switch(f)
    {
        case 1:
            SelectSort(players, sum);
            break;

        case 2:
            BubbleSort(players, sum);
            break;

        case 3:
            QuickSort(players, 0, sum);
            break;
    }
    Print(players, sum);
    return 0;
}
