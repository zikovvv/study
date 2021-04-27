#include<time.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
const int N = 1000;
int temp;
int *bubble(int *mass)
{
	for (int iter_glob = 1; iter_glob < N; iter_glob++)
	{
		for (int iter_loc = 0; iter_loc < N - iter_glob; iter_loc++)
		{
			if (mass[iter_loc] > mass[iter_loc + 1])
			{
				temp = mass[iter_loc + 1];
				mass[iter_loc + 1] = mass[iter_loc];
				mass[iter_loc] = temp;
			}
		}
	}
	for (int i = 0; i < N - 1; i++)
	{
		printf("%d ", mass[i]);
	}
	return mass;
}
int linear(int elem, int mass[])
{
	int out = -1;
	for (int i = 0; i < N; i++)
	{
		if (mass[i] == elem) return i;
	}
	return out;
}
int bin(int elem, int mass[])
{
	float step = (float)N / 4;
	float middle = (float)N / 2;
	while (elem != mass[(int)middle])
	{
		if (step < 0.5) return -1;
		middle += step * (elem > mass[(int)middle] ? 1 : -1);
		//printf("%f %f\n", middle, step);
		step /= 2;
	}
	return middle;
}
int main()
{
	int index;
	int mass[N];
	clock_t start;
	for (int i = 0; i < N; i++)
	{
		mass[i] = rand() % 4000 - 2000;
		//printf("%d\n", mass[i]);
	}
	bubble(mass);

	start = clock();
	for (int i = 0; i < 100000; i++) { index = linear(mass[500], mass); }
	printf("\nFinding element No. 500 time: %f, result : %d", float(clock() - start) / CLOCKS_PER_SEC, index);

	start = clock();
	for (int i = 0; i < 100000; i++) { index = bin(mass[500], mass); }
	printf("\nFinding element No. 500 time: %f, result : %d", float(clock() - start) / CLOCKS_PER_SEC, index);

	return 1;
}
