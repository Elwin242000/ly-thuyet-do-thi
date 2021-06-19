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

void DFS(int v, GRAPH g)
{
	ArrLabel[v] = 1;
	int u;
	for (u = 0; u < g.n; u++)
	{
		if (g.a[v][u] != 0 && ArrLabel[u] == 0)
		{
			ArrTrace[u] = v;
			DFS(u,g);
		}
	}
}

void duyettheoDFS(int S, int F, GRAPH g)
{
	int i;
	
	for(int i=0;i<g.n;i++)
	{
		ArrTrace[i]=-1;
		ArrLabel[i]=0;
	}
	
	DFS(S,g);
	
	if (ArrLabel[F] == 1)
	{
		printf("\nDuong di tu dinh %d den dinh %d la: \n\t", S, F);
		i = F;
		printf("%d ", F);
		while (ArrTrace[i] != S)
		{
			printf("<-- %d ", ArrTrace[i]);
			i = ArrTrace[i];
		}	
		printf("<-- %d ", ArrTrace[i]);
	}
	else
	{
		printf("\nKhong co duong di tu dinh %d den dinh %d", S, F);
	}
}

void Bai1(GRAPH g)
{
	printf("==BAI 1==");
	for (int i = 1; i < g.n; i++)
		duyettheoDFS(0,i,g);
}

void Bai2(GRAPH g)
{
	int S, F;
	printf("\n\n==BAI 2==");
	do
	{
		printf("\nNhap S = ");
		scanf("%d", &S);
	}while (S < 0 || S >= g.n);
	do
	{
		printf("Nhap F = ");
		scanf("%d", &F);
	}while (F < 0 || F >= g.n);
	duyettheoDFS(S,F,g);
}

int main()
{
	GRAPH g;
	int S, F;
	
	if (ReadMatrix(inputLink, g) == 1)
	{
		printf("Retrieved graph information from file successfully \n");
		OutputMatrix(g);
		
		if (ValidityCheck(g) == 1)
		{
			printf("The graph is valid\n");
			Bai1(g);
			
			Bai2(g);
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	
	return 0;
}
