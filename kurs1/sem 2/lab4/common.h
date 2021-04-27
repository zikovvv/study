#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;
long long generateRandLong(int len = 12) {
    long long num = (rand() % 9 + 1) * pow(10, len - 1);
    for (long long rank = pow(10, len - 2); rank != 0; rank /= 10) num += rand() % 10 * rank;
    return num;
}

struct Data{
    char * name;
    int mean_points;
    int will;
    int cheated;
    Data(){
        int namelen = rand() % 5 + 5;
        name = new char[namelen + 1];
        for (size_t i = 0; i < namelen; i++) name[i] = rand() % 26 + 'a';
        name[namelen] = '\0';
        mean_points = rand() % 100000;//(float)(rand() % 100) / (rand() % 100);
        will = rand() % 10;
        cheated = rand() % 10;
    }
};
bool operator<(const Data & e1, const Data & e2){ return e1.mean_points < e2.mean_points; }
bool operator>(const Data & e1, const Data & e2){ return e1.mean_points > e2.mean_points; }
bool operator>=(const Data & e1, const Data & e2){ return e1.mean_points >= e2.mean_points; }
bool operator<=(const Data & e1, const Data & e2){ return e1.mean_points <= e2.mean_points; }
bool operator==(const Data & e1, const Data & e2){ return e1.mean_points == e2.mean_points; }
Data operator+=(Data e1, Data e2){
    e1.mean_points += e2.mean_points;
    e1.will += e2.will;
    e1.cheated += e2.cheated;
    char* new_name = new char[strlen(e1.name) + strlen(e2.name)];
    strcat(new_name, e1.name);
    strcat(new_name, e2.name);
    delete [] e1.name;
    e1.name = new_name;
    return e1;
    //return Data(e1.name, e2.name, e1.mean_points + e2.mean_points, e1.will + e1.will, e1.cheated + e1.cheated);
}
ostream& operator<<(ostream & os, Data & e){
    os << e.name << ' ' << e.mean_points << ' ' << e.will << ' ' << e.cheated << endl;
    return os;
}
template<typename T> struct Node{
    T data;
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    Node<T>* parent = NULL;
    Node(T val, Node<T>* ptr) {
        data = val;
        parent = ptr;
    }
    
};
