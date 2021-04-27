/*
Варіант 2
Маємо рядок, що містить букви і цифри. Перетворіть цей рядок так, щоб спочатку в ньому йшли всі цифри,
а потім -усі букви вихідного рядка.
Можливі символи - цифри; прописні і рядкові латинські букви.
Приклади:
Вихідний рядок: Результат:
ad2e57b6 2576adeb
Tom&Jerry Неприпустимий символ - '&'
*/
#include<iostream>
#include<cstring>
#include<locale>
#include "windows.h"
using namespace std;
void if_forbidden_chars(char* str){
    const char* lat = "abcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < strlen(str); i++) {
        if(strchr(lat, tolower(str[i])) == NULL && !(str[i] >= '0' && str[i] <= '9')){
            cout << "неприпустимий символ : " << str[i] << endl;
            exit(1);
        }
    }
}
int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char str[300];
    //ввід
    cout << "Type in string : ";
    cin.getline(str, 300, '\n');
    //провірка на заборонені символи
    if_forbidden_chars(str);

    int len = strlen(str);
    char* new_str = new char[len + 1];
    new_str[len] = '\0';
    int cindex = 0;
    //цифри
    for (size_t i = 0; i < len; i++){
        if ('0' <= str[i] && str[i] <= '9'){ 
            new_str[cindex] = str[i];
            cindex++;
        }
    }
    //символи
    for (size_t i = 0; i < len; i++){
        if ('0' > str[i] || str[i] > '9'){ 
            new_str[cindex] = str[i];
            cindex++;
        }
    }
    cout << new_str << endl;
    cin.get();
    //cin.ignore(9999999);
    return 1;
}