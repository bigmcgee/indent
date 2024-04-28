#include <iostream>
using namespace std;

class tbtnode {
    friend class tbt;
    bool rbit;
    bool lbit;
    int data;
    tbtnode *rightc;
    tbtnode *leftc;
public:
    tbtnode(int val);
};

tbtnode::tbtnode(int val) {
    data = val;
    lbit = 0;
    rbit = 0;
    leftc = nullptr;
    rightc = nullptr;
}

class tbt {
    tbtnode *head;
public:
    void create();
    void inorder();
    void preorder();
    tbtnode *insucc(tbtnode *temp);
    tbt();
};

tbt::tbt() {
    head = nullptr;
}

void tbt::create() {
    int data;
    cout << "Enter data for the root node: ";
    cin >> data;
    head = new tbtnode(data);
    char choice;
    tbtnode *current = head;
    do {
        int value;
        cout << "Enter data for the new node: ";
        cin >> value;
        tbtnode *newNode = new tbtnode(value);
        
        // Prompt for left or right insertion
        cout << "Insert as left child or right child? (l/r): ";
        cin >> choice;
        
        if (choice == 'l' || choice == 'L') {
            if (current->lbit == 0) {
                newNode->leftc = current->leftc;
                newNode->rightc = current;
                current->leftc = newNode;
                current->lbit = 1;
                current = newNode;
            } else {
                current = current->leftc;
            }
        } else {
            if (current->rbit == 0) {
                newNode->rightc = current->rightc;
                newNode->leftc = current;
                current->rightc = newNode;
                current->rbit = 1;
                current = newNode;
            } else {
                current = current->rightc;
            }
        }
        cout << "Do you want to insert another node? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void tbt::inorder() {
    tbtnode *temp = head;
    while (temp->lbit == 1)
        temp = temp->leftc;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = insucc(temp);
    }
}

void tbt::preorder() {
    tbtnode *temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        if (temp->lbit == 1)
            temp = temp->leftc;
             else if (temp->rbit == 1)
            temp = temp->rightc;
        else {
            while (temp != nullptr && temp->rbit == 0)
                temp = temp->rightc;
            if (temp != nullptr)
                temp = temp->rightc;
        }
    }
}

tbtnode* tbt::insucc(tbtnode *temp) {
    tbtnode *x = temp->rightc;
    if (temp->rbit == 1) {
        while (x->lbit == 1)
            x = x->leftc;
    }
    return x;
}

int main() {
    tbt tree;
    tree.create();
    cout << "Inorder traversal: ";
    tree.inorder();
    cout << endl;
    cout << "Preoder Traversal: ";
    tree.preorder();
    cout << endl;
    return 0;
}