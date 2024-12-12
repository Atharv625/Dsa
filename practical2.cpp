#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

struct node
{
    char data;
    node *next;
};

class stack
{
    node *top;

public:
    stack()
    {
        top = nullptr;
    }

    bool isempty()
    {
        return top == nullptr;
    }

    void push(char x)
    {
        node *p = new node();
        p->data = x;
        p->next = top;
        top = p;
    }

    char pop()
    {
        if (isempty())
        {
            cout << "Stack underflow\n";
            return '\0';
        }
        char x = top->data;
        node *p = top;
        top = top->next;
        delete p;
        return x;
    }

    char topdata()
    {
        if (isempty())
        {
            cout << "Stack is empty\n";
            return '\0';
        }
        return top->data;
    }
};

int precedence(char x)
{
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return 3;
}

void infix_postfix(char infix[], char postfix[])
{
    stack s;
    int i = 0, j = 0;
    char token;

    while (infix[i] != '\0')
    {
        token = infix[i++];
        if (isalnum(token))
        {
            postfix[j++] = token;
        }
        else if (token == '(')
        {
            s.push(token);
        }
        else if (token == ')')
        {
            while (s.topdata() != '(')
            {
                postfix[j++] = s.pop();
            }
            s.pop(); // Remove '('
        }
        else
        {
            while (!s.isempty() && precedence(token) <= precedence(s.topdata()))
            {
                postfix[j++] = s.pop();
            }
            s.push(token);
        }
    }

    while (!s.isempty())
    {
        postfix[j++] = s.pop();
    }
    postfix[j] = '\0';
}

void reverse(char a[], char b[])
{
    int len = strlen(a);
    for (int i = 0; i < len; ++i)
    {
        if (a[len - i - 1] == '(')
            b[i] = ')';
        else if (a[len - i - 1] == ')')
            b[i] = '(';
        else
            b[i] = a[len - i - 1];
    }
    b[len] = '\0';
}

void infix_prefix(char infix[], char prefix[])
{
    char infix1[20], prefix1[20];
    reverse(infix, infix1);
    infix_postfix(infix1, prefix1);
    reverse(prefix1, prefix);
}

int evaluate(int op1, int op2, char op)
{
    switch (op)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    case '%':
        return op1 % op2;
    default:
        return 0;
    }
}

void evaluate_postfix(char postfix[])
{
    stack s;
    int i = 0, x, op1, op2, result;

    while (postfix[i] != '\0')
    {
        char token = postfix[i++];
        if (isalnum(token))
        {
            cout << "Enter value for " << token << ": ";
            cin >> x;
            s.push(x);
        }
        else
        {
            op2 = s.pop();
            op1 = s.pop();
            result = evaluate(op1, op2, token);
            s.push(result);
        }
    }
    cout << "Result: " << s.pop() << endl;
}

void evaluate_prefix(char prefix[])
{
    stack s;
    int i = strlen(prefix) - 1, x, op1, op2, result;

    while (i >= 0)
    {
        char token = prefix[i--];
        if (isalnum(token))
        {
            cout << "Enter value for " << token << ": ";
            cin >> x;
            s.push(x);
        }
        else
        {
            op1 = s.pop();
            op2 = s.pop();
            result = evaluate(op1, op2, token);
            s.push(result);
        }
    }
    cout << "Result: " << s.pop() << endl;
}

int main()
{
    char infix[20], postfix[20], prefix[20];
    int ch;

    do
    {
        cout << "\n1. Infix to Postfix\n";
        cout << "2. Infix to Prefix\n";
        cout << "3. Evaluate Postfix\n";
        cout << "4. Evaluate Prefix\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Enter Infix Expression: ";
            cin >> infix;
            infix_postfix(infix, postfix);
            cout << "Postfix: " << postfix << endl;
            break;
        case 2:
            cout << "Enter Infix Expression: ";
            cin >> infix;
            infix_prefix(infix, prefix);
            cout << "Prefix: " << prefix << endl;
            break;
        case 3:
            cout << "Enter Postfix Expression: ";
            cin >> postfix;
            evaluate_postfix(postfix);
            break;
        case 4:
            cout << "Enter Prefix Expression: ";
            cin >> prefix;
            evaluate_prefix(prefix);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (ch != 5);

    return 0;
}
