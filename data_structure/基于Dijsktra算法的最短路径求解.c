#include<stdio.h>
#include<stdlib.h>
#define Inf 30000
#define	MVNum 100

typedef struct{
	char vexs[MVNum];
	int arcs[MVNum][MVNum];
	int vexnum,arcnum;
}AMGraph;

int LocateVex(char vexs[],char c){
	int i;
	for(i=0;i<MVNum;i++)
		if(c==vexs[i]) return i;
}

void ShortestPath_Dij(AMGraph G,int v0,int S[],int D[],int Path[]){
	int n=G.vexnum,v,w,i,j;
	for(v=0;v<n;v++){
		S[v]=0;
		D[v]=G.arcs[v0][v];
		if(D[v]<Inf) Path[v]=v0;
		else Path[v]=-1;
	}
	S[v0]=1;
	D[v0]=0;
	//------------------------初始化完成，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S中------------------------
	for(i=1;i<n;i++){
		int min=Inf;
		for(w=0;w<n;w++){
			if(!S[w]&&D[w]<min){
				v=w;min=D[w];
			}
		}
		S[v]=1;
		for(w=0;w<n;w++){
			if(!S[w]&&(D[v]+G.arcs[v][w])<D[w]){
				D[w]=D[v]+G.arcs[v][w];
				Path[w]=v;
			}
		}
	}
}

int main(){
	printf("基于Dijsktra算法的最短路径求解\n");
	AMGraph G;
	printf("总顶点数，总边数：（输入0 0以结束）\n");
	scanf("%d%d",&G.vexnum,&G.arcnum);
	while(G.vexnum!=0){
	//------------------------创建邻接矩阵---------------------------------- 	
	int i,j,k,w;
	char a,b;
	printf("输入顶点：\n");
	for(i=0;i<G.vexnum;i++){
		getchar();
		G.vexs[i]=getchar();
	}
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j]=Inf;
	printf("输入路径：\n"); 
	for(k=0;k<G.arcnum;k++){
		getchar();
		scanf("%c %c %d",&a,&b,&w);
		i=LocateVex(G.vexs,a);	j=LocateVex(G.vexs,b);
		G.arcs[i][j]=w;
	}
	//-------------------------Dijsktra----------------------
	int S[G.vexnum];
	int D[G.vexnum];
	int Path[G.vexnum];
	char from,to;
	printf("你想求的最短路径的起点和终点：\n");
	getchar();
	from=getchar();
	getchar();
	to=getchar();
	int v0=LocateVex(G.vexs,from),vm=LocateVex(G.vexs,to);
	int p=vm;
	w=0;
	int path[G.vexnum];
	ShortestPath_Dij(G,v0,S,D,Path);
	printf("最短路径长度：\n%d\n",D[vm]);
	//----------------------寻找路径------------------------- 
	while(p!=v0){
		path[w++]=p;
		p=Path[p];
	}
	path[w]=v0;
	w++;
	printf("最短路径为：\n");
	for(i=w-1;i>=0;i--)
		printf("%c ",G.vexs[path[i]]);
	printf("\n\n总顶点数，总边数：（输入0 0以结束）\n"); 
	scanf("%d%d",&G.vexnum,&G.arcnum);
}
	return 0;
}











