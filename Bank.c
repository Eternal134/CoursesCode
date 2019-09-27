#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int begin_time;
    int end_time;
}Cust;

typedef struct QNode
{
    Cust cust;
    struct QNode *next;
}QNode;

typedef struct LQueue
{
    QNode *front;
    QNode *rear;
    int sum;        
}LQueue;

LQueue *InitQueue()
{
    LQueue *Q = (LQueue *)malloc(sizeof(LQueue));
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;
    Q->sum = 0;
    return Q;
}

void EnQueue(LQueue *Q, Cust cust)
{
    QNode *p = (QNode *)malloc(sizeof(QNode));
    p->cust = cust;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    Q->sum ++ ;
}

Cust DeQueue(LQueue *Q)
{
    QNode *p = Q->front->next;
    Cust cust = p->cust;
    Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
    Q->sum -- ;
	return cust;
}

void Bank(LQueue *Q[4])
{
    Cust cust;
    int i;
    int hour, minutes, time = 0, f, p = 0;
    int time_all = 0, sum_all = 0;
    while(1)
    {
        printf("现在的时间是：\n");
        scanf("%d:%d", &hour, &minutes);
        if(time > hour * 60 + minutes)
        {
            printf("Error!当前时间不能小于上次输入的时间！请重新输入\n");
            continue;
        }
        time = hour * 60 + minutes;
        printf("根据输入的数字选择相应的功能:\n\t1、有客户进入银行 2、有客户离开银行 3、银行关门\n：");
        scanf("%d",&f);
        int flag = 0, win;
        QNode *q;
        switch (f)
        {
            case 1:

                cust.begin_time = time;
                sum_all ++ ;
                for(i = 0; i < 4; i++)
                {
                    if(Q[i]->sum == 0)
                    {
                        EnQueue(Q[i], cust);
                        flag = 1;
                        printf("客户已经到%d号窗口办理业务.\n", i+1);
                        break;
                    }
                    if(Q[p]->sum > Q[i]->sum)
                    {
                        p = i;
                    }
                }
                if(!flag)
                {
                    EnQueue(Q[p], cust);
                    printf("客户已在%d号窗口排队.\n", p+1);
                }
                break;
    
            case 2:

                cust.end_time = time;
                printf("有客户离开的窗口是：\n");
                scanf("%d", &win);
                if(Q[win-1]->sum == 0)
                {
                    printf("Error！该窗口已经没有人了！\n");
                    break;    
                }
                time_all += time - Q[win-1]->front->next->cust.begin_time;
                DeQueue(Q[win]);
                printf("%d号窗口办理业务的客户已经离开.\n", win);
                break;

            case 3:
                printf("银行业务系统已经关闭！\n");
                flag = 3;
                for(i = 0; i < 4; i ++)
                {
                    for(q = Q[i]->front->next; q->next; q = q->next)
                    {
                        time_all += time - q->cust.begin_time;
                    }
                }
                break;
        }
        if(flag == 3)
        {
            break;
        }
        printf("\n");
    }

    float time_aver = time_all / sum_all;
    int h;
    float m;
    h = int(time_aver / 60);
    m = time_aver - h * 60;
    printf("今天客户的平均等待时间为:\t%d时%.2f分\n", h, m);
}

int main()
{
    LQueue *Q[4];
    for(int i = 0; i < 4; i ++)
    {
        Q[i] = InitQueue();
    }
    Bank(Q);
    return 0;
} 