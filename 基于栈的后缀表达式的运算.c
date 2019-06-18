//基于栈的后缀表达式求值 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 1000
typedef struct SqStack{
	char *base;
	char *top;
	int size;
}SqStack;

SqStack *InitSqStack(){								//初始化栈 
	SqStack *S;
	S=(SqStack *)malloc(sizeof(SqStack));
	S->base=(char *)malloc(sizeof(char)*MAXSIZE);
	S->top=S->base;
	S->size=MAXSIZE;
	return S;
}

int IsDight(char e){								//判断元素e是否是数字 
	if(e>47&&e<58) return 1;						//'0'的ASCII码为48，'9'的ASCII码为57 
	else return 0;
}

char Pop(SqStack *S){
	if(S->base!=S->top) return *(--S->top);
	else printf("Pop error.\n");
}

void Push(SqStack *S,char e){
	if(S->top-S->base!=S->size) *S->top++=e;
	else printf("Push error.\n");
}

char GetTop(SqStack *S){
	if(S->top!=S->base) return *(S->top-1);
	else printf("GetTop error.\n");
}

typedef struct SqStack_D{
	float *base;
	float *top;
	int size;
}SqStack_D;
	
SqStack_D *InitSqStack_D(){								//初始化栈 
	SqStack_D *S;
	S=(SqStack_D *)malloc(sizeof(SqStack_D));
	S->base=(float *)malloc(sizeof(float)*MAXSIZE);
	S->top=S->base;
	S->size=MAXSIZE;
	return S;
}

float Pop_D(SqStack_D *S){
	if(S->base!=S->top) return *(--S->top);
	else printf("Pop_D error.\n");
}

float Push_D(SqStack_D *S,float e){
	if(S->top-S->base!=S->size) *S->top++=e;
	else printf("Push_D error.\n"); 
}

char Precede(char theta_1,char theta_2){
	//判断两运算符之间优先关系
	switch(theta_1){
		case '+':
		case '-':
			if(theta_2=='+'||theta_2=='-'||theta_2==')'||theta_2=='#') return '>';
		    else return '<';
		case '*':
		case '/':
			if(theta_2=='(') return '<';
			else return '>';
		case '(':
			return '<'; 
	}
}

void Input_Transf_Output(SqStack *Optr,SqStack *Result){								//输入中缀并转后缀 
	char *p,op,*q;
	char str[50];
	printf("输入一个中缀表达式，运算数不超过9:\n\t"); 
	gets(str);																			//输入中缀表达式  
	p=str;																				//操作指针p 
	while(*p!=0){																		//访问表达式的每一个字符 
		if(IsDight(*p)){																//如果是数字，直接压入Result栈 
			Push(Result,*p);
		}
		else{																			//如果是运算符 
			if(Optr->base==Optr->top) Push(Optr,*p);									//如果Optr栈没有元素，压入Optr栈 
			else if(*p=='('){															//如果是（，压入Optr栈 
				Push(Optr,*p);
			}
			else if(*p==')'){															//如果是），依次弹出Optr栈中的元素压入Result栈，直到遇到（ 
				while(*(Optr->top-1)!='('){
					Push(Result,Pop(Optr));
				}
				Pop(Optr);																//丢弃（ 和 ） 
			}
			else if(Precede(GetTop(Optr),*p)=='<'){										//如果Optr栈顶元素比当前元素优先级低 
				Push(Optr,*p);															//将当前元素压入到运算符栈 
			}
			else if(Precede(GetTop(Optr),*p)=='>'){										//如果Optr栈顶元素比当前元素优先级高
				while(Optr->base!=Optr->top&&Precede(GetTop(Optr),*p)=='>'){			//依次弹出比当前运算符优先级高的运算符到Result栈
					Push(Result,Pop(Optr));
				}
				Push(Optr,*p);															//把当前运算符压入Optr栈 
			}
		}
		p++;
	}
	while(Optr->base!=Optr->top){														//Optr栈中所有剩余元素压入Result栈 
		Push(Result,Pop(Optr));
	}																		
	q=Result->base;
	printf("对应的后缀表达式为：\n\t");
	while(q<Result->top){																//倒序输出Result中所有的元素 
		printf("%c ",*q);
		q++;
	}
}

float Operation(SqStack *S){
	//后缀表达式运算 
	SqStack_D *Dight;													//定义一个保存运算结果的栈Dight 
	SqStack *Inver;														//保存后缀表达式的倒序的栈 
	Dight=InitSqStack_D();
	Inver=InitSqStack();
	int i;
	while(S->base!=S->top){												//把Result中所有元素倒序压到Inver中 
		Push(Inver,Pop(S));
	}
	char *p=Inver->top-1;												//操作指针p初始值为Inver栈顶 
	float a,b,c;														//a，b保存运算数，c保存临时运算结果 
	while(p>=Inver->base){												//逐个访问Inver中所有元素 
		if(IsDight(*p)){												//如果是数字，弹出压入Dight 
			Push_D(Dight,Pop(Inver)-'0');
		}
		else{															//如果不是数字，则是运算符 
			b=Pop_D(Dight);												//弹出数字赋给a和b 
			a=Pop_D(Dight);
			switch(*p){													//根据运算符不同而做不同的运算 
				case '+':
					c=a+b;
					break;
				case '-':
					c=a-b;
					break;
				case '*':
					c=a*b;
					break;
				case '/':
					c=a/b;
					break;
			}
			Push_D(Dight,c);											//把临时运算结果压入Dight 
			Pop(Inver);													//删除该运算符 
		}
		p--;															//继续访问下一个元素 
	}
	return *Dight->base;												//最后Dight只剩一个元素，即最终结果，返回它 
} 

int main(){
	SqStack *Optr,*Result;												//Optr栈保存运算符，Result栈保存暂时后缀表达式 
	float re;
	Optr=InitSqStack();					 
	Result=InitSqStack();
	Input_Transf_Output(Optr,Result);									//输入中缀表达式，转化为后缀表达式，输出转化结果 
	re=Operation(Result);												//对后缀表达式进行运算 
	printf("\n运算结果是：%.2f",re);									//输出运算结果 
	free(Optr);															//释放存储空间 
	free(Result);
	return 0;
}
