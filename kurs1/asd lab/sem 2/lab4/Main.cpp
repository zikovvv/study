#include "autocomplete.h"
#include "test_avl_tree.h"

using namespace std;
void bin_tree_default_test(){
    testBinarySearchTree();
}
void bin_tree_test_split_merge(){
    BinarySearchTree<int> tree1;
    
    int N = 20;
    int* to_insert = new int[N];
    for (size_t i = 0; i < N; i++) {
        to_insert[i] = i;
    }
    for (size_t i = 0; i < N * 4; i++)
        tree1.insert(to_insert[rand() % N]);

    tree1.preorderTraversal();

    int index = 16;
    cout << endl <<  "split by elem : " << to_insert[index] << endl;
    BinarySearchTree<int> tree2 = *tree1.split(to_insert[index]);

    cout << "tree 1 after split" << endl;
    tree1.preorderTraversal();
    tree1.print();

    cout << "tree 2 after split" << endl;
    tree2.print();
    tree2.preorderTraversal();
    
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
    
    int N = 20;
    int* to_insert = new int[N];
    for (size_t i = 0; i < N; i++) {
        to_insert[i] = i;
    }
    for (size_t i = 0; i < N * 4; i++)
        tree1.insert(to_insert[rand() % N]);

    tree1.preorderTraversal();

    int index = 16;
    cout << endl <<  "split by elem : " << to_insert[index] << endl;
    AVLTree<int> tree2 = *tree1.split(to_insert[index]);

    cout << "tree 1 after split" << endl;
    tree1.preorderTraversal();
    tree1.print();

    cout << "tree 2 after split" << endl;
    tree2.print();
    tree2.preorderTraversal();
    
    cout << "merge" << endl;
    tree1.merge(tree2);
    tree1.print();
    tree1.preorderTraversal();

    cout << "erased" << endl;
    tree1.eraseRange(to_insert[3], to_insert[N - 3]);
    tree1.print();
    tree1.preorderTraversal();
}
void autocompleter_test(){
    srand(time(NULL));
    const char* filepath = "words_alpha.txt";
    Trie autocompleter;
    autocompleter.insert_words_from_file(filepath);
    vector<string*> possible_words = *autocompleter.indByPrefix("abai");
    for (auto i = possible_words.begin(); i != possible_words.end(); ++i) cout << **i << endl;
}
int main(){
    srand(time(NULL));

    //autocompleter_test();
    bin_tree_default_test();
    //bin_tree_test_split_merge();
    //avl_tree_default_test();
    //avl_tree_test_split_merge();

    cout << "finished" << endl;
    getchar();
    return 0;
}