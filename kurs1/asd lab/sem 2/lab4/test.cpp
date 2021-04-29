#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;



struct dota
{
    int a = 0;
    dota(){a = rand() % 123;}    /* data */
};
ostream& operator<<(ostream os, dota& d){
    os  << d.a << endl;
    return os;
}
template<typename T> class testClass{
    public : 
        void f(T asd){
            cout << asd << endl;
        }
    private :
        int function_to_call_from_lambda(int arg){
            //cout << "im passed function and i got arg" << arg << endl;
            return arg;
        }   
};



int main()
{
    typedef testClass<int> intclass;
    typedef testClass<dota> dotaclass;

    testClass<float> test_class;

    int a = 1;
    float b = 0.1;
    test_class.f(a);
    intclass intcc;
    intcc.f(a);
    dotaclass dotacc;
    dotacc.f(dota());

    cout << "finished" << endl;
    getchar();
    return 1;
}