#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include "test_binary_search_tree.h"
using namespace std;
template<typename T> class AVLTree{
    public :
        typedef AVLNode<T> Node;
        Node* root = NULL;
        int Size = 0;
        AVLTree(){

        }
        AVLTree(Node* node){
            root = node;
            Size = size(root);
            updateHeightGlobalRecursive(root);
        }
        ~AVLTree(){
            cout << "destructed" << endl;
            auto f = [=](Node* node){ delete node; };
            postorderTraversal(root, f);
        }
        
        void insert(T val){
            Size++;
            if(root == NULL) root = new Node{val, NULL};
            else insert(root, val);
        }
        void erase(T val){
            if(root){
                Size--;
                root = erase(root, val);
            }
        }
        T eraseMin(Node* local_root){
            if (local_root->left == NULL){
                local_root->parent->left = local_root->right;
                if(local_root->right) local_root->right->parent = local_root->parent;
                T val = local_root->data;
                delete local_root;
                return val;
            }
            T val = eraseMin(local_root->left);
            balance(local_root);
            return val;
        }
        T eraseMax(Node* local_root){
            if (local_root->right == NULL){
                local_root->parent->right = local_root->left;
                if(local_root->left) local_root->left->parent = local_root->parent;
                T val = local_root->data;
                delete local_root;
                return val;
            }
            T val = eraseMax(local_root->right);
            balance(local_root);
            return val;
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
            findInRange_vector(minObject, maxObject, &elems_to_erase, root);
            for(auto it = elems_to_erase.begin(); it != elems_to_erase.end(); ++it) erase(*it);
        }
        int height(){ return root->height; }
        bool empty(){ return root == NULL; }
        int size(){ return this->Size; }
        AVLTree<T>* split(T key){
            pair<Node*, Node*> p = split(root, key);
            Node* new_root = p.second;
            root = p.first;
            AVLTree<T>* new_tree = new AVLTree<T>(new_root);
            updateHeightGlobalRecursive(root);
            return new_tree;
        }
        void print(){
            auto f = [this](Node* node){ cout << node->data << " | "; };
            cout << "inorder traversal :" << endl;
            if(root == NULL) cout << "No elements" << endl;
            else inorderTraversal(root, f);
            cout << endl;
        } 
        void preorderTraversal(){
            cout << "preorder traversal :" << endl;
            //auto f = [this](Node* node){ cout << node->data << ' ' << bfactor(node) << endl <<  " | "; };
            auto f = [this](Node* node){ cout << node->data <<  " | "; };
            if(root != NULL) preorderTraversal(root, f);
            else cout << "No elements to traverse" << endl;    
            cout << endl;
        }
        void merge(AVLTree<T> &tree){
            Node* new_root = tree.root;
            root = merge(root, new_root);
            tree.root = NULL;
            updateHeightGlobalRecursive(root);
        }
        int bfactor(Node* local_root){
            return local_root == NULL ? 0 : (local_root->left != NULL ? local_root->left->height : 0) - (local_root->right != NULL ? local_root->right->height : 0);
        }
        void balance(Node* local_root){
            updateHeightLocal(local_root);
            int factor = bfactor(local_root);

            if (factor == 2) {
                if (bfactor(local_root->left) < 0){
                    rotateLeft(local_root->left);
                }
                rotateRight(local_root);
            } 
            else if(factor == -2){
                if (bfactor(local_root->right) > 0){
                    rotateRight(local_root->right);
                }
                rotateLeft(local_root);
            }
        }
        void updateHeightLocal(Node* r){
            if(r != NULL)
                r->height = 1 + max(r->right ? r->right->height : 0, r->left ? r->left->height : 0);
        }
        void updateHeightGlobalRecursive(Node* node){
            if(node != NULL){
                updateHeightGlobalRecursive(node->left);
                updateHeightGlobalRecursive(node->right);
                node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
            }
        }
        void rotateRight(Node* r){
            Node* temp_node = r->right;
            T temp_val = r->data;
            r->right = r->left;
            r->left = r->right->left;
            if(r->left) r->left->parent = r;
            r->right->left = r->right->right;
            r->right->right = temp_node;
            if (temp_node) temp_node->parent = r->right;
            r->data = r->right->data;
            r->right->data = temp_val;
            updateHeightLocal(r->right);
            updateHeightLocal(r);
        }
        void rotateLeft(Node* r){
            Node* temp_node = r->left;
            T temp_val = r->data;
            r->left = r->right;
            r->right = r->left->right;
            if(r->right) r->right->parent = r;
            r->left->right = r->left->left;
            r->left->left = temp_node;
            if (temp_node) temp_node->parent = r->left;
            r->data = r->left->data;
            r->left->data = temp_val;
            updateHeightLocal(r->left);
            updateHeightLocal(r);
        }

    private :
        void insert(Node* r, T val){
            if (r->data != val){
                if(val > r->data){ 
                    if(r->right == NULL) r->right = new Node{val, r};
                    else insert(r->right, val);
                }
                else if(val < r->data){
                    if(r->left == NULL) r->left = new Node{val, r};
                    else insert(r->left, val);
                }
                balance(r);
            }
            else Size--;
        }
        void preorderTraversal(Node* node, auto& action){
            if(node != NULL){
                action(node);
                preorderTraversal(node->left, action);
                preorderTraversal(node->right, action);
            }
        }
        void inorderTraversal(Node* node, auto& action){
            if(node != NULL){
                inorderTraversal(node->left, action);
                action(node);
                inorderTraversal(node->right, action);
            }
        }
        void postorderTraversal(Node* node, auto& action){
            if(node != NULL){
                postorderTraversal(node->left, action);
                postorderTraversal(node->right, action);
                action(node);
            }
        }
        Node* merge(Node* t1, Node* t2){
            if (t2 == NULL) return t1;
            if (t1 == NULL) return t2;
            else if (t1->data > t2->data){
                t1->right = merge(t1->right, t2);
                return t1;
            }
            else{
                t2->left = merge(t1, t2->left);
                return t2;
            }
        }
        pair<Node*, Node*> split(Node* local_root, T key){
            if(local_root == NULL) return pair<Node*, Node*>{NULL, NULL};
            else if(key > local_root->data){
                pair<Node*, Node*> p = split(local_root->right, key);
                local_root->right = p.first;
                if(p.first) p.first->parent = local_root;
                return pair<Node*, Node*>{local_root, p.second};
            }
            else{
                pair<Node*, Node*> p = split(local_root->left, key);
                local_root->left = p.second;
                if(p.second) p.second->parent = local_root;
                return pair<Node*, Node*>{p.first, local_root};
            }
        }
        int size(Node* node){ return node == NULL ? 0 : 1 + size(node->left) + size(node->right); }
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
                if(data > minObject) num += findInRange(minObject, maxObject, local_root->left);
                if(data < maxObject) num += findInRange(minObject, maxObject, local_root->right);
            }
            return num;
        }
        Node* erase(Node* local_root, T val){
            if (local_root == NULL){
                Size++;
                return NULL;
            }
            Node* reserve = local_root;
            if (val < local_root->data){
                local_root->left = erase(local_root->left, val);
                if(local_root->left) local_root->left->parent = local_root;
            }
            else if (val > local_root->data) {
                local_root->right = erase(local_root->right, val);
                if(local_root->right) local_root->right->parent = local_root;
            }
            else if (local_root->left != NULL and local_root->right != NULL) {
                if(local_root->right->left == NULL){
                    local_root->data = local_root->right->data;
                    reserve = local_root->right;
                    local_root->right = local_root->right->right;
                    delete reserve;
                    if(local_root->right) local_root->right->parent = local_root;
                }
                else
                    local_root->data = eraseMin(local_root->right);
            }
            else {
                reserve = local_root;
                if (local_root->left != NULL)
                    local_root = local_root->left;
                else if (local_root->right != NULL)
                    local_root = local_root->right;
                else
                    local_root = NULL;
                delete reserve;
            }
            balance(local_root);
            return local_root;
        }
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
};


