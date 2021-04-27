#include <iostream>
#include <string>
#define N 8
using namespace std;

struct worker
{
    string position;
    int experience;
    int salary;
};
struct queue
{
    worker* list[N];
};
int size(queue* workers)
{
    for (int i = 0; i < N; i++)
    {
        if (!workers->list[i]) return i;
    }
    return N;
}
void push(queue* workers, worker* a)
{
    int l = size(workers);
    if (l < N)
    {
        for (int i = N - 1; i > 0; i--)
        {
            workers->list[i] = workers->list[i - 1];
        }
        workers->list[0] = a;
    }
    else cout << "push : error, queue is full" << endl;
}
bool empty(queue* workers) { return size(workers) == 0; }
worker* front(queue* workers)
{
    if (!empty(workers)) return workers->list[size(workers) - 1];
    cout << "front: error, queue is empty" << endl;
    return 0;
}
void pop(queue* workers)
{
    if (!empty(workers)) workers->list[size(workers) - 1] = 0;
    else cout << "pop: error, queue is empty" << endl;
}
void print(queue* workers)
{
    if (!empty(workers))
    {
        worker* save[N];
        int l = size(workers);
        for (int i = N - 1; i >= 0; i--)
        {
            if (i < l)
            {
                save[i] = front(workers);
                cout << "worker #" << l - i << ", position: " << save[i]->position << ", experience: " << save[i]->experience << ", salary: " << save[i]->salary << endl;
                pop(workers);
            }
        }
        for (int i = l - 1; i >= 0; i--)
        {
            push(workers, save[i]);
        }
    }
    else cout << "print: error, queue is empty" << endl;
}
int main()
{
    worker a = { "worker 1", rand() % 20, rand() % 20 + 100 };
    worker b = { "worker 2", rand() % 20, rand() % 20 + 100 };
    worker c = { "worker 3", rand() % 20, rand() % 20 + 100 };
    worker d = { "worker 4", rand() % 20, rand() % 20 + 100 };
    worker e = { "worker 5", rand() % 20, rand() % 20 + 100 };
    worker f = { "worker 6", rand() % 20, rand() % 20 + 100 };
    worker g = { "worker 7", rand() % 20, rand() % 20 + 100 };
    //5 workers
    queue workers = {};
    push(&workers, &a);
    push(&workers, &b);
    push(&workers, &c);
    push(&workers, &d);
    push(&workers, &e);


    //get increase 200 and add
    worker* temp = front(&workers);
    cout << a.salary << endl;
    cout << temp->salary << endl;
    pop(&workers);
    temp->salary += 200;
    push(&workers, temp);
    //4 more
    push(&workers, &g);
    push(&workers, &f);
    push(&workers, &e);
    push(&workers, &d);
    //dequeue 3 
    for (int i = 0; i < 3; i++) pop(&workers);
    //dequeue 7 more
    for (int i = 0; i < 7; i++) pop(&workers);
    //print
    print(&workers);
    cout << "len =" << size(&workers) << endl;
    return 1;
}