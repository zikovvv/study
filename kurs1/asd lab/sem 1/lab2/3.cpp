#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>

int fib(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fib(n - 1) + fib(n - 2);
}
int func(int last1, int last2, int limit) 
{
	int temp = last2 + last1;
	if (temp >= limit) return 0;
	last1 = last2;
	last2 = temp;
	return 1 + func(last1, last2, limit);
	
	
	//if (temp < limit)
	//{
		//last1 = last2;
		//last2 = temp;
		//printf("%d, %d\n", i, last2);
		//printf("%d ", last2);
		//i++;
		//func(last1, last2, i, limit);
	//}
	//else return i;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int last1 = 0, last2 = 1, i = 2, limit;
	printf("Введіть ліміт: ");
	scanf_s("%d", &limit);
	if (limit == 0) { printf("\nКількість чисел Фібоначчі менших за %d: %d", limit, 0); }
	else if (limit == 1) { printf("\nКількість чисел Фібоначчі менших за %d: %d", limit, 1); }
	else {
		i = func(last1, last2, limit) + 2;
		printf("\nКількість чисел Фібоначчі менших за %d: %d", limit, i);
	}
	return 1;
}