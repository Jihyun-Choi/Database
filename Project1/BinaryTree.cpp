#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

template <class Item>
class BST_node {//BST ������ ���� BST�� node class
    Item key_field;
    BST_node* left_son;
    BST_node* right_son;
public:
    Item value_type;
    BST_node() {}
    BST_node(Item key) { right_son = NULL; left_son = NULL; value_type = key; key_field = key; }

    void set_key(Item key) { key_field = key; }
    void set_left_son(BST_node* left) { left_son = left; }
    void set_right_son(BST_node* right) { right_son = right; }
    Item get_key() { return key_field; }
    BST_node* get_left_son() { return left_son; }
    BST_node* get_right_son() { return right_son; }
};

BST_node<string>* root;

template <class Item> //BST ����
BST_node<Item>* AddNode(BST_node<Item>* node, Item key) {
    if (node == NULL) return new BST_node<Item>(key);

    if (key < node->get_key())
        node->set_left_son(AddNode(node->get_left_son(), key));
    else if (key > node->get_key())
        node->set_right_son(AddNode(node->get_right_son(), key));
    return node;
}

template <class Item> void insert(Item data) {
    root = AddNode(root, data);
}

//Binary Tree traverals ����
template <class Item>
void inorder(BST_node<Item>* root) {//LVR
    if (root != NULL) {
        inorder(root->get_left_son());
        cout << root->get_key() << "  ";
        inorder(root->get_right_son());
    }
}

template <class Item>
void preorder(BST_node<Item>* root) {//VLR
    if (root != NULL) {
        cout << root->get_key() << "  ";
        preorder(root->get_left_son());
        preorder(root->get_right_son());
    }
}

template <class Item>
void postorder(BST_node<Item>* root) {//LRV
    if (root != NULL) {
        postorder(root->get_left_son());
        postorder(root->get_right_son());
        cout << root->get_key() << "  ";
    }
}

int main(void) {
    string sentence;
    char word[100] = "";

    cout << "Enter the sentence to implement BST" << endl << ">> ";
    getline(cin, sentence);//���ڿ� �Է�

    strcpy(word, sentence.c_str()); //string���ڿ��� char������ ��ȯ
    char* token = strtok(word, " ");//���ڿ� �ڸ���
    string str_token(token);

    while (token != NULL)
    {
        str_token = token;
        insert(str_token);//BST�� ��� ����
        token = strtok(NULL, " ");//���ڿ��� ���������� �ڸ���
    }

    cout << endl << endl << "BST inorder traversal: ";
    inorder(root);
    cout << endl << endl;

    cout << "BST preorder traversal: ";
    preorder(root);
    cout << endl << endl;

    cout << "BST postorder traversal: ";
    postorder(root);
    cout << endl << endl;

    return 0;
}