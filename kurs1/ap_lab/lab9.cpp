#include<iostream>
#include<cstring>
using namespace std;
const char* charset = "abcdefghijklmnopqrstuvwxyz";
int len_charset  = strlen(charset);
int nb_students = 10;
struct Points {
    int asd;
    int ap;
    int matan;
    char name[20];
    Points(){
        asd = rand() % 100, ap = rand() % 100, matan = rand() % 100;
        int l = rand() % 9 + 10;
        name[0] = toupper(charset[rand() % len_charset]);
        for (size_t i = 1; i < l; i++) name[i] = charset[rand() % len_charset];
        name[l] = '\0';
    }
};
struct MeanPoints{
    char* name;
    float mean_point;
};
int main(){
    Points* points = new Points[nb_students];
    for (size_t i = 0; i < nb_students; i++) points[i] = {};
    for (size_t i = 0; i < nb_students - 1; i++) {
        for (size_t j = 1; j < nb_students - i; j++) {
            if(strcmp(points[j - 1].name, points[j].name) == 1){
                Points temp = points[j - 1];
                points[j - 1] = points[j];
                points[j] = temp;
            }
        }
    }
    MeanPoints* mean_points = new MeanPoints[nb_students]; 
    for (size_t i = 0; i < nb_students; i++) mean_points[i] = {points[i].name, ((float)points[i].ap + (float)points[i].asd + (float)points[i].matan) / 3};
    for (size_t i = 0; i < nb_students; i++) cout << points[i].name << ' ' << points[i].matan << ' ' << points[i].asd << ' ' << points[i].ap << '|' << mean_points[i].name << ' ' << mean_points[i].mean_point << endl;
    getchar();
    return 1;
}   