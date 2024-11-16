#include<iostream>
using namespace std;

template <class T>

class C_deque
{
private:
    T* data;
    int capacity;
    int front;
    int rear;
    int size;
public:
    C_deque(int capacity)
    {
        this->capacity = capacity;
        data = new T[capacity];
        front = 0;
        rear = 0;
        size = 0;
    }
    void push_front(T value)
    {
        if (size == capacity)  throw("Deque is full");
        front = (front - 1 + capacity) % capacity;
        data[front] = value;
        size++;
    }
    void push_back(T value)
    {
        if (size == capacity)  throw("Deque is full");
        data[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
    }
    void pop_front()
    {
        if (isEmpty())  throw("Deque is empty");
        front = (front + 1) % capacity;
        size--;
    }
    void pop_back()
    {
        if (isEmpty())  throw("Deque is empty");
        rear = (rear - 1 + capacity) % capacity;
        size--;
    }
    const T get_front()
    {
        if (isEmpty())  throw("Deque is empty");
        return data[front];
    }
    const T get_back()
    {
        if (isEmpty())  throw("Deque is empty");
        return data[(rear - 1 + capacity) % capacity];
    }
    int getSize()    {return size;}
    bool isEmpty()   {return size == 0;}
};

int main()
{
    C_deque<int> dq(20);
    dq.push_front(1);
    dq.push_front(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_front(5);   
    while (!dq.isEmpty())
    {
        cout << dq.get_front() << " ";
        dq.pop_front();
    }
    cout << endl;
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(3);
    dq.push_front(4);
    dq.push_back(5);
    while (!dq.isEmpty())
    {
        cout << dq.get_back() << " ";
        dq.pop_back();
    }
    cout << endl;
    return 0;
}
