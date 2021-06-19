#include <stdio.h>
#include <conio.h>

#define inputLink "D:/STUDY/185050754/THUATTOAN_FLOYD/Dothi_Floyd.txt"

#define MAX 100
#define infinite 1000

int After_Node[MAX][MAX];
int L[MAX][MAX];

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

void Floyd(int S, int F, GRAPH g)
{
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			if (g.a[i][j] > 0)
			{
				After_Node[i][j] = j;
				L[i][j] = g.a[i][j];
			}
			else
			{
				After_Node[i][j] = -1;
				L[i][j] = infinite;
			}
		}
	}
	
	for (int k = 0; k < g.n; k++)
	{
		for (int i = 0; i < g.n; i++)
		{
			for (int j = 0; j < g.n; j++)
			{
				if (L[i][j] > L[i][k] + L[k][j])
				{
					L[i][j] = L[i][k] + L[k][j];
					After_Node[i][j] = After_Node[i][k];
				}
			}
		}
	}
	
	
	if (After_Node[S][F] == -1)
	{
		printf("KHong co duong di tu dinh %d den dinh %d.\n", S+1, F+1);
	}
	else if (S == F)
	{
		printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n", S+1, F+1);
		printf("Voi tong trong so la: %d", 0);
	}
	else
	{
		printf("Duong di ngan nhat tu dinh %d den dinh %d la: \n", S+1, F+1);
		printf("\t%d ", S+1);
		int u = S;
		while (After_Node[u][F] != F)
		{
			u = After_Node[u][F];
			printf("--> %d", u+1);
		}
		
		printf("--> %d", F+1);
		printf("\nVoi tong trong so la: %d", L[S][F]);
	}
}

void Bai1(GRAPH g)
{
	int S, F;
	do
	{	
		printf("Nhap dinh dau: S = ");
		scanf("%d", &S);
	} while (S <= 0 || S > g.n);
	do
	{
		printf("Nhap dinh dau: F = ");
		scanf("%d", &F);
	} while (F <= 0 || F > g.n);	
	Floyd(S-1, F-1, g);
}

void Bai2 (GRAPH g)
{
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			if (j == i)
			 	continue;
			else
			{
				Floyd(i, j, g);
				printf("\n");
			}
			printf("\n");		
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
			printf("\n\n===BAI 1===\n");
			Bai1(g);
			printf("\n\n===BAI 2===\n");
			Bai2(g);
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	
	return 0;
}
