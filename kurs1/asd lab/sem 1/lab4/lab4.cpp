#include <iostream>
#include <string>
#define N 7
using namespace std;

struct change 
{
	string str;
	int row;
};
struct stack 
{
	change* changes[N];
};
int size(stack* hist)
{
	for (int i = 0; i < N; i++)
	{
		if (!hist->changes[i]) return i;
	}
	return N;
}
void push(stack *hist, change *a)
{
 	int l = size(hist);
	if (l == N) { cout << "push: error, stack is full" << endl; }
	else { hist->changes[l] = a; }
}
bool empty(stack* hist) { return size(hist) == 0; }
change *top(stack *hist) 
{
	if (!empty(hist)) return hist->changes[size(hist) - 1];
	cout << "top: error, stack is empty" << endl;
	return 0;
}
void pop(stack *hist) 
{
	if (!empty(hist)) hist->changes[size(hist) - 1] = 0;
	else cout << "pop: error, stack is empty" << endl;
}
void print(stack *hist) 
{
	if (!empty(hist))
	{
		change* save[N];
		int l = size(hist);
		for (int i = N - 1; i >= 0; i--)
		{
			if (i >= l) save[i] = 0;
			else
			{
				save[i] = top(hist);
				cout << "change #" << i << " text: " << save[i]->str << " row: " << save[i]->row << endl;
				pop(hist);
			}
		}
		for (int i = 0; i < N; i++) push(hist, save[i]);
	} 
	else cout << "print: error, stack is empty" << endl;
}
int main() 
{
	change a = { "change 1", rand() % 20 };
	change b = { "change 2", rand() % 20 };
	change c = { "change 3", rand() % 20 };
	change d = { "change 4", rand() % 20 };
	change e = { "change 5", rand() % 20 };
	change f = { "change 6", rand() % 20 };
	change g = { "change 7", rand() % 20 };

	//add 4
	stack hist = {&a, &b, &c, &d};
	//add 5
	push(&hist, &e);
	push(&hist, &f);
	push(&hist, &g);
	push(&hist, &a);
	push(&hist, &b);
	//undo
	pop(&hist);
	pop(&hist);
	//undo and add
	change* last = top(&hist);
	pop(&hist);
	last->str = "new text";
	push(&hist, last);
	//undo 6 times
	for (int i = 0; i < 6; i++) pop(&hist);
	//print
	print(&hist);
	cout << "len = " << size(&hist) << endl;

	return 1;
} 