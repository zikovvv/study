#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include "windows.h"
#include <locale.h>
#include <vector>
using namespace std;
struct Worker{
    char name[20];
    char position[20];
    int salary;
};
struct Position{
    char name[20];
    int nb_vacancy;
    int requirements;    
    int salary;
};
struct Firm{
    char name[20];
    Position positions[10];
    int nb_positions = 0;
    Worker workers[10];
    int nb_workers = 0;
};

int input(){
    int a;
    cin >> a;
    return a;
}

void input(string& a){
    cin >> a;
}


int main() {
    FILE* fp = fopen("file.dat", "r+b");
    vector<Firm> list;
    while(1){
        int action;
        cout << "choose action : " << endl;
        cout << "0 - finish program" << endl;
        cout << "1 - add firm" << endl;
        cout << "2 - delete firm" << endl;
        cout << "3 - change firm" << endl;
        cout << "4 - print all firms" << endl;
        cin >> action;
        cout << action << endl;
        switch (action) {
        case 0 :
            cout << "exit" << endl;
            exit(0);
            break;        
        case 1 :
            break;
        case 2 :

            break;
        case 3 :
            int action1;
            while(1){
                cout << "choose firm : " << endl;
                cin >> action1;
                break;
            }
            break;
        default:
            cerr << "Unknown action was chosen" << endl;
            break;
        }
    }
    return 0;
}