#include<iostream>
#include<cmath>
using namespace std;
#define AND(x, y) (x) && (y)
#define OR(x, y) (x) || (y)
#define NOT(x) !x
#define XOR(x, y) AND(OR(x, y), NOT(AND(x, y))
#define ABS(x) ((x) >= 0 ? x : -(x))
#define POW(x, n) pow(x, n)
#define SQRT(x) sqrt(x)
#define IN(var) cin >> var
#define PRINT(x) cout << (x)
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define a 1
int main(){
    int x, y, z;  
    PRINT("enter x : ");
    IN(x);
    PRINT("enter y : ");
    IN(y);
    PRINT("enter z : ");
    IN(z);
    #if OR(a < 1, a >= 10)
        PRINT(MIN(POW(x, 2), 5 * ABS(y - z)));
    #else
        PRINT(POW(MAX(x - y, x + z), 2));
    #endif
    cin.ignore(123123);
    return 0;
} 
 