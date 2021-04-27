#include<iostream>
#include<string>
#include<ctime>
#include<cmath>
#include<locale>
#include<stdio.h>
#include<conio.h>
#include "windows.h"
#define nb_strings 10
#define max_string_len 20
using namespace std;
struct firma{

};
struct
void create_file_and_write(char * filepath){
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
    fputc((char)(26), f);
    cout << endl;
    fclose(f);
} 
void func(char * filepath){
    FILE* f = fopen(filepath, "r+");
    char buff[nb_strings][max_string_len];
    char num[100];
    int max_counts[nb_strings];
    for(int n = 0; !feof(f); n++) {
        fgets(buff[n], 1000, f);
        int max_count = 0, count = 0, templen = strlen(buff[n]);
        for(int i = 0; i < templen; i++){
            if (buff[n][i] <= '9' && buff[n][i] >= '0') count ++;
            else{
                if (count > max_count) max_count = count;
                count = 0;
            }
        }
        max_counts[n] = max_count;
    }
    fseek(f, 0, SEEK_SET);
    for (size_t i = 0; i < nb_strings; i++) {
        itoa(max_counts[i], num, 10);
        fputs(num, f);
        fputs(buff[i], f);
    }
    fclose(f);    
}
int main() {
    //local
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char* filepath = "C:\\Users\\Latitude\\Desktop\\ap_lab\\lab14.dat";
    
    //створює файл в якому є випакові рядки випадуової довжини з циярами і з символами
    //create_file_and_write(filepath);
    //пише першими символами кожного рядка максимальну кількість цифер в рядку підряд
    //func(filepath);

    cout << "finished" << endl;
    cin.ignore(9999999);
    return 1;
}  