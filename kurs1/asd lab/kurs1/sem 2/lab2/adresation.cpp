#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include "common.h"
using namespace std;
struct HashNode{bool deleted = true; bool deleted_for_search = true; long long key = 0; Data diplom;};
struct HashTable {
    int M = 8;
    int Size = 0;
    HashNode* bucketsArray = new HashNode[M];
    float loadFactor = 1;
    int hash(long long key){ return key % M;}//(((rand() % 100) * key + rand() % 100) % 9149658775000477) % M; }
    int size(){ return Size; }
    void erase(long long key) {
        int index, iter = 0;
        for(index = hash(key); iter < M && !bucketsArray[index].deleted_for_search; index = (index + 1) % M){
            if(bucketsArray[index].key == key && !bucketsArray[index].deleted){
                bucketsArray[index].deleted = true;
                Size --;
                break;
            }
            iter ++ ;
        }
    }
    void insert(long long key, Data value) {
        int index;
        if((float)Size / M >= loadFactor) {
            M *= 2;
            HashNode* newBucketsArray = new HashNode[M];
            for (size_t i = 0; i < M / 2; i++) {
                if(!bucketsArray[i].deleted){
                    for(index = hash(bucketsArray[i].key); !newBucketsArray[index].deleted; index = (index + 1) % M){}
                    newBucketsArray[index] = bucketsArray[i];
                }
            }
            delete [] bucketsArray;
            bucketsArray = newBucketsArray;
        }
        bool temp = false;
        for(index = hash(key); !bucketsArray[index].deleted; index = (index + 1) % M){
            temp = bucketsArray[index].key == key;
            if(temp) break;
        }
        bucketsArray[index] = {false, false, key, value};
        Size += temp ? 0 : 1;
    }
    Data* find(long long key) {   
        int index, iter = 0;
        for(index = hash(key); iter < M && !bucketsArray[index].deleted_for_search; index = (index + 1) % M){
            if(bucketsArray[index].key == key && !bucketsArray[index].deleted) return &bucketsArray[index].diplom;
            iter ++ ;
        }
        return NULL;
    }
}hashTable;
int main(int argc, char** argv){
    srand(time(0));
    testHashTable<HashTable>();
    return 0;
}