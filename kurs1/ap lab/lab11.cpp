#include<iostream>
#include<cstring>
#include<ctime>
#include<cmath>
#include<locale>
#include "windows.h"
using namespace std;
int main() {
    const char* ukr_small = "йцукенгшщзхїфівапролджєячсмитьбю";
    const char* ukr_big = "ЙЦУКЕНГШЩЗХЇФІВАПРОЛДЖЄЯЧСМИТЬБЮ";
    const char* lat_small = "abcdefghijklmnopqrstuvwxyz";
    const char* lat_big = "QWERTYUIOPASDFGHJKLZXCVBNM";
    const char* num = "1234567890";
    srand(time(0));
    //setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char str[300];
    cout << lat_small << endl;
    for (size_t i = 0; i < strlen(ukr_small); i++) cout << ukr_small[i] << "іфдларфодліаджлофід" << endl;    
    cin.getline(str, 300, '\n');
    cout << str << endl;
    int nb_ukr_small = 0, nb_ukr_big = 0, nb_lat_small = 0, nb_lat_big = 0, nb_num = 0, nb_other = 0;
    for (size_t i = 0; i < strlen(str); i++) {
        char c = str[i];
        cout << (int)c << ' ' << 'х' << endl;
        if(c == 'х') cout << "{QW{E{QWE{!{{!!!!!!!!" << endl;
        if(strchr(ukr_small, c)) nb_ukr_small++;
        else if(strchr(ukr_big, c)) nb_ukr_big++;
        else if(strchr(lat_small, c)) nb_lat_small++;
        else if(strchr(lat_big, c)) nb_lat_big++;
        else if(strchr(num, c)) nb_num++;
        else nb_other++;
    }
    printf("ukr small : %d, ukr big : %d, lat small : %d, lat big : %d, num : %d, other : %d", nb_ukr_small, nb_ukr_big, nb_lat_small, nb_lat_big, nb_num, nb_other);
    cin.ignore(9999999);
    return 1;
}  