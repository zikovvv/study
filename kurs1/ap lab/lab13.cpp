/*
2. Створити текстовий файл, рядок якого містить цифри i символи.
В кожному рядку визначити найбільшу послідовність цифр, що йдуть поспіль.
Значення довжин цифрових послідовностей записати першими символами рядків вхідного файлу.
*/
#include<iostream>
#include<string>
#include<ctime>
#include<cmath>
#include<locale>
#include<conio.h>
#include "windows.h"
#define nb_strings 10
#define max_string_len 20
using namespace std;
void create_file_and_write(char * filepath){
    remove(filepath);
    FILE* f = fopen(filepath, "w+");
    char temp[max_string_len];
    for (size_t i = 0; i < nb_strings; i++) {
        int templen = max_string_len - rand() % 10;
        for (size_t n = 0; n < templen; n++) temp[n] = rand() % 2 == 0 ? rand() % 26 + 'a' : rand() % 10 + '0';
        temp[templen] = '\0';
        cout << temp << endl;
        fputs(temp, f);
        fputc('\n', f);
    }
    //fputc((char)(26), f);
    cout << endl;
    fclose(f);
} 
void func(char * filepath, char* filepath1){
    FILE* f = fopen(filepath, "r+");
    remove(filepath1);
    FILE* f1 = fopen(filepath1, "w+");

    char buff[100];
    char num[100];
    while(!feof(f)) {
        fgets(buff, 100, f);
        int max_count = 0, count = 0, templen = strlen(buff);
        if (templen > 0) {
            for(int i = 0; i < templen; i++){
                if (buff[i] <= '9' && buff[i] >= '0') count ++;
                else{
                    if (count > max_count) max_count = count;
                    count = 0;
                }
            }
            itoa(max_count, num, 10);
            fputs(num, f1);
            fputc('_', f1);
            fputs(buff, f1);
            buff[0] = '\0';
        }
    }
    fclose(f);  
    fclose(f1);
}
int main() {
    //локалізація
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //путь к файлу
    char* filepath = "C:\\Users\\Latitude\\Desktop\\ap_lab\\lab13.txt";
    char* filepath1 = "C:\\Users\\Latitude\\Desktop\\ap_lab\\lab13_1.txt";

    
    //створює файл в якому є випакові рядки випадуової довжини з циярами і з символами
    create_file_and_write(filepath);

    //пише першими символами кожного рядка максимальну кількість цифер в рядку підряд
    func(filepath, filepath1);

    cout << "finished" << endl;
    cin.ignore(9999999);
    return 1;
}  