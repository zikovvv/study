#include "autocomplete.h"
#include "test_avl_tree.h"

using namespace std;
void bin_tree_default_test(){
    testBinarySearchTree();
}
void bin_tree_test_split_merge(){
    BinarySearchTree<int> tree1;
    
    int N = 8;
    int* to_insert = new int[N];
    for (size_t i = 0; i < N; i++) {
        to_insert[i] = i;
    }
    for (size_t i = 0; i < N * 4; i++)
        tree1.insert(to_insert[rand() % N]);

    tree1.preorderTraversal();
    
    cout << endl <<  "split by elem : " << to_insert[2] << endl;
    BinarySearchTree<int> tree2 = *tree1.split(to_insert[4]);
    tree1.preorderTraversal();
    tree1.print();
    
    cout << "tree 2" << endl;
    tree2.print();
    tree2.preorderTraversal();
    cout << endl;
    
    cout << "merge" << endl;
    tree1.merge(tree2);
    tree1.print();
    tree1.preorderTraversal();

    cout << "erased" << endl;
    tree1.eraseRange(to_insert[3], to_insert[N - 3]);
    tree1.print();
    tree1.preorderTraversal();
}
void avl_tree_default_test(){
    testAVLTree();
}
void avl_tree_test_split_merge(){
    AVLTree<int> tree1;
    
    int N = 4;
    int* to_insert = new int[N];
    for (size_t i = 0; i < N; i++) {
        to_insert[i] = i;
    }
    for (size_t i = 0; i < N * 4; i++)
        tree1.insert(to_insert[rand() % N]);

    //tree1.preorderTraversal();
   
    cout << endl <<  "split by elem : " << to_insert[2] << endl;
    AVLTree<int> tree2 = *tree1.split(to_insert[2]);
    tree2.~AVLTree();
    cout << "tree2 destructed" << endl;
    tree1.~AVLTree();
    /*
    tree1.preorderTraversal();
    tree1.print();

    cout << "tree 2" << endl;
    tree2.print();
    tree2.preorderTraversal();
    cout << endl;
    
    cout << "merge" << endl;
    tree1.merge(tree2);
    tree1.print();
    tree1.preorderTraversal();

    cout << "erased" << endl;
    //tree1.eraseRange(to_insert[3], to_insert[N - 3]);
    tree1.print();
    tree1.preorderTraversal();
    */
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
    srand(time(NULL));

    bin_tree_default_test();
    bin_tree_test_split_merge();
    avl_tree_default_test();
    avl_tree_test_split_merge();
    


    cout << "finished" << endl;
    getchar();
    return 0;
}