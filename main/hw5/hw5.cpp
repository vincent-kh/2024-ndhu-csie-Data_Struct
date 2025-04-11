//q2 indexOfElement(e) -> indexOf(e), positionOfElement(e) -> atIndex(indexOf(e))

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class CircularArraySequence {
public:
    CircularArraySequence(int capacity = 10)
        : capacity(capacity), size(0), front(0), rear(0) {
        arr = new T[capacity];
    }

    ~CircularArraySequence() {
        delete[] arr;
    }

    void push_back(const T& value) {
        ensureCapacity();
        arr[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
    }

    void pop_back() {
        if (isEmpty()) throw underflow_error("Sequence is empty.");
        rear = (rear - 1 + capacity) % capacity;
        size--;
    }

    void insert_front(const T& value) {
        ensureCapacity();
        front = (front - 1 + capacity) % capacity;
        arr[front] = value;
        size++;
    }

    void erase_front() {
        if (isEmpty()) throw underflow_error("Sequence is empty.");
        front = (front + 1) % capacity;
        size--;
    }

    T& atIndex(int index) 
    {
        if (index < 0 || index >= size) throw out_of_range("Index out of range.");
        return arr[(front + index) % capacity];
    }

    int indexOf(const T& value) const {
        for (int i = 0; i < size; i++) {
            if (arr[(front + i) % capacity] == value) {
                return i;
            }
        }
        return -1;
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

private:
    T* arr;
    int capacity;
    int size;
    int front;
    int rear;

    void ensureCapacity() {
        if (size < capacity) return;

        int newCapacity = capacity * 2;
        T* newArr = new T[newCapacity];

        for (int i = 0; i < size; i++) {
            newArr[i] = arr[(front + i) % capacity];
        }

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
        front = 0;
        rear = size;
    }
};

int main() {
    CircularArraySequence<int> sequence;

    sequence.push_back(10);
    sequence.push_back(20);
    sequence.push_back(30);
    sequence.print();

    sequence.insert_front(5);
    sequence.insert_front(1);
    sequence.print();

    cout << "Element at index 2: " << sequence.atIndex(2) << endl;
    sequence.atIndex(2) = 15;
    sequence.print();

    sequence.erase_front();
    sequence.print();
    sequence.pop_back();
    sequence.print();

    cout << "Index of 15: " << sequence.indexOf(15) << endl;

    return 0;
}
