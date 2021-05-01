#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;
struct Node_char{
    bool isWord = false;
    bool isLeaf = false;
    unordered_map<char, Node_char*> children;
};
class Trie {
    public :
        ~Trie(){destructor(root);cout<<"autocompleter destructed" << endl;} 
        Node_char* root = new Node_char;
        void insert(char* word) {
            Node_char* node = root;
            int l = strlen(word);
            for (int i = 0; i < l; i++) {
                node->isLeaf = false;
                if (node->children.count(word[i]) == 0) {
                    Node_char* next = new Node_char;
                    node->children.insert({word[i], next });
                    node = next;
                    if (i == l - 1) node->isLeaf = true;
                }
                else node = node->children.at(word[i]);
            }
            node->isWord = true;
        }
        void insert_words_from_file(const char* filepath){
            fstream f;
            f.open(filepath, ios::in | ios::out);
            char temp[100];
            while(!f.eof()){
                f >> temp;
                insert(temp);
            }
            f.close();
        }
        vector<string*>* indByPrefix(string word) {
            cout << "search for words starting with " << '"' << word << '"' << endl;
            vector<string*>* possible_words = new vector<string*>;
            Node_char* node = root;
            for (int i = 0; i < word.length(); i++) {
                if (node->children.count(word[i]) == 0) return possible_words;
                node = node->children.at(word[i]);
            }
            indByPrefix(new string(word), node, possible_words);
            return possible_words;
        }
    private : 
        void indByPrefix(string* word, Node_char* local_root, vector<string*>* possible_words) {
            if(local_root->isWord) {
                possible_words->push_back(word);
                word = new string(*word);
            }
            if(!local_root->isLeaf){
                string parentword(*word);
                for(auto it = local_root->children.cbegin(); it != local_root->children.cend(); ++it){
                    string* new_word = it == local_root->children.cbegin() ? word : new string(parentword);
                    new_word->push_back(it->first);
                    indByPrefix(new_word, it->second, possible_words);
                }
            }
        }
        void destructor(Node_char* local_root){
            for(auto it = local_root->children.cbegin(); it != local_root->children.cend(); ++it){
                destructor(it->second);
                delete it->second;
            }
        }
};
