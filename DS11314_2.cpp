#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
using namespace std;
template<class T>
class MinMaxHeap {
public:
    MinMaxHeap() {}
    //The insert function in a Min-Max Heap adds a new element to the heap while maintaining its unique properties.
    void insert(int value) 
    {
        heap.push_back(value);
        percolateUp(heap.size() - 1);
    }
    // Retrieve the minimum element in the heap, throw an exception when heap is empty
    T getMin() const 
    {
        return heap[0];
    }
    // Retrieve the maximum element in the heap, throw an exception when heap is empty
    T getMax() const 
    {
        return max(heap[1], heap[2]);
    }
    // Delete the minimum element in the heap, throw an exception when heap is empty
    void deleteMin() {
    }
    // Delete the maximum element in the heap, throw an exception when heap is empty
    void deleteMax() {
    }

private:
    vector<T> heap;

    bool isMinLevel(int idx) 
    {
        int level = 0;
        while (idx > 0) 
        {
            idx >>= 1;
            level++;
        }
        return level % 2 == 0;
    }

    void percolateUp(int idx) 
    {
        if (idx == 0) return;
        int parent = (idx - 1) / 2;
        if (isMinLevel(idx)) 
        {
            if (heap[idx] > heap[parent]) 
            {
                swap(heap[idx], heap[parent]);
                percolateUpMax(parent);
            } 
            else 
            {
                percolateUpMin(idx);
            }
        } 
        else 
        {
            if (heap[idx] < heap[parent]) 
            {
                swap(heap[idx], heap[parent]);
                percolateUpMin(parent);
            } 
            else 
            {
                percolateUpMax(idx);
            }
        }
    }

    

};
int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        cout << mmHeap.getMin() << " ";
        mmHeap.deleteMin();
      }
      catch(exception) {
        break;
      }
    }
    cout << endl;
    
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
        cout << mmHeap.getMax() << " ";
        mmHeap.deleteMax();
      }
      catch(exception) {
        break;
      }
    }

    return 0;
}
