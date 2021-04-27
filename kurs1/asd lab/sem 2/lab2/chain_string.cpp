#include <iostream>
#include <ctime>
#include <cmath>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <Windows.h>
#include "common.h"
using namespace std;
struct HashNode{ string key; Data diplom; };
struct Node { HashNode data; Node* next = NULL; Node* prev = NULL; };
struct LinkedList {
    Node* head = NULL;
    int size = 0;
    bool insert(HashNode new_elem) {
        Node* node = get_by_key(&new_elem.key);
        if (node == NULL) {
            head = new Node{new_elem, head, NULL};
            if (size > 0) head->next->prev = head;
            size++;   
            return true;
        }
        else *node = {new_elem, node->next, node->prev};
        return false;
    }
    bool pop(string *key) {
        bool deleted = false;
        if(size > 0) {
            for (Node* node = head; node != NULL; node = node->next) {
                if(node->data.key.compare(*key) == 0){
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
    Node* get_by_key(string *key) {
        for(Node* node = head; node != NULL; node = node->next){
            if(node->data.key.compare(*key) == 0) return node;
        }
        return NULL;
    }
};
struct HashTable {
    int M = 8;
    int Size = 0;
    float loadFactor = 0.75;
    LinkedList* bucketsArray = new LinkedList[M];
    int hash(string *key) {
        unsigned int res = 37;
        for(int i = 0; i < key->length(); i++) res = 54059 * res ^ ((int)(*key)[i] * 76963);
        return res % M;
    }
    int size(){ return Size; }
    void erase(string *key) { Size -= bucketsArray[hash(key)].pop(key) ? 1 : 0; }
    void insert(string *key, Data value) {
        if((float)(Size + 1) / M >= loadFactor) {
            M *= 2;
            LinkedList* newBucketsArray = new LinkedList[M];
            for (size_t i = 0; i < M / 2; i++) {
                for (Node* node = bucketsArray[i].head; node != NULL; node = node->next)
                    newBucketsArray[hash(&node->data.key)].insert(node->data);
            }
            delete [] bucketsArray;
            bucketsArray = newBucketsArray;
        } 
        Size += bucketsArray[hash(key)].insert(HashNode{*key, value}) ? 1 : 0;
    }
    Data* find(string *key) {   
        Node* linkedListNode = bucketsArray[hash(key)].get_by_key(key);
        if (linkedListNode != NULL) return &linkedListNode->data.diplom;
        return NULL;
    }
}hashTable;
int main(int argc, char** argv){
    srand(time(0));
    testHashTable_s<HashTable>();
    return 0;
}