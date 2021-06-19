#include <stdio.h>
#include <conio.h>

#define inputLink "D:/STUDY/185050754/THUATTOAN_DIJKSTRA/Dothi_Dijkstra.txt"

#define MAX 100
#define infinite 1000

int ArrTrace[MAX];
int ArrLabel[MAX];
int Length[MAX];

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
		if (g.a[i][i] != 1000)
			return 0;
	}
	return 1;
}

int FindTheSmallestPath(GRAPH g)
{
	int li = -1;
	float p = infinite;
	
	for (int i = 0; i < g.n; i++)
	{
		if (ArrLabel[i] == 0 && Length[i] < p)
		{
			p = Length[i];
			li = i;
		}
	}
	
	return li;
}

void UpdateRoute(int n, GRAPH g)
{
	ArrLabel[n] = 1;
	for (int j = 0; j < g.n; j++)
	{
		if (ArrLabel[j] == 0 && g.a[n][j] > 0 && g.a[n][j] < infinite)
		{
			if (Length[j] > Length[n] + g.a[n][j])
			{
				Length[j] = Length[n] + g.a[n][j];
				ArrTrace[j] = n;
			}
		}
	}
}

void ThuatToan_Dijkstra(int S, int F, GRAPH g)
{
	int i;
	for (int j = 0; j < g.n; j++)
	{
		ArrLabel[j] = 0;
		Length[j] = infinite;
		ArrTrace[j] = -1;	
	}
	
	Length[S] = 0;
	
	while (ArrLabel[F] == 0)
	{
		int u = FindTheSmallestPath(g);
		if (u == -1)
		{
			break;
		}
		UpdateRoute(u, g);
	}
	
	if (ArrLabel[F] == 1)
	{
		printf("\nDuong di ngan nhat tu dinh %d den dinh %d la: \n\t", S, F);
		i = F;
		printf("%d ", F);
		while (ArrTrace[i] != S)
		{
			printf("<- %d", ArrTrace[i]);
			i = ArrTrace[i];
		}
		
		printf("<- %d", ArrTrace[i]);
		printf("\n\tVoi do dai la %d\n", Length[F]);
	}
	else
	{
		printf("Khong co duong di tu dinh %d den dinh %d\n", S, F);
	}

}

void Bai1(GRAPH g)
{
	int S, F;
	do
	{
		printf("\nNhap S = ");
		scanf("%d", &S);
	}while (S < 0 || S > g.n);
	do
	{
		printf("Nhap F = ");
		scanf("%d", &F);
	}while (F < 0 || F > g.n);
	ThuatToan_Dijkstra(S, F, g);
}

void Bai3(GRAPH g)
{
	for (int i = 1; i < g.n; i++)
		ThuatToan_Dijkstra(0, i, g);
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
			printf("\n===Bai 1===");
			Bai1(g);
			printf("\n===Bai 3===");
			Bai3(g);
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	
	return 0;
}
