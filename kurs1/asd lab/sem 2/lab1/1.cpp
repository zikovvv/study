#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;

struct Hostel
{
    int number;
    int space;
    bool heating;
};

struct DynamicArray
{
    int capacity = 5;
    const int koef = 2;
    Hostel* arr = new Hostel[capacity];
    int size = 0;

    void push_back(Hostel new_elem)
    {   
        if (size == capacity)
        {
            capacity *= koef;
            Hostel* temp_arr = new Hostel[capacity];
            for (size_t i = 0; i <= size; i++) temp_arr[i] = arr[i];
            delete[] arr;
            arr = temp_arr;
        }
        arr[size] = new_elem;
        size ++;
    }
    Hostel pop_back()
    {
        size--;
        Hostel temp = arr[size];
        return temp; 
    }
    Hostel get(int n)
    {
        if(n >= 0 && n < size) return arr[n];
        else
        {
            printf("no element with index %d\n", n);
            exit(1);
        }
    }
    int get_size(){return size;}
    void print()
    {
        if(size > 0)
        {
            for (int i = 0; i < size; i++) printf("№: %d, space: %d, heating: %d\n", arr[i].number, arr[i].space, arr[i].heating);
        }
        else cout << "no elements to print" << endl;
    }
    void push_front(Hostel new_elem)
    {
        if (size == capacity)
        {
            capacity *= koef;
            Hostel* temp_arr = new Hostel[capacity];
            for (int i = 0; i <= size; i++) temp_arr[i + 1] = arr[i];
            delete[] arr;
            arr = temp_arr;
        }
        else
        {
            for (int i = size - 1; i >= 0; i = i - 1) arr[i + 1] = arr[i];
        }
        arr[0] = new_elem;
        size++;
    }
    Hostel pop_front()
    {
        size--;
        Hostel temp = arr[0];
        for (int i = 0; i < size; i++) arr[i] = arr[i + 1];
        return temp;
    }
    void clean()
    {
        delete [] arr;
    }
};

struct Node
{
    Node* next;
    Hostel hostel;
};

struct LinkedList
{
    Node* tail = NULL;
    Node* head = NULL;
    void push_back(Hostel new_elem)
    {
        Node* node = new Node{new_elem, NULL};//(Node*)malloc(sizeof(Node));
        if (head != NULL)
        {
            tail->next = node;
            tail = node;
        }
        else
        {
            head = node;
            tail = node;
        }
    }
    void push_front(Hostel new_elem)
    {
        Node* node = (Node*)malloc(sizeof(Node));
        node->hostel = new_elem;
        node->next = NULL;
        if (head != NULL)
        {
            node->next = head;
            head = node;
        }
        else
        {
            head = node;
            tail = node;
        }
    }
    int size()
    {
        if(head == NULL) return 0;
        else
        {
            int counter = 1;
            Node* node = head;
            while(node->next != NULL)
            {   
                node = node->next;
                counter++;
            }
            return counter;
        }
    }
    void print()
    {
        if(head == NULL) cout << "no elements to print" << endl;
        else
        {
            Node* node = head;
            while(1)
            {
                printf("№: %d, space: %d, heating: %d\n", node->hostel.number, node->hostel.space, node->hostel.heating);
                if(node->next != NULL) node = node->next;
                else break;
            }
        }
    }
    Hostel pop_front()
    {
        if(head == NULL)
        {
            cout << "no elements to pop front" << endl;
            exit(1);
        }
        else if(head == tail)
        {
            Hostel hostel = head->hostel;
            delete head;
            head = NULL;
            tail = NULL;
            return hostel;
        }
        else
        {
            Hostel hostel = head->hostel;
            head = head->next;
            return hostel;
        }
    }
    Hostel pop_back()
    {
        Hostel hostel;
        if(head == NULL)
        {
            cout << "no elements to pop back" << endl;
            exit(1);
        }
        else if(head == tail)
        {
            hostel = head->hostel;
            head = NULL;
            tail = NULL;
            return hostel;
        }
        else
        {
            Node* node = head;
            hostel = tail->hostel;
            while(1)
            {
                if(node->next == tail)
                {
                    node->next = NULL;
                    tail = node;
                    return hostel;
                }
                else node = node->next;
            }
        }
    }
    Hostel get(int n)
    {
        if(head == NULL)
        {
            cout << "no elements in array" << endl;
            exit(1);
        }
        else
        {
            Node* node = head;
            for(int i = 0;i < n;i++)
            {
                if(node->next != NULL) node = node->next;
                else
                {
                    printf("No element with index %d in array\n", n);
                    exit(1);
                }
            }
            Hostel hostel = node->hostel;
            return hostel;
        }
    }
    void clean()
    {
        if (head != NULL)
        {
            Node* node = head;
            Node* ptr;
            while(1)
            {
                ptr = node;
                if(node->next != NULL)
                {
                    node = node->next;
                    delete ptr;
                }
                else break;
            }
        }
    }
};

