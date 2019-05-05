#include <iostream>

int rX, rY, mX, mY, n, m;
unsigned int** topo;
bool** check;
int litres = 0;

void fill(int I, int J, int& l)
{
	if (I == mX && J == mY)
	{
		l = 0;
		return;
	}
	l++;
	topo[I][J]++;

	#ifdef DBG
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				std::cerr << topo[i][j] << ' ';
			}
			std::cerr << std::endl;
		}
		std::cerr << std::endl;
		std::cin.ignore();
	#endif
	
	for (int p : {-2, -1, 1, 2})
	{
		int i = I + p % 2;
		int j = J + p / 2;

		if (i < 0 || i >= n || j < 0 || j >= m)
			continue;

		if (topo[I][J] - topo[i][j] != 1)
			continue;
			
		fill(i, j, l);
	}
}


int find(int I, int J)
{
	if (I == mX && J == mY)
		return -69;
		
	check[I][J] = 1;

	int bestp = -69;
	unsigned int lowest = -1;
	for (int p : {-2, -1, 1, 2})
	{
		int i = I + p % 2;
		int j = J + p / 2;

		if (i < 0 || i >= n || j < 0 || j >= m)
			continue;

		if (topo[i][j] > topo[I][J] || check[i][j])
			continue;

		if (topo[i][j] < lowest)
		{
			lowest = topo[i][j];
			bestp = p;
		}
	}
	
	if (bestp == -69)
	{
		return J*n+I;
	}
	else
	{
		return find(
			I + bestp % 2,
			J + bestp / 2
		);
	}
	
		
}
int main()
{

	std::cin >> m >> n;
	topo = (unsigned int**)malloc(sizeof(unsigned int*) * n);
	check = (bool**)malloc(sizeof(bool*) * n);
	for (int i = 0; i < n; i++)
	{
		topo[i] = (unsigned int*)malloc(sizeof(unsigned int) * m);
		check[i] = (bool*)malloc(sizeof(bool) * m);
		for (int j = 0; j < m; j++)
		{
			std::cin >> topo[i][j];
		}
	}

	std::cin >> rX >> rY;
	std::cin >> mX >> mY;
	rX--;
	rY--;
	mX--;
	mY--;

	for (;;)
	{
		#ifdef DBG
			std::cerr << "============\n";
		#endif
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				check[i][j] = false;
	
		int code = find(rX, rY);
		if (code == -69)
		{
			//litres++;
			break;
		}

		int l = 0;
		fill(code % n, (code - code % n) / n, l);
		if (l == 0)
			break;
		litres += l;
	}

	std::cout << litres << std::endl;
}

/*
5 3
3 1 3 0 4
2 2 3 0 2
0 0 2 1 2
3 3
2 2


4 4
0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
3 3
1 1

4 4
0 0 3 0
0 0 3 0
0 0 3 0
0 0 3 0
4 4
1 1

4 4
0 0 3 0
0 0 3 0
0 0 3 0
0 0 2 0
4 4
1 1

4 4
5 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0
4 4
1 1

4 4
5 4 3 2
4 3 2 1
3 2 1 0
2 1 0 0
4 4
1 1

4 4
5 4 3 2
4 3 2 3
3 2 3 4
2 3 4 5
4 4
1 1

1 1
0
1 1
1 1
*/