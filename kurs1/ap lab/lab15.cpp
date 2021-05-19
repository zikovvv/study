#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
int main()
{
    srand(time(0));
    int N = 5;
    float* arr = new float[N];
    for (size_t i = 0; i < N; i++) {
        cin >> arr[i];
    }

    string fname("numbers.dat");
    
    fstream out(fname, ios::out | ios::binary);
    out.write((char*)arr, sizeof(float) * N);
    out.close();

    fstream in(fname, ios::in | ios::binary);
    float* arr1 = new float[2];
    in.read((char*)arr1, sizeof(float));
    in.seekg(-sizeof(float), ios::end);
    in.read((char*) &(arr1[1]), sizeof(float));
    in.close();

    cout << arr1[0] - arr1[1] << endl;
    cin.ignore(1111);
    return 0;
}