int main()
{
    srand(time(0));
    LinkedList linked;
    DynamicArray dynamic;
    
    Hostel h;
    double start;
    
    double d_start = clock();
    double times_dynamic[6] = {0};
    start = clock();
    for (int i = 0; i < 50000; i++)
    {
        h = {i, 2, true};
        dynamic.push_back(h);
    }
    cout << "push back " << (clock() - start) / CLOCKS_PER_SEC << endl;    
    times_dynamic[0] = clock() - start;

    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        h = {i, 2, true};
        dynamic.push_front(h);
    }
    cout << "push front " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_dynamic[1] = clock() - start;
    
    start = clock();
    for (int i = 0; i < 20000; i++)
    {
        dynamic.get(rand() % 60000);
    }
    cout << "get " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_dynamic[2] = clock() - start;
    
    start = clock();
    for (int i = 0; i < 5000; i++)
    {
        dynamic.pop_front();
    }
    cout << "pop front " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_dynamic[3] = clock() - start;
    
    start = clock();
    for (int i = 0; i < 5000; i++)
    {
        dynamic.pop_back();
    }
    cout << "pop back " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_dynamic[4] = clock() - start;

    cout << "dynamic all time " << (clock() - d_start) / CLOCKS_PER_SEC << endl << endl;
    d_start = clock() - d_start;
    dynamic.clean();
    


    double l_start = clock();
    double times_linked[6];
    
    start = clock();
    for (int i = 0; i < 50000; i++)
    {
        h = {i, 2, true};
        linked.push_back(h);
    }
    cout << "push back " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_linked[0] = clock() - start;
    
    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        h = {i, 2, true};
        linked.push_front(h);
    }
    cout << "push front " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_linked[1] = clock() - start;
    
    start = clock();
    for (int i = 0; i < 20000; i++)
    {
        linked.get(rand() % 60000);
    }
    cout << "get " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_linked[2] = clock() - start;

    start = clock();
    for (int i = 0; i < 5000; i++)
    {
        linked.pop_front();
    }
    cout << "pop front " << (clock() - start) / CLOCKS_PER_SEC << endl;    
    times_linked[3] = clock() - start;

    start = clock();
    for (int i = 0; i < 5000; i++)
    {
        linked.pop_back();
    }
    cout << "pop back " << (clock() - start) / CLOCKS_PER_SEC << endl;
    times_linked[4] = clock() - start;

    cout << "linked all time " << (clock() - l_start) / CLOCKS_PER_SEC << endl << endl;
    l_start = clock() - l_start;
    linked.clean();    


    return 1;

    
    

    
    /*
    Hostel a{1, 1, false};
    Hostel b{2, 2, false};
    Hostel c{3, 3, false};
    linked.print();
    cout << linked.size() << ' ' << linked.head << ' ' << linked.tail << endl;
    linked.push_front(a);
    linked.push_front(b);
    cout << linked.get(1).number << endl;
    //cout << linked.pop_back().number << endl;
    linked.print();
    cout << linked.size() << ' ' << linked.head << ' ' << linked.tail << endl;
    linked.push_front(b);
    linked.print();
    cout << linked.size() << ' ' << linked.head << ' ' << linked.tail << endl;
    linked.push_back(c);
    linked.push_back(a);
    cout << linked.get(0).number << endl;
    linked.print();
    cout << linked.pop_back().number << endl;
    cout << linked.size() << endl;
    cout << linked.pop_back().number << endl;
    cout << linked.size() << endl;
    cout << linked.pop_back().number << endl;
    cout << linked.size() << endl;
    cout << linked.pop_back().number << endl;
    cout << linked.size() << endl;
    cout << linked.pop_back().number << endl;
    cout << linked.size() << endl;

    linked.print();
    cout << linked.size() << linked.head << ' ' << linked.tail << endl;
    */    

    /*
    Hostel a{1, 1, false};
    Hostel b{2, 2, false};
    Hostel c{3, 3, false};
    
    cout << aaa.get_size() << endl;
    aaa.print();
    //cout << aaa.get(0).number << endl;
    aaa.push_front(a);
    aaa.print();
    
    cout << endl;
    aaa.push_front(b);
    aaa.push_front(c);
    aaa.push_back(c);
    aaa.print();
    
    cout << endl;
    aaa.pop_front();
    aaa.pop_back();
    aaa.pop_back();
    aaa.pop_front();
    aaa.print();

    cout << endl;
    cout << aaa.capacity << endl;
    for (size_t i = 0; i < 11; i++)
    {
        //cout << i << " " << aaa.capacity << " " << aaa.size << endl;
        switch (i % 3)
        {
            case 1 : 
                aaa.push_front(b);
                break;
            case 2 : 
                aaa.push_front(c);
                break;
            case 0 :
                aaa.push_front(a);
                break;
        }
    }
    aaa.print();
    cout << aaa.capacity << endl;
    */
    
    return 0;
}