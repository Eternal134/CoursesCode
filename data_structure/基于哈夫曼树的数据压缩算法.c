#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define inf 32767
typedef struct{
	//哈夫曼树结点的结构体类型 
	int weight;
	int parent,lchild,rchild;
}HTNode,*Huffmantree;

typedef struct{
	//统计输入的字符的频率的结构体 
	char c;
	int num;
}Diff;
	
void Select(Huffmantree HT,int n,int *s,int *ss){
	//选择前n个结点中权值最小的两个结点的函数 
	int j,min1=inf,min2=inf,temp;												 
	for(j=1;j<=n;j++){															//先找出最小的一个 
		if(HT[j].weight<min1&&HT[j].parent==0){
			*s=j;	min1=HT[j].weight;
		}
	}
	temp=min1;																	//用temp记下最小的权值 
	HT[*s].weight=inf;															//将这个最小的权值改成无限大 
	for(j=1;j<=n;j++){															//再找出此时最小的权值的结点，即权值第二小的结点 
		if(HT[j].weight<min2&&HT[j].parent==0){									
			*ss=j;	min2=HT[j].weight;
		}
	}
	HT[*s].weight=temp;															//把最小的权值改回来 
}

Huffmantree CreatHuffmantree(int dn,Diff *diff){
	//建立哈夫曼树 
	int a,b,i;
	int *s1=&a,*s2=&b;
	int m=2*dn-1;																//储存整棵哈夫曼树需要的空间m 
	Huffmantree HT=(HTNode *)malloc((m+1)*sizeof(HTNode));						//开辟哈夫曼树的空间 
	
	for(i=1;i<=m;i++){															//将每个节点的双亲和左右孩子都置为0 
		HT[i].parent=HT[i].rchild=HT[i].lchild=0;
	}
	for(i=1;i<=dn;i++){															//根据统计到的字符出现的频率，对哈夫曼树各结点的权值初始化 
		HT[i].weight=diff[i-1].num;
	}
	for(i=dn+1;i<=m;i++){														//根据已知的结点确定未知的结点 
		Select(HT,i-1,s1,s2);													//选择前i个结点中权值最小的两个 
		HT[*s1].parent=i;	HT[*s2].parent=i;									//将他们的双亲结点置为i 
		HT[i].lchild=*s1;	HT[i].rchild=*s2;									//将i结点的左右孩子分别指向s1，s2 
		HT[i].weight=HT[*s1].weight+HT[*s2].weight;								//i结点的权值为s1和s2的权值之和 
	}
	return HT;																	//返回已经建立好的哈夫曼树 
}

char **Huffmancode(Huffmantree HT,int n){
	//根据建立的哈夫曼树对不同字符进行编码 
	int start,c,f,i;															
	char **HC=(char **)malloc((n+1)*sizeof(char));								//开辟储存所有编码的指针数组HC 
	char *cd=(char *)malloc(n*sizeof(char));									//临时编码字符串cd 
	cd[n-1]='\0';																//将cd的最后一个字符置为0 
	for(i=1;i<=n;i++){															//对字符编码的过程 
		start=n-1;																//每确定一位编码，从后向前写入cd，从n-1位置开始写 
		c=i;f=HT[i].parent;														//c是待确定编码的字符，f指向c的双亲节点 
		while(f!=0){															//没有访问到根结点时 
			start--;															//待确定的编码向前移动一位 
			if(HT[f].lchild==c) cd[start]='0';									//如果f的左孩子是c，则编码0 
			else cd[start]='1';													//否则编码1 
			c=f;f=HT[f].parent;													//c改为f，f继续向上找 
		}
		HC[i]=(char *)malloc((n-start)*sizeof(char));							//开辟储存本次确定的字符编码的字符串空间 
		strcpy(HC[i],&cd[start]);												//将cd中的字符串写入HC中 
	}
	free(cd);																	//释放cd的空间 
	return HC;																	//返回编码信息 
}

