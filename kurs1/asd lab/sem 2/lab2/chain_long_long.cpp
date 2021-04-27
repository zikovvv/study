#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include "common.h"
using namespace std;
struct HashNode{ long long key; Data diplom; };
struct Node { HashNode data; Node* next = NULL; Node* prev = NULL; };
struct LinkedList {
    Node* head = NULL;
    int size = 0;
    bool insert(HashNode new_elem) {
        Node* node = get_by_key(new_elem.key);
        if (node == NULL) {
            head = new Node{new_elem, head, NULL};
            if (size > 0) head->next->prev = head;
            size++;   
            return true;
        }
        else *node = {new_elem, node->next, node->prev};
        return false;
    }
    bool pop(long long key) {
        bool deleted = false;
        if(size > 0) {
            for (Node* node = head; node != NULL;node = node->next) {
                if(node->data.key == key){
                    if(node->prev != NULL) node->prev->next = node->next;
                    else head = node->next;
                    if(node->next != NULL) node->next->prev = node->prev;
                    delete node;
                    deleted = true;
                    break;
                }
            }
            if (deleted){
                size--;
                if(size == 0) head = NULL;
            }
        }
        return deleted;
    }
    Node* get_by_key(long long key) {
        for(Node* node = head; node != NULL; node = node->next){
            if(node->data.key == key) return node;
        }
        return NULL;
    }
};
struct HashTable {
    int M = 8;
    int Size = 0;
    float loadFactor = 8.5;
    LinkedList* bucketsArray = new LinkedList[M];
    int hash(long long key){ return key % M;}//(((rand() % 100) * key + rand() % 100) % 9149658775000477) % M; }
    int size(){ return Size; }
    void erase(long long key) { Size -= bucketsArray[hash(key)].pop(key) ? 1 : 0; }
    void insert(long long key, Data value) {
        if((float)(Size + 1) / M >= loadFactor) {
            M *= 2;
            LinkedList* newBucketsArray = new LinkedList[M];
            for (size_t i = 0; i < M / 2; i++) {
                for (Node* node = bucketsArray[i].head; node != NULL; node = node->next)
                    newBucketsArray[hash(node->data.key)].insert(node->data);
            }
            delete [] bucketsArray;
            bucketsArray = newBucketsArray;
        } 
        Size += bucketsArray[hash(key)].insert(HashNode{key, value}) ? 1 : 0;
    }
    Data* find(long long key) {   
        Node* linkedListNode = bucketsArray[hash(key)].get_by_key(key);
        if (linkedListNode != NULL) return &linkedListNode->data.diplom;
        return NULL;
    }
}hashTable;

int main(int argc, char** argv){
    srand(time(0));
    testHashTable<HashTable>();
    return 0;
}