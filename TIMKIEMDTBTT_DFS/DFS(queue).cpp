#include <stdio.h>
#include <conio.h>

#define inputLink "D:/STUDY/185050754/TIMKIEMDTBTT_DFS/Dothi_DFS.txt"
#define MAX 100

int ArrTrace[MAX];
int ArrLabel[MAX];

struct GRAPH
{
	int n;
	int a[MAX][MAX];
};

struct QUEUE
{
	int size;
	int array[MAX];
};

int ReadMatrix(char filepath[100], GRAPH &g)
{
	FILE* f;
	f = fopen(filepath,"rt");
	
	if (f == NULL)
	{
			printf("can not open this file");
			return 0;
		}
	
	fscanf(f, "%d", &g.n);
	
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n;j++)
		{
			fscanf(f, "%d", &g.a[i][j]);
		}
	}
	
	fclose(f);
	return 1;
}

void OutputMatrix(GRAPH g)
{
	printf("The number of vertices in the graph is: %d\n", g.n);
	
	printf("The adjacency matrix of the graph is: \n");
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			printf("\t%d", g.a[i][j]);
		}
		printf("\n");
	}
}

int ValidityCheck(GRAPH g)
{
	for (int i = 0; i < g.n; i++)
	{
		if (g.a[i][i] != 0)
			return 0;
	}
	return 1;
}

void DFSSearch(int s,GRAPH g)
{
	int ArrTrace[MAX];
	int ArrLabel[MAX];
	for(int i=0;i<g.n;i++)
	{
		ArrTrace[i]=-1;
		ArrLabel[i]=0;
	}
	int ArrDFS[MAX];
	int numVertex = 0;
	ArrLabel[s] = 1;
	printf("%d-->", s);
	ArrDFS[numVertex++] = s;
	while(numVertex > 0)
	{
		int u = ArrDFS[--numVertex];
		printf("%d-->", u);
		for(int v = 0; v < g.n; v++)
		{
			if(g.a[u][v] !=0 && ArrLabel[v] == 0)
			{
				ArrLabel[v] = 1;
				if(ArrTrace[v] ==-1)
					ArrTrace[v] = u;
				ArrDFS[numVertex++] = v;
				break;
			}		
		}
	}
}

int main()
{
	GRAPH g;
	
	if (ReadMatrix(inputLink, g) == 1)
	{
		printf("Retrieved graph information from file successfully \n");
		OutputMatrix(g);
		
		if (ValidityCheck(g) == 1)
		{
			printf("The graph is valid\n");
			DFSSearch(0,g);
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	
	return 0;
}
