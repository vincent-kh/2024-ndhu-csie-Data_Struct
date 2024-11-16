#include<iostream>
using namespace std;

template <class T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;
    };
    Node* head;
    int size;
public:
    Stack()
    {
        head = NULL;
        size = 0;
    }
    void push(T data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = head;
        head = newNode;
        size++;
    }
    void pop()
    {
        if (isEmpty())  throw("Stack is empty");
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }
    const T top()
    {
        if (isEmpty())  throw("Stack is empty");
        return head->data;
    }
    int getSize()    {return size;}
    bool isEmpty()   {return size == 0;}
};

int main()
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    while (!s.isEmpty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
    return 0;
}