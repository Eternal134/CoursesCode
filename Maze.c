//迷宫问题

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{   /*  
     * 此处的结构体有两个用处：
     *   一、在栈中表示可以通过的路径，这时 n 表示通路的下一步的方向，值为1时表示下步向左，2表示下步向右，
     * 3表示下步向上，4表示下步向下；
     *   二、在结构体数组中表示迷宫本身，这是 n 表示该节点的一些情况，值为0时表示可以通过，1表示“墙壁”，即
     * 不能通过，2表示该节点已经走过，3表示该节点已经走过且从此节点通过是“死路”；
     */
    int x, y, n;               
}Data;


typedef struct StackNode
{   //链栈节点类型
    Data data;            
    struct StackNode *next;
}StackNode;

StackNode *InitStack()
{   //初始化链栈
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));          //S也是结构体，需要分配空间
    S->next = NULL;
    return S;           //**注意**，创建的链栈结尾会有一个没有值的节点，定位链栈的结尾时，需要判断下一节点是否是该空节点
}

StackNode *Push(StackNode *S, Data data)
{   //链栈压栈
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = data;
    p->next = S;
    S = p;
    return S;
}

StackNode *Pop(StackNode *S)
{   //链栈出栈
    Data data = S->data;
    StackNode *p = S;
    S = S->next;
    free(p);
    return S;
}

StackNode *Maze(StackNode *S, Data *coord, int m, int n, int flag)
{
    if(!flag)
    {
        S = Push(S, coord[0]);
        coord[0].n = 2;
    }
    
    int a, b;
    
    while (S->data.x != m-1 && S->data.y != n-1)
    {
        //“走”过的点的n值设为2
        a = S->data.x;
        b = S->data.y;           //a,b表示当前栈顶元素的坐标

        if (b > 1 && coord[a*n + b-1].n == 0)
        //向左试探
        {
            S->data.n = 1;
         coord[a*n + b-1].n = 2;
            S = Push(S, coord[a*n + b-1]);
            continue;
        }
        if (b < n && coord[a*n + b+1].n == 0)
        //向右试探
        {
            S->data.n = 2;
            coord[a*n + b+1].n = 2;
            S = Push(S, coord[a*n + b+1]);
            continue;
        }
        if (a > 1 && coord[(a-1)*n + b].n == 0)
        //向上试探
        {
            S->data.n = 3;
            coord[(a-1)*n + b].n = 2;
            S = Push(S, coord[(a-1)*n + b]);
            continue;
        }
        if (a < m && coord[(a+1)*n + b].n == 0)
        //向下试探
        {
            S->data.n = 4;
            coord[(a+1)*n + b].n = 2;
            S = Push(S, coord[(a+1)*n + b]);
            continue;
        }
        //如果周围没有可以走的路，从栈中弹出该节点并把该坐标的n设为3

        if(S->next->next == NULL)
        {   //如果节点周围没有通路而且该节点是迷宫的入口，表示该迷宫无解
            return S;
        }
        S = Pop(S);
        coord[a*n + b].n = 3;
    }//while

    //下面一系列 if-else 判断最后一步的走法
    if(S->data.x == 0)
    {   //如果x是0，表示出口靠上侧墙壁，下一步应该向上走，以下判断类似
        S->data.n = 3;
    }
    else if(S->data.x == m-1)
    {
        S->data.n = 4;
    }
    if(S->data.y == 0)
    {
        S->data.n = 1;
    }
    else if(S->data.y == n-1)
    {
        S->data.n = 2;
    }
    return S;
}

int OutputPath(StackNode *S)
{
    StackNode *T = InitStack();         //用于逆序输出栈S中的内容
    StackNode *p = S;       //定义遍历循环变量
    while (p->next)
    {   //将栈S中的元素倒序放到T中
        T = Push(T, p->data);
        p = p->next;
    }
    
    printf("迷宫的一条通路为（三元组的前两位数表示坐标，最后一位数代表方向，1为左，2为右，3为上，4为下）：\n");
    for (p = T; p->next; p = p->next)
    {   //将T中的元素内容输出
        printf("%d %d %d\n",p->data.x + 1, p->data.y + 1, p->data.n);
    }
    return 0;
}

int main()
{   
    StackNode *S = InitStack();
    int m, n, i, j;             //迷宫的宽为m，高为n，i,j为循环变量
    printf("输入你的迷宫的高和宽：\n");
    scanf("%d%d",&n,&m);

    Data coord[m][n];           //结构体数组，用来存储迷宫
    printf("现在开始构建你的迷宫(0为通路，1为断路，其中第一个元素为迷宫入口，且出口在右侧或下侧)：\n");
    //输入迷宫信息
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &coord[i][j].n);
            coord[i][j].x = i;
            coord[i][j].y = j;
        }
    }

    int flag = 0;           //flag用来判断是否已经求出了一条通路，如果是，flag设为1
    while(1)
    {   
        S = Maze(S, *coord, m, n, flag);            //求出迷宫的一条通路
        if(S->next->next == NULL && flag)
        {   //如果S中只有一个节点且已经求出过一个通路，该迷宫没有其他解
            printf("迷宫无其他解！\n");
            break;
        }
        else if(S->next->next == NULL && !flag)
        {   //如果S中只有一个节点且没有求出过通路，证明该迷宫无解
            printf("迷宫无解！\n");
            return 0;
        }
        flag = 1;
        OutputPath(S);              //输出求出的路径

        printf("通路表示为：\n");
        for(i = 0; i < m; i++)
        {   //用*表示通路
            for ( j = 0; j < n; j++)
            {
                if(coord[i][j].n == 2)
                {
                    printf("* ");
                }
                else if(coord[i][j].n == 3)
                {
                    printf("0 ");
                }
                else
                {
                    printf("%d ",coord[i][j].n);
                }
        }
        printf("\n");
        }//for
        
        coord[S->data.x][S->data.y].n = 3;              //将上次求出的出口的n值设为3
        S = Pop(S);                 //将出口从S中删除，准备求下一条通路
    }//while
    return 0;
}
