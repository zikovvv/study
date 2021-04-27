#include "autocomplete.h"
#include "test_avl_tree.h"

using namespace std;
void bin_tree_default_test(){
    testBinarySearchTree();
}
void bin_tree_test_split_merge(){
    BinarySearchTree<int, Node<int>> tree1;

    int N = 20;
    int* to_insert = new int[N];
    for (size_t i = 0; i < N; i++) {
        to_insert[i] = rand() % 10;
        //cout << to_insert[i] << endl;
    }
    for (size_t i = 0; i < N; i++) {
        tree1.insert(to_insert[i]);
    }
    tree1.preorderTraversal();
    cout << endl <<  "split by elem : " << to_insert[4] << endl;
    BinarySearchTree<int, Node<int>> tree2 = *tree1.split(to_insert[4]);
    tree1.preorderTraversal();
    tree2.preorderTraversal();
    tree1.print();
    tree2.print();
    cout << endl;

    tree1.merge(&tree2);
    tree1.print();
    tree1.preorderTraversal();

    tree1.eraseRange(2, 8);
    tree1.print();

}
void avl_tree_default_test(){
    testAVLTree();
}

void autocompleter_test(){
    const char* filepath = "C:\\Users\\Latitude\\Desktop\\asd lab\\sem 2\\lab4\\words_alpha.txt";
    Trie autocompleter;
    autocompleter.insert_words_from_file(filepath);
    vector<string> possible_words = autocompleter.indByPrefix("aba");
    for (auto i = possible_words.begin(); i != possible_words.end(); ++i) cout << *i << endl;
    autocompleter.destructor();
}
int main(){
    AVLTree<int, Node<int>> t;
    t.insert(10);
    t.insert(-20);
    t.insert(123);
    t.insert(0);
    t.insert(4);
    t.print();
    cout << t.Size << endl;
    cout << t.size() << endl;

    avl_tree_default_test();
    cout << "finished" << endl;
    getchar();
    return 0;
}