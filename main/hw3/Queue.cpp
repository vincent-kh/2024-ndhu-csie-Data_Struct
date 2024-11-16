
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Queue
{
private:
    vector<T> data;
    int front;
    int rear;
    int size;
public:
    Queue()
    {
        front = 0;
        rear = 0;
        size = 0;
    }
    void push(T value)
    {
        data.push_back(value);
        rear++;
        size++;
    }
    void pop()
    {
        if (isEmpty())  throw("Queue is empty");
        front++;
        size--;
    }
    const T get_front()
    {
        if (isEmpty())  throw("Queue is empty");
        return data[front];
    }
    int getSize()    {return size;}
    bool isEmpty()   {return size == 0;}
};

int main()
{
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);
    while (!q.isEmpty())
    {
        cout << q.get_front() << " ";
        q.pop();
    }
    cout << endl;
    return 0;
}