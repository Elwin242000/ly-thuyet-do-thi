#include <stdio.h>
#include <conio.h>

#define inputLink "D:/STUDY/185050754/TIMKIEMDTBTT_BFS/Dothi_BFS.txt"
#define MAX 100

struct GRAPH
{
	int n;
	int a[MAX][MAX];
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

void BFSSearch(int s, int f, GRAPH g)
{
	int ArrTrace[MAX];
	int ArrLabel[MAX];
	
	for (int i = 0; i < g.n; i++)
	{
		ArrLabel[i] = 0;
		ArrTrace[i] = -1;
	}
	
	int ArrBFS[MAX];
	int numVertex = 0;
	ArrLabel[s] = 1;
	ArrBFS[numVertex++] = s;
	while (numVertex > 0)
	{
		int v = ArrBFS[0];
		for (int i = 0; i < numVertex-1; i++)
			ArrBFS[i] = ArrBFS[i+1];
		numVertex--;
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
			
		
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	
	return 0;
}
