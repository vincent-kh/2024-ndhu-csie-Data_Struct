#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template<class T>
class MaxHeap 
{
public:
    //Constructing a empty heap.
    MaxHeap(){}
    //To add an element to the heap.
    void insert(T n)
    {
        heap.push_back(n);
        int i = heap.size() - 1;
        while (i != 0 && heap[parrent(i)] < heap[i])
        {
            swap(heap[i], heap[parrent(i)]);
            i = parrent(i);
        }
    }
    //To remove the root element in the heap and return it.
    T extract()
    {
        if (heap.size() == 0)
        {
            throw runtime_error("Heap is empty");
        }
        T root = heap[0];
        heap[0] = heap[heap.size() - 1];
        heap.size();
        heap.pop_back();
        int i = 0;
        while (i < heap.size())
        {
            int j = -1;
            if (child(i, 0) < heap.size() && heap[child(i, 0)] > heap[i])
            {
                j = child(i, 0);
            }
            if (child(i, 1) < heap.size() && heap[child(i, 1)] > heap[i] && heap[child(i, 1)] > heap[child(i, 0)])
            {
                j = child(i, 1);
            }
            if (j == -1)
            {
                break;
            }
            swap(heap[i], heap[j]);
            i = j;
        }
        return root;
    }
    //Return the number of element int the heap.
    int count(){return heap.size();}
    
    void print()
    {
        int low = log2(heap.size());
        for(int j = 0; j < low + 1; j++)
        {
            int start = (1 << j) - 1;
            int end = (1 << (j + 1)) - 1;
            for(int i = start; i < end && i < heap.size(); i++)
            {
                cout << heap[i] << " ";
            }
            cout << endl;
        }
    }


private:
    int parrent(int i){return (i - 1) / 2;}
    int child(int i, bool j){return 2 * i + j + 1;}
    vector<T> heap;
};

int main()
{
    MaxHeap<int> heap;
    heap.insert(3);
    heap.insert(2);
    heap.insert(1);
    heap.insert(15);
    heap.insert(5);
    heap.insert(4);
    heap.insert(45);
    heap.insert(6);
    heap.print();
    cout<<endl;

    cout << heap.extract() << endl;
    cout << endl;
    heap.print();
    return 0;
}