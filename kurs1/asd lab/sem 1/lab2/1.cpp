#include<time.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>
#include<windows.h>

float resheto(int len)
{
	float time_for_calc = clock();
	bool* primes = new bool[len + 1];
	for (int i = 0; i <= len; i++) { primes[i] = true; }
	for (int i = 2; i <= ceil(sqrt(len)); i++)
	{
		if (primes[i])
		{
			for (int j = pow(i, 2); j <= len; j += i)
			{
				primes[j] = false;
			}
		}
	}
	time_for_calc = clock() - time_for_calc;
	for (int i = 2; i <= len; i++)
	{
		if (primes[i])
		{
			//printf("%d ", i);
		}
	}
	return time_for_calc;
}
bool isPrime(int n)
{
	bool prime = true;
	int len = floor(sqrt(n));
	if (n == 1) { prime = false; }
	else {
		for (int i = 2; i <= len; i++)
		{
			if (n % i == 0)
			{
				prime = false;
				break;
			}
		}
	}
	return prime;
}
float perebor(int nb_primes)
{
	int n = 2, i = 0;
	
	while(i < nb_primes)
	{
		if (isPrime(n))
		{
			i++;
			//printf("%d ", n);
		}
		n++;
	}
	//printf("\n\n");
	
	return 1;
}
void main1() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	scanf_s("%d", &n);
	printf("%s", isPrime(n) ? "is prime" : "is not prime");
}

void main2() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int diapazon;
	printf("diapazon:");
	scanf_s("%d", &diapazon);
	resheto(diapazon);
}
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int number_of_primes = 100;
	float time_prebor = clock();
	for (int i = 0; i < 1000; i++)
	{	
		perebor(number_of_primes);
	}
	printf("%f\n", (clock() - time_prebor) / CLOCKS_PER_SEC);

	float time_p = clock();
	for (int i = 0; i < 1000; i++)
	{
		resheto(542);
	}
	printf("%f", (clock() - time_p)/ CLOCKS_PER_SEC);
}





