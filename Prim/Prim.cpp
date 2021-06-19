#include <stdio.h>
#include <conio.h>

#define inputLink "D:/STUDY/185050754/Prim/Dothi_Prim.txt"
#define MAX 100
#define infinite 1000

int ArrLabel[MAX];

struct GRAPH
{
	int n;
	int a[MAX][MAX];
};

struct EDGE
{
	int u;
	int v;
	int value;
};

EDGE T[MAX];

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

void CacDinhLienThong(GRAPH g, int Nhan[MAX], int i)
{
	for (int j = 0; j < g.n; j++)
	{
		if (g.a[i][j] != 0 && Nhan[j] != Nhan[i])
		{
			Nhan[j] = Nhan[i];
			CacDinhLienThong(g,Nhan,j);
		}
	}
}

int XetLienThong(GRAPH g)
{
	int Nhan[MAX];
	int Sothanhphanlienthong = 0;
	for (int i = 0; i < g.n; i++)
		Nhan[i] = 0;
	
	for (int i = 0; i < g.n; i++)
	{
		if (Nhan[i] == 0)
		{
			Sothanhphanlienthong++;
			Nhan[i] = Sothanhphanlienthong;
			CacDinhLienThong(g, Nhan, i);
		}
	}
	return Sothanhphanlienthong;
}

int ThuatToan_Prim(GRAPH g)
{
	if (XetLienThong(g) != 1)
	{
		printf("Do thi khong lien thong, do do khong thuc hien duoc thuat toans Prim tim cay khung nho nhat\n");
	}
	
	int nT = 0;
	
	for (int i = 0; i < g.n; i++)
		ArrLabel[i] = 0;
	ArrLabel[0] = 1;
	while (nT < g.n - 1)
	{
		EDGE Canhnhonhat;
		int Giatrinhonhat = 100;
		for (int i = 0; i < g.n; i++)
		{
			if (ArrLabel[i] == 1)
			{
				for (int j = 0; j < g.n; j++)
				{
					if (ArrLabel[j] == 0 && g.a[i][j] != 0 && Giatrinhonhat > g.a[i][j])
					{
						Canhnhonhat.u = i;
						Canhnhonhat.v = j;
						Canhnhonhat.value = g.a[i][j];
						Giatrinhonhat = g.a[i][j];
					}
				}
			}
		}
		T[nT] = Canhnhonhat;
		nT++;
		ArrLabel[Canhnhonhat.v] = 1;
	}
	int TongTrongSoCuaCayKhung = 0;
	printf("Cay khung nho nhat cua do thi la:\n");
	for (int i = 0; i < nT - 1; i++)
	{
		printf("(%d, %d), ", T[i].u, T[i].v);
		TongTrongSoCuaCayKhung += T[i].value;
	}
	printf("(%d, %d).\n", T[nT-1].u, T[nT-1].v);
	TongTrongSoCuaCayKhung += T[nT-1].value;
	printf("Tong gia tri cua cay khung la %d\n", TongTrongSoCuaCayKhung);
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
			ThuatToan_Prim(g);
		}
		else
		{
			printf("The graph is invalid\n");
		}
	}
	
	return 0;
}
