#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>
#include "common.h"
using namespace std;
template<typename T> class BinarySearchTree{
    public :
        typedef BinaryNode<T> Node;
        Node* root = NULL;
        int Size = 0;
        BinarySearchTree(){}
        BinarySearchTree(Node* node){
            root = node;
            Size = size(root);
        }
        void insert(T new_val){
            Size ++;
            if(root == NULL) root = new Node{new_val, NULL};
            else{
                Node* node = find_ptr(new_val);
                if (new_val > node->data) node->right = new Node{new_val, node};
                else if(new_val < node->data) node->left = new Node{new_val, node};
                else Size--;
            }
        }   
        void erase(T val){
            if(root != NULL){
                Node* elem_to_delete = find_ptr(val);
                if(elem_to_delete->data == val){
                    if(elem_to_delete->right != NULL){
                        Node* node = find_min(elem_to_delete->right);
                        elem_to_delete->data = node->data;
                        if(node->parent != elem_to_delete) node->parent->left = node->right; 
                        else node->parent->right = node->right;
                        if(node->right != NULL) node->right->parent = node->parent;
                        delete node;
                    }
                    else if(elem_to_delete->left != NULL){
                        Node* node = find_max(elem_to_delete->left);
                        elem_to_delete->data = node->data;
                        if(node->parent != elem_to_delete) node->parent->right = node->left;
                        else node->parent->left = node->left;
                        if(node->left != NULL) node->left->parent = node->parent;
                        delete node;
                    } 
                    else{
                        if(elem_to_delete->parent != NULL){
                            if(elem_to_delete->parent->left == elem_to_delete) elem_to_delete->parent->left = NULL;
                            else elem_to_delete->parent->right = NULL;
                        }
                        else root = NULL;
                        delete elem_to_delete;
                    }
                    Size--;
                }
            }
        }
        bool find(T val){ return root == NULL ? false : find_ptr(val)->data == val; }
        vector<T> findInRange_vector(T minObject, T maxObject){
            vector<T> elements; 
            if(minObject < maxObject)findInRange_vector(minObject, maxObject, &elements, root);
            return elements;
        }
        int findInRange(T minObject, T maxObject){
            int num = 0; 
            if(minObject < maxObject) num = findInRange(minObject, maxObject, root);
            return num;
        }
        void eraseRange(T minObject, T maxObject){
            vector<T> elems_to_erase;
            if(minObject < maxObject){
                findInRange_vector(minObject, maxObject, &elems_to_erase, root);
                for(auto it = elems_to_erase.begin(); it != elems_to_erase.end(); ++it) erase(*it);
            }
        }
        int height(){ return height(root); }
        bool empty(){ return Size <= 0; }
        int size(){ return this->Size; }
        void print(){
            cout << "inorder traversal :" << endl;
            if(root == NULL) cout << "No elements" << endl;
            else inorderTraversal(root);
            cout << endl;
        } 
        void preorderTraversal(){
            cout << "preorder treversal :" << endl;
            if(root != NULL) preorderTraversal(root);
            else cout << "No elements to traverse" << endl;
            cout << endl;
        }
        void merge(BinarySearchTree<T>& tree){
            Node* new_root = tree.root;
            root = merge(root, new_root);
        }
        BinarySearchTree<T>* split(T key){
            Node* new_root = NULL;
            if (root->data == key){
                new_root = new Node(key, NULL);
                new_root->left = NULL;
                new_root->right = root->right;
            }
            else{
                pair<Node*, Node*> p = split(root, key);
                cout << p.first->data << " " << p.second->data << endl;
                new_root = p.second;
            }
            BinarySearchTree<T>* new_tree = new BinarySearchTree<T>{new_root};
            return new_tree;
        }
    private :

        Node* merge(Node* t1, Node* t2){
            if (t1 == NULL) return t2;
            if (t2 == NULL) return t1;
            t1->data += t2->data;
            t1->left = merge(t1->left, t2->left);
            if(t1->left) t1->left->parent = t1;
            t1->right = merge(t1->right, t2->right);
            if(t1->right) t1->right->parent = t1;
            return t1;
        }   
        void preorderTraversal(Node* node){
            if(node != NULL){
                cout << node->data << " | ";
                preorderTraversal(node->left);
                preorderTraversal(node->right);
            }
        }
        void inorderTraversal(Node* node){
            if(node != NULL){
                inorderTraversal(node->left);
                cout << node->data << " | ";
                inorderTraversal(node->right);
            }
        }
        pair<Node*, Node*> split(Node* root, T key){
            if(root == NULL) return pair<Node*, Node*>{NULL, NULL};
            else if(key > root->data){
                pair<Node*, Node*> p = split(root->right, key);
                root->right = p.first;
                if(p.first != NULL) p.first->parent = root;
                return pair<Node*, Node*>{root, p.second};
            }
            else{
                pair<Node*, Node*> p = split(root->left, key);
                root->left = p.second;
                if(p.second != NULL) p.second->parent = root;
                return pair<Node*, Node*>{p.first, root};
            }
        }
        int size(Node* node){ return node == NULL ? 0 : 1 + size(node->left) + size(node->right); }
        Node* find_ptr(T val){
            if (root != NULL){
                Node* node = root;
                while(val > node->data ? node->right != NULL : node->left != NULL){
                    if(node->data == val) return node;
                    else node = val > node->data ? node->right : node->left;
                }
                return node;
            }
            return NULL;
        }
        
        void findInRange_vector(T minObject, T maxObject, vector<T>* elements, Node* local_root){
            if(local_root != NULL){
                T data = local_root->data;
                if(data <= maxObject && data >= minObject) elements->push_back(local_root->data);
                if(data >= minObject) findInRange_vector(minObject, maxObject, elements, local_root->left);
                if(data <= maxObject) findInRange_vector(minObject, maxObject, elements, local_root->right);
            }
        }
        int findInRange(T minObject, T maxObject, Node* local_root){
            int num = 0;
            if(local_root != NULL){
                T data = local_root->data;
                if(data <= maxObject && data >= minObject) num++;
                if(data >= minObject) num += findInRange(minObject, maxObject, local_root->left);
                if(data <= maxObject) num += findInRange(minObject, maxObject, local_root->right);
            }
            return num;
        }
        int height(Node* local_root) { return local_root == NULL ? 0 : 1 + max( height( local_root->left ), height( local_root->right ) ); }
        Node* find_min(Node* local_root){
            Node* node = local_root;
            for(; node->left != NULL; node = node->left){}
            return node;
        }
        Node* find_max(Node* local_root){
            Node* node = local_root;
            for(; node->right != NULL; node = node->right){}
            return node;
        }
};