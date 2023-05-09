#include <iostream>
#include <algorithm>

class Node {
public:
    int key;
    int level;
    Node* left;
    Node* right;

    Node(int key) : key(key), level(1), left(nullptr), right(nullptr) {}
};

class AATree {
private:
    Node* root;

    Node* skew(Node* node);
    Node* split(Node* node);
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* find(Node* node, int key);
    Node* successor(Node* node);
    Node* decreaseLevel(Node* node);
    void display(Node* node, int indent);

public:
    AATree() : root(nullptr) {}

    void insert(int key);
    void remove(int key);
    Node* find(int key);
    void display();
};

Node* AATree::skew(Node* node) {
    if (node == nullptr)
        return nullptr;

    if (node->left == nullptr)
        return node;

    if (node->left->level == node->level) {
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }
    else {
        return node;
    }
}

Node* AATree::split(Node* node) {
    if (node == nullptr)
        return nullptr;

    if (node->right == nullptr || node->right->right == nullptr)
        return node;

    if (node->level == node->right->right->level) {
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        temp->level++;
        return temp;
    }
    else {
        return node;
    }
}

Node* AATree::insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        return node;
    }

    node = skew(node);
    node = split(node);
    return node;
}

Node* AATree::successor(Node* node) {
    if (node == nullptr)
        return nullptr;
    Node* temp = node->right;
    while (temp != nullptr && temp->left != nullptr) {
        temp = temp->left;
    }
    return temp;
}

Node* AATree::decreaseLevel(Node* node) {
    int expectedLevel = std::min(node->left ? node->left->level : 0, node->right ? node->right->level : 0) + 1;
    if (expectedLevel < node->level) {
        node->level = expectedLevel;
        if (node->right && expectedLevel < node->right->level) {
            node->right->level = expectedLevel;
        }
    }
    return node;
}

Node* AATree::remove(Node* node, int key) {
    if (node == nullptr)
        return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (node->left == nullptr && node->right ==nullptr)
        {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {
            Node* successorNode = successor(node);
            node->key = successorNode->key;
            node->right = remove(node->right, successorNode->key);
        }
    }

        node = decreaseLevel(node);
    node = skew(node);
    if (node->right) {
        node->right = skew(node->right);
        if (node->right->right) {
            node->right->right = skew(node->right->right);
        }
    }
    node = split(node);
    if (node->right) {
        node->right = split(node->right);
    }
    return node;
}

Node* AATree::find(Node* node, int key) {
    if (node == nullptr)
        return nullptr;

        if (key < node->key) {
            return find(node->left, key);
        }
        else if (key > node->key) {
            return find(node->right, key);
        }
        else {
            return node;
        }
}
void AATree::display(Node* node, int indent) {
    if (node == nullptr) {
        return;
    }

    display(node->right, indent + 4);
    for (int i = 0; i < indent; i++) {
        std::cout << " ";
    }
    std::cout << node->key << std::endl;
    display(node->left, indent + 4);
}
void AATree::insert(int key) {
    root = insert(root, key);
}

void AATree::remove(int key) {
    root = remove(root, key);
}

Node* AATree::find(int key) {
    return find(root, key);
}
void AATree::display() {
    display(root, 0);
}

int main() {
    AATree tree;

    tree.insert(50);
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(80);
    tree.insert(60);
    tree.insert(90);

    tree.display();
    Node* foundNode = tree.find(50);
    if (foundNode != nullptr) {
        std::cout << "Found node with key " << foundNode->key << std::endl;
    }
    else {
        std::cout << "Node doesn't exist" << std::endl;
    }

    tree.remove(30);
    tree.display();


    return 0;
}