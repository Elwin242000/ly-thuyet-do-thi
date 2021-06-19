#include <stdio.h>
#include <conio.h>
#include <cstdio>

#define inputLink "D:/STUDY/185050754/CHUTRINHDUONGDI_EULER/Dothi1E.txt"
#define Max 100

struct GRAPH
{
	int n;
	int a[Max][Max];
};

int ReadMatrix(char filepath[100], GRAPH &g)
{
	FILE* f;
	f = fopen(filepath, "rt");
	
	if (f == NULL)
	{
		printf("can not open this file");
		return 0;
	}
	
	fscanf(f, "%d", &g.n);
	
	for (int i = 0; i < g.n; i++)
		for (int j = 0; j < g.n; j++)
			fscanf(f, "%d", &g.a[i][j]);
	
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

int CheckDegree(GRAPH g)
{
	for (int i = 0; i < g.n; i++)
	{
		int S = 0;
		for (int j = 0; j < g.n; j++)
		{
			if (g.a[i][j] != 0)
				S++;
		}
		if (S % 2 != 0)
			return 0;
	}
	return 1;
}

void FindWay(int i, GRAPH &g, int Euler[], int &sodinhtrongeuler)
{
	for (int j = 0; j < g.n; j++)
	{
		if (g.a[i][j] != 0)
		{
			g.a[i][j] = g.a[j][i] = 0;
			FindWay(j, g, Euler, sodinhtrongeuler);
		}
	}
	Euler[sodinhtrongeuler++] = i + 1;
}

int CheckEuler(GRAPH g)
{
	if (CheckDegree(g) == 0)
		return 0;
	int x = 0;
	int flag = 0;
	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
			if (g.a[i][j] != 0)
			{
				x = i;
				flag =1;
			}
		if (flag == 1)
			break;
	}
	GRAPH temp = g;
	int Euler[Max] = {};
	int VertexNumber = 0;
		
	FindWay(x, temp, Euler, VertexNumber);
		
	for (int i = 0; i < temp.n; i++)
		for (int j = 0; j < temp.n; j++)
			if (temp.a[i][j] != 0)
				return 0;
		
	if (Euler[0] != Euler[VertexNumber-1])
		return 0;
		
	printf("\nChu trinh Euler: ");
	for (int i = VertexNumber-1; i >= 0; i--)
		printf("\t%d", Euler[i]);
	return 1;
}

int CheckWay(GRAPH g)
{
	int x = 0;
	int flag = 0; 
	int bac; 
	for (int i = 0; i < g.n; i++)
	{ 
		bac = 0; 
		for (int j = 0; j < g.n; j++)
		{ 
			if (g.a[i][j] != 0)
			{
				bac++;
			} 
		}
		if (bac%2 != 0)
		{
			x = i;
			flag = 1;
			break;
		}
	}
	if(flag == 0)
		return 0;	
	GRAPH temp = g;
	int Euler[Max] = {};
	int VertexNumber = 0;
		
	FindWay(x, temp, Euler, VertexNumber);
	
	for (int i = 0; i < temp.n; i++)
		for (int j = 0; j < temp.n; j++)
			if (temp.a[i][j] != 0)
				return 0;
		
	if (Euler[0] == Euler[VertexNumber-1])
		return 0;
		
	printf("\n\nDuong di Euler: ");
	for (int i = VertexNumber-1; i >= 0; i--)
		printf("\t%d", Euler[i]);
	return 1;
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
			if (!CheckEuler(g))
			{
				printf("\nKhong co chu trinh Euler\n");
			}
			if (!CheckWay(g))
			{
				printf("\n\nKhong co duong di Euler\n");	
			}
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	return 0;
}
