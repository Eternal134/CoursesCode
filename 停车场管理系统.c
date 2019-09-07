#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 5			//停车场最大容纳量
#define Price 5				//停车每小时单价

typedef struct{					//定义车辆结构体
    char car_id[9];					//车牌号
    float begin_time;					//进入停车场的时间，用于计时收费
    float end_time;						//离开停车场的时间，用于计时收费
}Car;

typedef struct {				//表示停车场的顺序栈
    Car *base;
    Car *top;
    int stacksize; 
}SqStack;

Car Pop(SqStack *S){			//弹出栈顶元素
    return *--S->top;
}

void Push(SqStack *S,Car car){				//压栈操作
    *S->top ++ = car;
}

typedef struct QNode{					//定义队列节点
    Car car;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct LQueue{					//表示便车区的链队
    QNode *front;
    QNode *rear;
}LQueue;

SqStack *InitSqStack(){							//初始化栈
	SqStack *S;
	S = (SqStack *)malloc(sizeof(SqStack));
	S->base = (Car *)malloc(sizeof(Car)*MAXSIZE);
	S->top = S->base;
	S->stacksize = MAXSIZE;
	return S;
}

void EnQueue(LQueue *Q,Car car){			//入队
	QNode *p = (QNode *)malloc(sizeof(QNode));
    p->car = car;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

Car DeQueue(LQueue *Q){					//出队
	QNode *p = Q->front->next;
	Car car = p->car;
	Q->front->next = p->next;
	if(Q->rear == p) Q->rear = Q->front;
	free(p);
	return car;
}

void PopStack(SqStack *S, Car *p){				
	//弹出任意栈中元素的函数
    SqStack *T;				//定义一个栈，用于暂存指定弹出元素前面的元素
	Car *q;
	Car car;
	T = InitSqStack();
	while(S->top-1>p){
		//将指定元素在栈中前面的所有元素按顺序弹出到交换栈T
		Push(T,Pop(S));
	}
	car = Pop(S);			//删除指定元素
	while(T->top != T->base){
		Push(S,Pop(T));				//将交换栈中的元素按顺序压入原栈中，此时指定元素已经被删除
	} 
}

void Enter(SqStack *S, LQueue *Q, Car car){
	//车辆进入停车场
    if(S->top - S->base == S->stacksize){
		//如果栈满，代表停车场已达最大容量
    	printf("停车场已满，您的车辆已进入便车区排队等候！\n\n");
	    EnQueue(Q,car);				//将car入队，代表车辆进入便车区队列
    }
    else{
        //如果停车场未满，将car压栈，代表车辆已进入停车场
        Push(S, car);
        printf("您的车辆已进入停车场并开始计费！\n\n");
    }
}

void Out(SqStack *S, LQueue *Q, Car car){
	//车辆离开停车场
	float time_long;		//暂存停车总计时的变量，方便输出信息
    Car *p;					//循环变换
    Car c;
    float cost;					//暂存本次停车总收费
    int flag = 0;					//标志变量，如果有车辆退出停车场的操作，flag设为1
    if(S->top == S->base){
		//如果停车场中没有任何车辆，输出提示信息
        printf("\n停车场中没有该车辆!");
    }
    else{
        for(p = S->base;p <= S->top;p++){
			//遍历栈
            if(strcmp(p->car_id,car.car_id) == 0) {
				//找到对应车牌号相同的栈元素
            	cost = Price*(car.end_time - p->begin_time);			//计算停车费
            	time_long = car.end_time - p->begin_time;				//暂存停车的总时间
				PopStack(S,p);					//将栈中的对应元素删除，代表车辆离开了停车场
				flag = 1;						//有车辆离开停车场，将flag值置为1
            	printf("您的车辆已离开停车场！共计时--%.2f--时，您共需要支付：",time_long);
               	printf("\n---%.2f元\n", cost);
				printf("\n感谢您的光顾！\n");
            	break;					//结束循环
        	}
        }
		if(!flag){
			//如果flag的值仍为0，则没有在栈中找到相应的元素，代表停车场中没有该车
			printf("停车场中没有该车，请检查输入车牌号是否有误!\n\n");
		}
        else if(Q->front != Q->rear){
			//如果有车辆离开了停车场且便车区有车辆排队，安排进入停车场
        	c = DeQueue(Q);				//出队，表示便车区排在最前面的车辆可以进入停车场
        	c.begin_time = car.end_time;			//车辆进入停车场的起始时间为前一辆车离开时的时间
        	Push(S,c);				//压栈，代表车辆进入停车场
        	printf("\n停车场已有空位，车辆--%s--已从便车区进入停车场并开始计费！\n\n",c.car_id); 
    	}
        
    }
}

int main(){
    SqStack *S;
    LQueue *Q;
    S = InitSqStack();
    //初始化队列，（调用函数时出错）
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->front->next = NULL;

    Car car;
    int flag;       //定义标志变量，根据flag的判断用户选择的是什么操作
    float time;
    int hour,minute;
    printf("\n-------------欢迎来到***Eternal***的停车场！-------------\n\n");

    while(1){
		printf("\n******************************************\n");
    	printf("请选择服务（停车输入0，离开输入1，退出系统输入2）：\n");
    	printf("-------------\t");
    	scanf("%d",&flag);
    	if(2 == flag) break; 			//如果输入了2，停止循环
    	getchar();					//吸收掉上一次输入时的回车
    	printf("请输入你的车牌号（不超过8位）：\n");
    	printf("-------------\t");
    	gets(car.car_id);				//输入车牌号
    	printf("请输入停车/离开时间（24小时制，格式为时：分）\n");
    	printf("-------------\t");
    	scanf("%d:%d",&hour,&minute);				//输入时间
    	time = hour + (float)minute/60;					//以小时为单位换算时间

    	if(0 == flag){
			//如果输入了0，安排停车
        	car.begin_time = time;				//将输入的时间设为进入停车场的时间
        	Enter(S,Q,car);					//进入停车场
    	}
    	else{
			//如果是1，安排车辆离开停车场
        	car.end_time = time;				//将输入的时间设为离开停车场的时间
        	Out(S,Q,car);					//离开停车场
    	}
	}
    return 0;
}
