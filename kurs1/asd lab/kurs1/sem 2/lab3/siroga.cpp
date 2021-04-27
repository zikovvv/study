#include <iostream>
#include <ctime>
#include <queue>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
using namespace std;

struct homework
{
    int subjectInterest;
    int utilityLevel;
    int difficultness;
    int deadline;
    homework()
    {
        deadline = rand() % 100 + 1;
    }
    bool operator<(const homework& aHomework)const
    {
        return deadline <= aHomework.deadline;
    }
    bool operator==(const homework& aHomework)
    {
        return deadline == aHomework.deadline;
    }
};

/*struct binaryHeap
{
    homework *arr = new homework[1];
    int getParent(int i)
    {
        return (i - 1)/2;
    }
    int getLeftChild(int i)
    {
        return 2*i +1;
    }
    int getRightChild(int i)
    {
        return 2*i +2;
    }
    void siftUp(int i)
    {
        for(i;;)
        {
            if(arr[getParent(i)]<arr[i])
            {
                swap(arr[i], arr[getParent(i)]);
                i = getParent(i);
            }
            else
            {
                break;
            }
        }
    }

    void siftDown(int i)
    {
        for(i;;)
        {
            int maxdl = max(arr[getLeftChild(i)].deadline,arr[getRightChild(i)].deadline);
            if(maxdl == arr[getLeftChild(i)].deadline)
            {
                if(arr[i]<arr[getLeftChild(i)])
                {
                    swap(arr[i], arr[getLeftChild(i)]);
                    i = getLeftChild(i);
                }
            }
            else if(maxdl == arr[getRightChild(i)].deadline)
            {
                if(arr[i]<arr[getRightChild(i)])
                {
                    swap(arr[i], arr[getRightChild(i)]);
                    i = getRightChild(i);
                }
            }
            else
            {
                break;
            }
        }
    }
    ~binaryHeap()
    {
        delete[] arr;
    }
};*/

struct priorityQueue
{
    int capacity = 1;
    int realSize = 0;
    int alpha = 2;
    homework* arr = new homework[capacity];
    /*
    int getParent(int i)
    {
        return (i - 1) / 2;
    }
    */
    int getParent(int index){ return index == 0 ? 0 : index % 2 == 0 ? (index - 2) / 2 : (index - 1) / 2; }
    int getLeftChild(int i)
    {
        return 2 * i + 1;
    }
    int getRightChild(int i)
    {
        return 2 * i + 2;
    }
    /*
    void siftUp(int i)
    {
        for (i;; i = getParent(i))
        {
            if (i > 1 && arr[getParent(i)] < arr[i])
            {
                swap(arr[i], arr[getParent(i)]);
            }
            else
            {
                break;
            }
        }
    }
    */
    
    /*
    void siftDown(int i)
    {
        for (i;;)
        {
            if (2 * i + 1 <= realSize)
            {
                if (2 * i + 2 <= realSize)
                {
                    if (max(arr[getLeftChild(i)].deadline, arr[getRightChild(i)].deadline) == arr[getLeftChild(i)].deadline)
                    {
                        if (arr[i] < arr[getLeftChild(i)])
                        {
                            swap(arr[i], arr[getLeftChild(i)]);
                            i = getLeftChild(i);
                        }
                    }
                    else if (max(arr[getLeftChild(i)].deadline, arr[getRightChild(i)].deadline) == arr[getRightChild(i)].deadline)
                    {
                        if (arr[i] < arr[getRightChild(i)])
                        {
                            swap(arr[i], arr[getRightChild(i)]);
                            i = getRightChild(i);
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else if (arr[i] < arr[getLeftChild(i)])
                {
                    swap(arr[i], arr[getLeftChild(i)]);
                    i = getLeftChild(i);
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }*/
    void siftUp(int index){
        for (int parent = getParent(index); arr[parent] < arr[index] && index > 0; index = parent, parent = getParent(index))      
            swap(arr[parent], arr[index]);
    }
    void siftDown(int parent){
        int temp, left = getLeftChild(parent), right = getRightChild(parent);
        while(left < realSize){
            temp = 0;
            if(arr[parent] < arr[left]) temp = left;
            if (right < realSize) {
                if(arr[left] < arr[right]) temp = right;
            } 

            if(temp != 0){
                swap(arr[temp], arr[parent]);
                parent = temp;
            } 
            else break;
            left = getLeftChild(parent), right = getRightChild(parent);
        }
    }
    //binaryHeap bHeap;
    homework top()
    {
        return arr[0];
    }
    int size()
    {
        return realSize;
    }

    bool empty()
    {
        return !(size());
    }
    void push(homework aHomework)
    {
        if (realSize + 1 == capacity)
        {
            capacity *= alpha;
            homework* newArray = new homework[capacity];
            memcpy(newArray, arr, realSize * (sizeof(homework)));
            delete[] arr;
            arr = newArray;
        }
        arr[realSize] = aHomework;
        if (!empty())
        {
            siftUp(realSize);
        }
        realSize++;
    }

    void pop()
    {
        if (!empty())
        {
            swap(arr[0], arr[realSize - 1]);
            //delete bHeap.arr[realSize];
            realSize--;
            siftDown(0);
        }
    }
};
template <typename T>
float testPriorityQueueSpeed(T&& priorityQueue)
{
    const int iters = 100000;
    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(homework());
        }
        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
    return time;
}
bool testPriorityQueue()
{
    srand(time(NULL));
    const int iters = 20000;
    priorityQueue myPriorQueue;
    priority_queue<homework> stlPriorQueue;
    bool isDataEqual = true;

    cout << "started comparing"<< endl;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            homework randData = homework();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }
        if (!(myPriorQueue.top() == stlPriorQueue.top()))
        {
            cout << myPriorQueue.top().deadline << ' ' << stlPriorQueue.top().deadline << " iter : " << i << endl;
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl << endl;
            cin.ignore(9999999999);
            break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }
    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();
    float stlTime =
        testPriorityQueueSpeed<priority_queue<homework>>(priority_queue<homework>());
    float myTime = testPriorityQueueSpeed<priorityQueue>(priorityQueue());
    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl << endl;
    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl << endl;
        return true;
    }
    cerr << ":(" << endl << endl;
    return false;
}

int main()
{
    srand(time(NULL));
    testPriorityQueue();
    cin.ignore(99999);
    return 0;
}