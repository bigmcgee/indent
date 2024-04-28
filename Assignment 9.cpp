#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Structure for a node in AVL tree
struct Node {
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;
};

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to update height of a node
void updateHeight(Node* node) {
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Function to rotate right subtree rooted with y
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    // Return new root
    return x;
}

// Function to rotate left subtree rooted with x
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    // Return new root
    return y;
}

// Function to perform insertion in AVL tree
Node* insert(Node* node, string keyword, string meaning) {
    // Perform normal BST insertion
    if (node == nullptr) {
        Node* newNode = new Node;
        newNode->keyword = keyword;
        newNode->meaning = meaning;
        newNode->height = 1;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    if (keyword < node->keyword)
        node->left = insert(node->left, keyword, meaning);
    else if (keyword > node->keyword)
        node->right = insert(node->right, keyword, meaning);
    else // Keyword already exists, update meaning
        node->meaning = meaning;

    // Update height of this ancestor node
    updateHeight(node);

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && keyword < node->left->keyword)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && keyword > node->right->keyword)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && keyword > node->left->keyword) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && keyword < node->right->keyword) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to search for a keyword in AVL tree
Node* search(Node* root, string keyword) {
    if (root == nullptr || root->keyword == keyword)
        return root;

    if (root->keyword < keyword)
        return search(root->right, keyword);

    return search(root->left, keyword);
}

// Function to find minimum node in AVL tree
Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// Function to delete a node in AVL tree
Node* deleteNode(Node* root, string keyword) {
    if (root == nullptr)
        return root;

    if (keyword < root->keyword)
        root->left = deleteNode(root->left, keyword);
    else if (keyword > root->keyword)
        root->right = deleteNode(root->right, keyword);
    else {
        // Node to be deleted found

        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(root->right);

            // Copy the inorder successor's data to this node
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->keyword);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr)
        return root;

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalanceFactor(root);

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to print AVL tree inorder (sorted)
void printInorder(Node* root) {
    if (root != nullptr) {
        printInorder(root->left);
        cout << root->keyword << ": " << root->meaning << endl;
        printInorder(root->right);
    }
}

// Function to print AVL tree in reverse inorder (sorted in descending order)
void printReverseInorder(Node* root) {
    if (root != nullptr) {
        printReverseInorder(root->right);
        cout << root->keyword << ": " << root->meaning << endl;
        printReverseInorder(root->left);
    }
}

int main() {
    Node* root = nullptr;
    int choice;
    string keyword, meaning;

    while (true) {
        cout << "\nMenu\n1. Add a new keyword\n2. Delete a keyword\n3. Update meaning of a keyword\n";
        cout << "4. Display data sorted in ascending order\n5. Display data sorted in descending order\n";
        cout << "6. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword to add: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin.ignore(); // Ignore newline character from previous input
                getline(cin, meaning);
                root = insert(root, keyword, meaning);
                cout << "Keyword added successfully." << endl;
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                root = deleteNode(root, keyword);
                cout << "Keyword deleted successfully." << endl;
                break;
            case 3:
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cout << "Enter new meaning: ";
                cin.ignore(); // Ignore newline character from previous input
                getline(cin, meaning);
                root = insert(root, keyword, meaning);
                cout << "Meaning updated successfully." << endl;
                break;
            case 4:
                cout << "Data sorted in ascending order:" << endl;
                printInorder(root);
                break;
            case 5:
                cout << "Data sorted in descending order:" << endl;
                printReverseInorder(root);
                break;
            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
