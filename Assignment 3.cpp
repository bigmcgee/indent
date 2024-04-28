#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
const int MAX_SIZE = 100;

struct Node {
    char key[50];
    char meaning[100];
    Node* left;
    Node* right;
    Node(const char* key, const char* meaning) {
    strcpy(this->key, key);
    strcpy(this->meaning, meaning);
    left = nullptr;
    right = nullptr;
    }
};

class Dictionary {
    private:
    Node* root;
    Node* queue[MAX_SIZE];
    int front, rear;
    public:
    Dictionary() {
    root = nullptr;
    front = -1;
    rear = -1;
}

void insert(const char* key, const char* meaning) { root = insert(root, key, meaning); }
    Node* insert(Node* node, const char* key, const char* meaning) {
    if (node == nullptr) {
    return new Node(key, meaning);
    }

    if (strcmp(key, node->key) < 0) {
    node->left = insert(node->left, key, meaning);
}

    else if (strcmp(key, node->key) > 0) {
    node->right = insert(node->right, key, meaning);
    }

    else {
    cout << "Keyword already exists\n" << endl;
    return node; // Return the node without insertion
    }
    return node;
}

void deleteKeyword(const char* key) { root = deleteKeyword(root, key); }
    Node* deleteKeyword(Node* node, const char* key) {
    if (node == nullptr) {
    cout << "Keyword not found\n" << endl;
    return node;
    }

    if (strcmp(key, node->key) < 0) {
    node->left = deleteKeyword(node->left, key);
    }

    else if (strcmp(key, node->key) > 0) {
    node->right = deleteKeyword(node->right, key);
    }

    else {
    if (node->left == nullptr) {
    Node* temp = node->right;
    delete node;
    return temp;
    }

    else if (node->right == nullptr) {
    Node* temp = node->left;
    delete node;
    return temp;
    }

    Node* temp = findMin(node->right);
    strcpy(node->key, temp->key);
    strcpy(node->meaning, temp->meaning);
    node->right = deleteKeyword(node->right, temp->key);
    }
    return node;
}

void createMirrorImage() { root = createMirrorImage(root); }
    Node* createMirrorImage(Node* node) {
    if (node == nullptr) {
    return nullptr;
    }
    Node* left = createMirrorImage(node->left);
    Node* right = createMirrorImage(node->right);
    node->left = right;
    node->right = left;
    return node;
}

void displayLevelWise() {
    if (root == nullptr) {
    cout << "Dictionary is empty\n" << endl;
    return;
}
    enqueue(root);
    Node* temp;
    while (!isEmpty()) {
        temp = dequeue();
        cout << temp->key << " : " << temp->meaning << " ";

        if (temp->left != nullptr) {
        enqueue(temp->left);
        }

        if (temp->right != nullptr) {
        enqueue(temp->right);
        }
    }
}

    Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}
    bool isEmpty() { return front == -1 && rear == -1; }
    bool isFull() { return (rear + 1) % MAX_SIZE == front; }
    void enqueue(Node* node) {
    if (isFull()) {
        cout << "Queue is full\n" << endl;
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    } 
    else {
        rear = (rear + 1) % MAX_SIZE;
    }
    queue[rear] = node;
    }

    Node* dequeue() {
    if (isEmpty()) {
        cout << "Queue is empty\n" << endl;
        return nullptr;
    }

    Node* temp = queue[front];
    if (front == rear) {
        front = rear = -1;
    } 
    else {
        front = (front + 1) % MAX_SIZE;
    }
    return temp;
    }
};
int main() {
    Dictionary dictionary;
    int choice;
    char key[50];
    char meaning[100];

    do {
        cout << "\n\n1. Insert Keyword" << endl;
        cout << "2. Delete Keyword" << endl;
        cout << "3. Create Mirror Image" << endl;
        cout << "4. Display Level Wise" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: \n";
        cin >> choice;
        switch (choice) {
        case 1:
        cout << "Enter keyword: ";
        cin >> key;
        cout << "Enter meaning: ";
        cin >> meaning;
        dictionary.insert(key, meaning);
        break;

        case 2:
        cout << "Enter keyword to delete: ";
        cin >> key;
        dictionary.deleteKeyword(key);
        break;

        case 3:
        dictionary.createMirrorImage();
        cout << "Mirror image created\n" << endl;
        break;

        case 4:
        dictionary.displayLevelWise();
        break;

        case 5:
        exit(0);
        }
    } while (choice != 5);
return 0;
}