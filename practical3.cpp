#include <iostream>
using namespace std;

int cqueue[5];
int front = -1, rear = -1, n = 5;

void insertCQ(int val)
{
    if ((front == 0 && rear == n - 1) || (front == rear + 1))
    {
        cout << "Queue Overflow\n";
        return;
    }
    if (front == -1)
    { // Queue is empty
        front = 0;
        rear = 0;
    }
    else
    {
        if (rear == n - 1) // Wrap around
            rear = 0;
        else
            rear++;
    }
    cqueue[rear] = val;
}

void deleteCQ()
{
    if (front == -1)
    { // Queue is empty
        cout << "Queue Underflow\n";
        return;
    }
    cout << "Element deleted from queue is: " << cqueue[front] << endl;
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        if (front == n - 1) // Wrap around
            front = 0;
        else
            front++;
    }
}

void displayCQ()
{
    if (front == -1)
    { // Queue is empty
        cout << "Queue is empty\n";
        return;
    }
    cout << "Queue elements are:\n";
    int f = front, r = rear;

    if (f <= r)
    { // Continuous section
        while (f <= r)
        {
            cout << cqueue[f] << " -> ";
            f++;
        }
    }
    else
    { // Wrap-around section
        while (f < n)
        {
            cout << cqueue[f] << " -> ";
            f++;
        }
        f = 0;
        while (f <= r)
        {
            cout << cqueue[f] << " -> ";
            f++;
        }
    }
    cout << "END\n";
}

int main()
{
    int ch, val;

    cout << "1) Insert\n";
    cout << "2) Delete\n";
    cout << "3) Display\n";
    cout << "4) Exit\n";

    do
    {
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Input for insertion: ";
            cin >> val;
            insertCQ(val);
            break;

        case 2:
            deleteCQ();
            break;

        case 3:
            displayCQ();
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (ch != 4);

    return 0;
}
