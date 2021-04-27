// laba1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
void task1()
{
	setlocale(LC_CTYPE, "rus");
	int number1, number2;
	float mean_arifm, mean_geom;
	printf("Число 1:");
	scanf_s("%d", &number1);
	printf("Число 2:");
	scanf_s("%d", &number2);
	mean_arifm = (pow(number1, 3) + pow(number2, 3)) / 2;
	mean_geom = sqrt(abs(number1) * abs(number2));
	printf("середнє арифметичне кубів: %f,\nсереднє геометричне модулів: %f", mean_arifm, mean_geom);
}
void task2()
{
	setlocale(LC_CTYPE, "rus");
	int x, y, z;
	printf("x:");
	scanf_s("%d", &x);
	printf("y:");
	scanf_s("%d", &y);
	printf("z:");
	scanf_s("%d", &z);
	if (x <= y & y <= z) { printf("%d, %d, %d", x, y, z); }
	if (x <= z & z <= y) { printf("%d, %d, %d", x, z, y); }
	if (y <= x & x <= z) { printf("%d, %d, %d", y, x, z); }
	if (y <= z & z <= x) { printf("%d, %d, %d", y, z, x); }
	if (z <= y & y <= x) { printf("%d, %d, %d", z, y, x); }
	if (z <= x & x <= y) { printf("%d, %d, %d", z, x, y); };
}
void task3()
{
	setlocale(LC_CTYPE, "rus");
	for (int i = 16; i < 100; i += 4) 
	{
		if (i % 6 != 0) { printf("%d\n", i); }
	}
}

void task4()
{
	setlocale(LC_CTYPE, "rus");
	float mass[16];
	
	//довжина масиву
	int len = 16;
	float k;
	for (int i = 0; i < len; i++)
	{
		//випадкові числа в масив
		mass[i] = rand() % 201;
		//виведення
		printf("%f\n", mass[i]);
	}
	float max = mass[0] + mass[15];
	//for (int i = 0; i < len; i++){scanf_s("%f", &mass[i]);}

	for (int i = 0; i < len / 2; i++) 
	{
		k = mass[i] + mass[len - i - 1];
		if (k > max)
		{
			max = k;
		}
	}
	printf("max: %f", max);
}
bool function(float x0, float y0, float x1, float y1, float r0, float r1)
{
	float len = sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
	float radius_sum = r0 + r1;
	if (radius_sum >= len) { return true; }
	else { return false; }
}
int f(int a, int b, int c) 
{
	if (a >= b & a >= c) { return a; }
	if (b >= a & b >= c) { return b; }
	if (c >= b & c >= a) { return c; }
}
bool task5()
{
	setlocale(LC_CTYPE, "rus");
	float x0, y0, x1, y1, r0, r1;
	printf("x першого центра:");
	scanf_s("%f", &x0);
	printf("y першого центра:");
	scanf_s("%f", &y0);
	printf("x другого центра:");
	scanf_s("%f", &x1);
	printf("y другого центра:");
	scanf_s("%f", &y1);
	printf("радiус першого кола:");
	scanf_s("%f", &r0);
	printf("радiус другого кола:");
	scanf_s("%f", &r1);
	bool out = function(x0, y0, x1, y1, r0, r1);
	return out;
}

void main()
{
	setlocale(LC_CTYPE, "rus");
	printf("%d", task5());
}