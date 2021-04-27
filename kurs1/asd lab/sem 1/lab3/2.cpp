#include<time.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
const int N = 200;
int temp, r;
clock_t start;

int *permutat(int mass[]) 
{
	for (int i = N; i >= 1; i--)
	{
		r = rand() % i;
		temp = mass[i];
		mass[i] = mass[r];
		mass[r] = temp;
	}
	return mass;
}
int max(int mass[]) 
{
	int n = mass[0], len = sizeof(mass);
	for (int i = 0; i < len; i++)
	{
		if (n < mass[i]) 
		{
			n = mass[i];
		}
	}
	return n;
}
int m(int n) 
{
	int mn = 0, digit;
	while (n) 
	{
		digit = n % 10;
		n /= 10;
		if (digit > mn) 
		{
			mn = digit;
		}
	}
	return mn;
}
int *sort(int mass[]) 
{
	int n1, n2;
	for (int i = 0; i < N - 1; i ++) 
	{
		for (int j = i + 1; j < N; j++)
		{
			n1 = mass[i], n2 = mass[j];
			int max1 = m(n1);
			int max2 = m(n2);

			if (max1 > max2) 
			{

				mass[j] = n1;
				mass[i] = n2;
			}
			else if(max1 == max2)
			{
				if (n1 >= n2) 
				{
					mass[j] = n1;
					mass[i] = n2;
				}
			}
		}
	}
	return mass;
}
int main()
{
	int mass[N];
	int *permutated;
	int *sorted;
	for (int i = 0; i < N; i++) { mass[i] = i + 1; }
	permutated = permutat(mass);
	for (int i = 0; i < N; i++) 
	{
		printf("%d ", permutated[i]);
	}
	printf("\n\n");

	sorted = sort(mass);
	for (int i = 0; i < N; i++)
	{
		printf("%d ", sorted[i]);
	}

	return 1;

}