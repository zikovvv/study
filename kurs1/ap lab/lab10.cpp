#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
using namespace std;
const int N = 13;
double p(double x, double* a){
    double X = x;
    for (double* b = a + 1; b != a + N; b++, X *= x) a[0] += *b * X;
    return a[0];
}
int main(){
    srand(time(0));
    double s, t;
    cout << "type s: ";
    cin >> s;
    cout << endl << "type t: ";
    cin >> t;
    cout << endl;
    double a[N];
    for (size_t i = 0; i < N; i++){a[i] = (double)rand() / (double)rand(); cout << a[i] << ' ';}  
    cout << endl << p(1, a) - p(t, a) + pow(p(s - t, a), 2) - pow(p(1, a), 3) << endl;
    return 1;
}   