#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;
template <typename T> class a{
    public : 
        int val1 = 1;
        a(){}
        a(int b){val1 = b;}
        void shit(){shit(123);}
        void print_pub(){cout << val1 << ' ' << val2 << endl;}
        int return_pub(){return val1;}
    private : 
        int val2 = 2;
        void print_priv(){cout << val1 << ' ' << val2 << endl;}
        void shit(int asd){cout << asd << endl; }
        int return_pub(int b){return this->val1;}

};
template <typename T> class b : public a<T>{
    public : 
        void increase(){
            increase_();
        }
    private :
        void increase_(){
            val1 ++;
            val1 ++;
            val1 ++;
            val1 ++;
        } 
};
/*
class a{
    public : 
        int val1 = 1;
        a(){}
        a(int b){val1 = b;}
        void shit(){shit(123);}
        void print_pub(){cout << val1 << ' ' << val2 << endl;}
        int return_pub(){return val1;}
    private : 
        int val2 = 2;
        void print_priv(){cout << val1 << ' ' << val2 << endl;}
        void shit(int asd){cout << asd << endl; }
        int return_pub(int b){return this->val1;}

}A;
class b : public a{
    public : 
        void increase(){
            increase_();
        }
    private :
        void increase_(){
            val1 ++;
            val1 ++;
            val1 ++;
            val1 ++;
        } 
}B;
*/
int main(){
    a<int> A;
    b<int> B;

    A.print_pub();
    B.print_pub();
    B.increase();
    cout << endl;
    A.print_pub();
    B.print_pub();
    cout << B.return_pub();


    getchar();
    return 0;
}