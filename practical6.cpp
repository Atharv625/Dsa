#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    int lth, rth; // Left and right thread flags
    Node *left, *right;
};

class ThreadedBinaryTree
{
private:
    Node *root;
    Node *dummy;

    void inorder(Node *current);
    void preorder(Node *current);

public:
    ThreadedBinaryTree();
    ~ThreadedBinaryTree();

    void create();
    void insert(Node *current, Node *newNode);
    void display();
    void clear(Node *current);
};

ThreadedBinaryTree::ThreadedBinaryTree()
{
    root = nullptr;
    dummy = new Node;
    dummy->data = -999;
    dummy->left = dummy->right = dummy;
    dummy->lth = dummy->rth = 0;
}

ThreadedBinaryTree::~ThreadedBinaryTree()
{
    clear(root);
    delete dummy;
}

void ThreadedBinaryTree::clear(Node *current)
{
    if (current && current != dummy)
    {
        if (current->lth)
            clear(current->left);
        if (current->rth)
            clear(current->right);
        delete current;
    }
}

void ThreadedBinaryTree::create()
{
    Node *newNode = new Node;
    newNode->left = newNode->right = nullptr;
    newNode->lth = newNode->rth = 0;

    cout << "\nEnter the element: ";
    cin >> newNode->data;

    if (root == nullptr)
    {
        root = newNode;
        root->left = root->right = dummy;
        dummy->left = root;
    }
    else
    {
        insert(root, newNode);
    }
}

void ThreadedBinaryTree::insert(Node *current, Node *newNode)
{
    if (newNode->data < current->data)
    {
        if (current->lth == 0)
        {
            newNode->left = current->left;
            newNode->right = current;
            current->left = newNode;
            current->lth = 1;
        }
        else
        {
            insert(current->left, newNode);
        }
    }
    else if (newNode->data > current->data)
    {
        if (current->rth == 0)
        {
            newNode->right = current->right;
            newNode->left = current;
            current->right = newNode;
            current->rth = 1;
        }
        else
        {
            insert(current->right, newNode);
        }
    }
}

void ThreadedBinaryTree::display()
{
    if (root == nullptr)
    {
        cout << "Tree is empty." << endl;
        return;
    }

    cout << "\nIn-order Traversal: ";
    inorder(root);

    cout << "\nPre-order Traversal: ";
    preorder(root);
}

void ThreadedBinaryTree::inorder(Node *current)
{
    while (current != dummy)
    {
        while (current->lth == 1)
            current = current->left;

        cout << current->data << " ";

        while (current->rth == 0)
        {
            current = current->right;
            if (current == dummy)
                return;
            cout << current->data << " ";
        }

        current = current->right;
    }
}

void ThreadedBinaryTree::preorder(Node *current)
{
    while (current != dummy)
    {
        cout << current->data << " ";

        if (current->lth == 1)
        {
            current = current->left;
        }
        else
        {
            while (current->rth == 0 && current->right != dummy)
                current = current->right;

            current = current->right;
        }
    }
}

int main()
{
    ThreadedBinaryTree tbt;
    int choice;
    char ans;

    do
    {
        cout << "\nProgram for Threaded Binary Tree"
             << "\n1) Create"
             << "\n2) Display"
             << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            do
            {
                tbt.create();
                cout << "\nDo you want to enter more elements? (y/n): ";
                cin >> ans;
            } while (ans == 'y' || ans == 'Y');
            break;

        case 2:
            tbt.display();
            break;

        default:
            cout << "\nInvalid choice!";
        }

        cout << "\n\nWant to see the main menu again? (y/n): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}
