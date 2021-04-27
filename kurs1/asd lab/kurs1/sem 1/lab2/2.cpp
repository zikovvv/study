#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
int to_6(int n10) 
{
	int n6 = 0, i = 0;
	while (n10 > 0) 
	{
		n6 += (n10 % 6) * pow(10, i);
		n10 = n10 / 6;// (n10 - n10 % 6) / 6;
		i++;
	}
	return n6;
}
int back_to_10(int n6, int n10 = 0, int i = 0)
{
	while (n6 > 0)
	{
		n10 += (n6 % 10) * pow(6, i);
		n6 = (n6 - n6 % 10) / 10;
		i++;
	}
	return n10;
}
int main()
{
	int n;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("10-ове число: ");
	scanf_s("%d", &n);
	printf("В 6-овій системі числення: %d\n", to_6(n));
	printf("6-ове число:");
	scanf_s("%d", &n);
	printf("В 10-овій системі числення: %d\n", back_to_10(n));
	return 1;
}