int main(){
	//----------------统计字符串中出现的字符的频率----------------- 
	char str[50];																//储存需要编码的字符串 
	printf("输入需要编码的字符串：输入0以结束\n");
	gets(str);																	//输入需要编码的字符串 
	while(strcmp(str,"0")){														//在没有输入0时重复以下操作 
	int i,j,len,dn=1;															//定义循环变量i,j,字符串长度len，不同的字符个数dn 
	Diff diff[20];																//定义储存不同的字符的名字和频率的结构体数组 
	len=strlen(str);															//测量需要编码的字符串的长度 
	diff[0].c=str[0];	diff[0].num=1;
	for(i=1;i<len;i++){															//遍历输入的每个字符 
		for(j=0;j<dn;j++){														//将当前访问到的字符与已经确定过的字符比较 
			if(diff[j].c==str[i]){												//如果遇到相同的字符，该字符的频率加1 
				diff[j].num++;
				break;
			}
		}
		if(j==dn){																//如果j==dn，代表上层循环没有提前结束，则出现了新的元素 
			diff[j].c=str[i];													//此时，将该字符的信息赋给一个新的结构体数组的空间 
			diff[j].num=1;
			dn++;																//dn加1 
		}
	}
	Diff d;																		//下面是对已经确定的不重复的字符根据ASCII码冒泡排序 
	for(i=0;i<dn-1;i++)
		for(j=0;j<dn-i-1;j++){
			if(diff[j].c>diff[j+1].c){
				d=diff[j];	diff[j]=diff[j+1];	diff[j+1]=d;
			}
		}
	printf("字符串中出现的字符及其频率：（按ASCII码排列）\n");
	for(i=0;i<dn;i++){
		printf("%c:%d ",diff[i].c,diff[i].num);
	}
	//-------------根据输入的字符串建立相应的哈夫曼树--------------
	Huffmantree HT;																//定义哈夫曼树HT 
	HT=CreatHuffmantree(dn,diff);												//建立哈夫曼树 
	printf("\n建立的哈夫曼树的存储结构的终态：\n");
	for(i=1;i<=2*dn-1;i++){
		printf("%d %d %d %d %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	} 
	//-------------------求每个字符的哈夫曼编码--------------------
	char **code=Huffmancode(HT,dn);												//储存每个字符的哈夫曼编码的指针数组code 
	printf("每个字符对应的哈夫曼编码为：\n");
	for(i=1;i<=dn;i++){											
		printf("%c:%s ",diff[i-1].c,*(code+i));
	} 
	//----------------------求编码后的字符串-----------------------
	char result[100];															//储存编码的字符串result 
	int place=0;																//place指当前写到的result串的位置，方便下次写入 
	for(i=0;i<len;i++){															//遍历需要编码的字符串的每个字符 
		for(j=0;j<dn;j++){														//将当前需要比较的字符与确定了的字符的哈夫曼编码匹配 
			if(str[i]==diff[j].c){
				 strcpy(&result[place],*(code+j+1));
				 place+=strlen(*(code+j+1));
			}
		}
	}
	printf("\n编码后的字符串为：\n");
	puts(result);
	// ----------------------求解码后的字符串-----------------------
	char decode[len];															//储存解码后字符串的数组decode 
	int p,c=2*dn-1,l=0;															//p为依次遍历编码字符串的变量，c表示当时访问的哈夫曼树的结点，初始化为根结点，l表示解码的进度 
	for(p=0;p<strlen(result);p++){												//遍历编码的每个字符 
		if(result[p]=='0') c=HT[c].lchild;										//如果是0，访问左孩子 
		else c=HT[c].rchild;													//否则，是1，访问右孩子 
		if(HT[c].lchild==0&&HT[c].rchild==0){									//如果结点的左右孩子都是0，则是叶子结点 
			decode[l]=diff[c-1].c;												//将已经确定的字符写入decode中 
			l++;																//准备确定下一字符 
			decode[l]='\0';														//字符串的结尾赋值为/0 
			c=2*dn-1;															//再将C指向根结点 
		}
	}
	printf("\n解码字符串：\n");
	puts(decode);																//输出解码的字符串 
	printf("\n\n输入需要编码的字符串：输入0以结束\n");
	gets(str);																	//输入下一需要操作的字符串 
	}
	return 0; 
}
