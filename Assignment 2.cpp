#include <iostream>
using namespace std;

class treenode {
    char data[10];
    treenode* left;
    treenode* right;
    friend class tree;
};

class tree {
    treenode* root;

public:
    tree() {
        root = NULL;
    }

    void create_nr();
    void create_r();
    void create_r(treenode* temp);
    void inorder();
    void inorder(treenode* temp);
    void preorder();
    void preorder(treenode* temp);
    void postorder();
    void postorder(treenode* temp);
    void inorder_n();
    void preorder_n();
    void postorder_n();
};

class stack {
    int top;
    treenode* data[30];

public:
    stack() {
        top = -1;
    }

    void push(treenode* temp);
    treenode* pop();
    treenode* tops();
    int empty();
    friend class tree;
};

treenode* stack::tops() {
    treenode* temp = data[top];
    return temp;
}

void stack::push(treenode* temp) {
    top++;
    data[top] = temp;
}

int stack::empty() {
    if (top == -1)
        return 1;
    else
        return 0;
}

treenode* stack::pop() {
    treenode* temp;
    if (empty() == 1)
        cout << "Stack is empty";
    else {
        temp = data[top];
        top--;
        return temp;
    }
    return 0;
}

void tree::inorder_n() {
    stack s1;
    treenode* temp = root;
    while (1) {
        while (temp != NULL) {
            s1.push(temp);
            temp = temp->left;
        }
        if (s1.empty() == 1)
            break;
        else {
            temp = s1.pop();
            cout << temp->data << "\t";
            temp = temp->right;
        }
    }
}

void tree::postorder_n() {
    stack s1;
    treenode* temp = root;
    while (1) {
        while (temp != NULL) {
            s1.push(temp);
            temp = temp->left;
        }
        if (s1.tops()->right == NULL) {
            temp = s1.pop();
            cout << temp->data << "\t";
        }
        while (!s1.empty() && temp == s1.tops()->right) {
            temp = s1.pop();
            cout << temp->data << "\t";
        }
        if (s1.empty())
            break;
        temp = s1.tops()->right;
    }
}

void tree::preorder_n() {
    stack s1;
    treenode* temp = root;
    while (1) {
        while (temp != NULL) {
            cout << temp->data << "\t";
            s1.push(temp);
            temp = temp->left;
        }
        if (s1.empty() == 1)
            break;
        else {
            temp = s1.pop();
            temp = temp->right;
        }
    }
}

void tree::create_r() {
    root = new treenode;
    cout << "Enter data at root: ";
    cin >> root->data;
    root->left = NULL;
    root->right = NULL;
    create_r(root);
}

void tree::create_r(treenode* temp) {
    treenode* curr;
    char ch;
    cout << "Do you want to add the data to the left of " << temp->data << ". Press l: ";
    cin >> ch;
    if (ch == 'l') {
        curr = new treenode;
        curr->left = NULL;
        curr->right = NULL;
        cout << "Enter the data: ";
        cin >> curr->data;
        temp->left = curr;
        create_r(curr);
    }
    cout << "Do you want to add the data to right of " << temp->data << ". Press r: ";
    cin >> ch;
    if (ch == 'r') {
        curr = new treenode;
        curr->left = NULL;
        curr->right = NULL;
        cout << "Enter the data: ";
        cin >> curr->data;
        temp->right = curr;
        create_r(curr);
    }
}

void tree::create_nr() {
    char ch, opt;
    treenode* temp, * curr;
    if (root == NULL) {
        root = new treenode;
        cout << "Enter the data for the root: ";
        cin >> root->data;
        root->left = NULL;
        root->right = NULL;
    }

    do {
        temp = root;
        int flag = 0;
        curr = new treenode;
        cout << "Enter the data: ";
        cin >> curr->data;
        curr->left = NULL;
        curr->right = NULL;
        while (flag == 0) {
            cout << "Do you want to enter the node to the right or left of " << temp->data << ". Press l or r: ";
            cin >> ch;
            if (ch == 'l') {
                if (temp->left == NULL) {
                    temp->left = curr;
                    flag = 1;
                }
                temp = temp->left;
            } else if (ch == 'r') {
                if (temp->right == NULL) {
                    temp->right = curr;
                    flag = 1;
                }
                temp = temp->right;
            }
        }
        cout << "Do you want to continue, press y: ";
        cin >> opt;
    } while (opt == 'y');
}

void tree::inorder() {
    inorder(root);
}

void tree::inorder(treenode* temp) {
    if (temp != NULL) {
        inorder(temp->left);
        cout << temp->data << "\t";
        inorder(temp->right);
    }
}

void tree::preorder() {
    preorder(root);
}

void tree::preorder(treenode* temp) {
    if (temp != NULL) {
        cout << temp->data << "\t";
        preorder(temp->left);
        preorder(temp->right);
    }
}

void tree::postorder() {
    postorder(root);
}

void tree::postorder(treenode* temp) {
    if (temp != NULL) {
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << "\t";
    }
}

int main() {
    tree t1;
    int ch;

    do {
        cout << "\nPress:\n1 to make the tree\n2 to make tree using recursion\n3 to inorder recursive display\n4 to postorder recursive display \n5 to preorder recursive \n6 to inorder display\n7 to postorder display \n8 to preorder display\n9 to quit" << endl;
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                t1.create_nr();
                break;
            case 2:
                t1.create_r();
                break;
            case 3:
                cout << "Inorder data is:\n";
                t1.inorder();
                break;
            case 4:
                cout << "Postorder data is:\n";
                t1.postorder();
                break;
            case 5:
                cout << "Preorder data is:\n";
                t1.preorder();
                break;
            case 6:
                cout << "Inorder data using non recursive:\n";
                t1.inorder_n();
                break;
            case 7:
                cout << "Postorder data using non recursive:\n";
                t1.postorder_n();
                break;
            case 8:
                cout << "Preorder data using non recursive:\n";
                t1.preorder_n();
                break;
            case 9:
            	return 0;
            	break;
            default:
                cout << "Wrong choice\n";
                break;
        }
    } while (1);

    return 0;
}

