#include <stdio.h>
#include <conio.h>
#include <cstdio>

#define inputLink "D:/STUDY/185050754/MATRANLIENTHONG/Dothi1.txt"
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

void SetLabel(GRAPH g, int Label[])
{
	for (int i = 0; i < g.n; i++)
		Label[i] = 0;
}

void VertexConnectWithI(GRAPH g, int Label[], int vertexI)
{
	for (int j = 0; j < g.n; j++)
	{
		if (g.a[vertexI][j] != 0 && Label[j] != Label[vertexI])
		{
			Label[j] = Label[vertexI];
				
			VertexConnectWithI(g,Label, j);
		}
	}
}

int NumberComponent(GRAPH g, int Label[])
{
	int numberComponent = 0;
	for (int i = 0; i < g.n; i++)
	{
		if (Label[i] == 0)
		{
			numberComponent++;
			Label[i] = numberComponent;
			VertexConnectWithI(g, Label, i);
		}
	}
	return numberComponent;
}

void ListComponent(GRAPH g, int Label[], int nComp)
{
	for (int i = 1; i <= nComp; i++)
	{
		printf("Thanh phan lien thong thu %d gom cac dinh: ", i);
		for (int j = 0; j < g.n; j++)
		{
			if (Label[j] == i)
				printf("\t%d", j+1);
		}
		printf("\n");
	}
}

void CheckComponent(GRAPH g)
{
	int Label[Max];
	
	SetLabel(g, Label);
	
	int number = NumberComponent(g,Label);
	printf("\nNumber of Component: %d\n", number);
	
	ListComponent(g,Label, number);
	
	if (number >= 1)
	{
		printf("Do thi lien thong");
	}
	else
	{
		printf("Do thi khong lien thong");
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
			
			CheckComponent(g);
			
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	return 0;
}
