#include <iostream>

int ceil(float a)
{
	return a + (a > int(a));
}

int round(float a)
{
	return (int)a + (a-(int)a >= .5);
}

int floor(float a)
{
	return a;
}

const int maxnum = 10;

int main()
{
	int histo[maxnum];
	for (int i = 0; i < maxnum; i++)
		histo[i] = 0;

	float curnum;
	while (std::cin >> curnum)
	{
		histo[floor(curnum)]++;
	}

	int highest = 0;
	for (auto i : histo)
	{
		if (i > highest)
			highest = i;
	}

	highest = floor(highest / 20.0);

	for (int row = highest+1; row > 0; row--)
	{
		for (int col = 0; col < maxnum; col++)
		{
			if (ceil(histo[col] / 20.0) >= row)
				std::cout << '*';
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
	
}