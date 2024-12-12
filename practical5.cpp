#include <iostream>
using namespace std;

struct tnode
{
    int data;
    tnode *left, *right;
};

struct node
{
    tnode *x;
    node *next;
};

class queue
{
    node *front, *rear;

public:
    queue() : front(nullptr), rear(nullptr) {}

    bool isempty()
    {
        return front == nullptr;
    }

    void enque(tnode *i)
    {
        node *p = new node();
        p->x = i;
        p->next = nullptr;
        if (front == nullptr)
        {
            front = rear = p;
        }
        else
        {
            rear->next = p;
            rear = p;
        }
    }

    tnode *deque()
    {
        if (isempty())
        {
            cout << "Queue Underflow\n";
            return nullptr;
        }
        node *p = front;
        tnode *temp = p->x;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        delete p;
        return temp;
    }
};

class tree
{
    tnode *t;

public:
    tree() : t(nullptr) {}

    tnode *insert(int x)
    {
        tnode *p = new tnode();
        p->data = x;
        p->left = p->right = nullptr;

        if (t == nullptr)
            return p;

        tnode *current = t, *parent = nullptr;
        while (current != nullptr)
        {
            parent = current;
            if (x < current->data)
                current = current->left;
            else
                current = current->right;
        }

        if (x < parent->data)
            parent->left = p;
        else
            parent->right = p;

        return t;
    }

    tnode *create()
    {
        int n, key;
        cout << "\nEnter the number of nodes: ";
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cout << "\nEnter the data: ";
            cin >> key;
            t = insert(key);
        }
        return t;
    }

    void inorder(tnode *t)
    {
        if (t != nullptr)
        {
            inorder(t->left);
            cout << "\t" << t->data;
            inorder(t->right);
        }
    }

    tnode *search(int key)
    {
        tnode *current = t;
        while (current != nullptr)
        {
            if (current->data == key)
                return current;
            else if (current->data < key)
                current = current->right;
            else
                current = current->left;
        }
        return nullptr;
    }

    tnode *find_min(tnode *r)
    {
        while (r->left != nullptr)
            r = r->left;
        return r;
    }

    tnode *del(tnode *t, int key)
    {
        if (t == nullptr)
            return nullptr;

        if (key < t->data)
        {
            t->left = del(t->left, key);
        }
        else if (key > t->data)
        {
            t->right = del(t->right, key);
        }
        else
        {
            if (t->left == nullptr && t->right == nullptr)
            {
                delete t;
                return nullptr;
            }
            else if (t->left == nullptr)
            {
                tnode *temp = t->right;
                delete t;
                return temp;
            }
            else if (t->right == nullptr)
            {
                tnode *temp = t->left;
                delete t;
                return temp;
            }
            else
            {
                tnode *temp = find_min(t->right);
                t->data = temp->data;
                t->right = del(t->right, temp->data);
            }
        }
        return t;
    }

    void level_wise()
    {
        if (t == nullptr)
            return;

        queue q;
        q.enque(t);

        while (!q.isempty())
        {
            int levelSize = 0; // Keeps track of the current level's size
            queue tempQueue;

            while (!q.isempty())
            {
                tnode *current = q.deque();

                if (current != nullptr)
                {
                    cout << current->data << " ";

                    // Add left and right children to the temporary queue
                    if (current->left != nullptr)
                        tempQueue.enque(current->left);
                    if (current->right != nullptr)
                        tempQueue.enque(current->right);
                }
            }

            cout << endl;  // Move to the next line for the next level
            q = tempQueue; // Update the main queue with nodes for the next level
        }
    }
};

int main()
{
    int choice, key, cnt;
    tnode *root = nullptr, *result = nullptr;
    tree t;

    do
    {
        cout << "\nMain menu:"
                "\n1. Create"
                "\n2. Insert"
                "\n3. Display"
                "\n4. Search"
                "\n5. Delete"
                "\n10. Display Tree Level-wise"
                "\n13. Exit"
                "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            root = t.create();
            break;
        case 2:
            cout << "\nEnter the number to insert: ";
            cin >> key;
            root = t.insert(key);
            break;
        case 3:
            cout << "Binary tree (In-order traversal): ";
            t.inorder(root);
            cout << endl;
            break;
        case 4:
            cout << "\nEnter the node to search: ";
            cin >> key;
            result = t.search(key);
            if (result == nullptr)
                cout << "\nElement " << key << " not present\n";
            else
                cout << "\nElement " << key << " is present\n";
            break;
        case 5:
            cout << "\nEnter the node to delete: ";
            cin >> key;
            root = t.del(root, key);
            cout << "\nElement deleted successfully\n";
            break;
        case 10:
            cout << "\nLevel-wise display:\n";
            t.level_wise();
            break;
        case 13:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "\nInvalid choice! Please enter your choice again.\n";
        }
    } while (choice != 13);

    return 0;
}
