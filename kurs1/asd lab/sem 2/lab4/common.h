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
        mean_points = rand() + rand();//(float)(rand() % 100) / (rand() % 100);
        will = rand() % 10;
        cheated = rand() + rand();
    }
};
bool operator<(const Data & e1, const Data & e2){ return e1.mean_points + e1.cheated < e2.mean_points + e2.cheated; }
bool operator>(const Data & e1, const Data & e2){ return e1.mean_points + e1.cheated > e2.mean_points + e2.cheated; }
bool operator>=(const Data & e1, const Data & e2){ return e1.mean_points + e1.cheated >= e2.mean_points + e2.cheated; }
bool operator<=(const Data & e1, const Data & e2){ return e1.mean_points + e1.cheated <= e2.mean_points + e2.cheated; }
bool operator==(const Data & e1, const Data & e2){ return e1.mean_points + e1.cheated == e2.mean_points + e2.cheated; }
bool operator!=(const Data & e1, const Data & e2){ return e1.mean_points + e1.cheated != e2.mean_points + e2.cheated; }
ostream& operator<<(ostream & os, Data & e){
    os << e.name << ' ' << e.mean_points << ' ' << e.will << ' ' << e.cheated;
    return os;
}
template<typename T> struct BinaryNode{
    T data;
    BinaryNode<T>* left = NULL;
    BinaryNode<T>* right = NULL;
    BinaryNode<T>* parent = NULL;
    BinaryNode(T val, BinaryNode<T>* ptr) {
        data = val;
        parent = ptr;
    }
    BinaryNode(BinaryNode<T>* ptr) {
        data = ptr->data;
        left = ptr->left;
        right = ptr->right;
        parent = ptr->parent;
    }
};
template<typename T> struct AVLNode{
    T data;
    int height = 1;
    AVLNode<T>* left = NULL;
    AVLNode<T>* right = NULL;
    AVLNode<T>* parent = NULL;
    AVLNode(T val, AVLNode<T>* ptr) {
        data = val;
        parent = ptr;
    }
    AVLNode(AVLNode<T>* ptr) {
        data = ptr->data;
        height = ptr->height;
        left = ptr->left;
        right = ptr->right;
        parent = ptr->parent;
    }
};