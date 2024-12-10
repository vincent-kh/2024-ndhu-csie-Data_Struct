#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <algorithm>
using namespace std;

template<class T>
class MinMaxHeap {
public:
    MinMaxHeap() {}

    void insert(T value) 
    {
        heap.push_back(value);
        percolateUp(heap.size() - 1);
    }

    T getMin() const 
    {
        if (heap.empty()) throw std::out_of_range("Heap is empty!");
        return heap[0];
    }

    T getMax() const 
    {
        if (heap.empty()) throw std::out_of_range("Heap is empty!");
        if (heap.size() == 1) return heap[0];
        if (heap.size() == 2) return heap[1];
        return (heap[1] > heap[2]) ? heap[1] : heap[2];
    }

    void deleteMin() 
    {
        if (heap.empty()) throw std::out_of_range("Heap is empty!");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) percolateDown(0);
    }

    void deleteMax() 
    {
        if (heap.empty()) throw std::out_of_range("Heap is empty!");
        int maxIdx;
        if (heap.size() == 1) 
        {
            heap.pop_back();
            return;
        } 
        else if (heap.size() == 2) 
        {
            maxIdx = 1;
        }
        else 
        {
            maxIdx = (heap[1] > heap[2]) ? 1 : 2;
        }
        heap[maxIdx] = heap.back();
        heap.pop_back();
        if (maxIdx < static_cast<int>(heap.size())) percolateDown(maxIdx);
    }

private:
    vector<T> heap;

    void percolateUp(int idx) 
    {
        if (idx == 0) return;
        int parentIdx = parent(idx);
        if (onMinLevel(idx)) 
        {
            if (heap[idx] > heap[parentIdx]) 
            {
                swap(heap[idx], heap[parentIdx]);
                percolateUpMax(parentIdx);
            } 
            else 
            {
                percolateUpMin(idx);
            }
        } 
        else 
        {
            if (heap[idx] < heap[parentIdx]) 
            {
                swap(heap[idx], heap[parentIdx]);
                percolateUpMin(parentIdx);
            }
            else
            {
                percolateUpMax(idx);
            }
        }
    }

    void percolateUpMin(int idx) 
    {
        while (grandParent(idx) >= 0 && heap[idx] < heap[grandParent(idx)]) 
        {
            swap(heap[idx], heap[grandParent(idx)]);
            idx = grandParent(idx);
        }
    }

    void percolateUpMax(int idx) {
        while (grandParent(idx) >= 0 && heap[idx] > heap[grandParent(idx)]) 
        {
            swap(heap[idx], heap[grandParent(idx)]);
            idx = grandParent(idx);
        }
    }

    void percolateDown(int idx) 
    {
        int paridx = parent(idx);
        if (onMinLevel(idx)) 
        {
            if(heap[idx]<heap[paridx])
            {
                percolateDownMin(idx);
            }
            else
            {
                percolateDownMax(idx);
            }
        }
        else
        {
            if(heap[idx]>heap[paridx])
            {
                percolateDownMax(idx);
            }
            else
            {
                percolateDownMin(idx);
            }
        }
    }

    void percolateDownMin(int idx) 
    {
        int minIdx = minDescendant(idx);
        if (minIdx == -1) return;
        if (heap[minIdx] < heap[idx]) 
        {
            swap(heap[minIdx], heap[idx]);
            if (isGrandChild(minIdx, idx)) 
            {
                if (heap[minIdx] > heap[parent(minIdx)]) 
                {
                    swap(heap[minIdx], heap[parent(minIdx)]);
                }
                percolateDownMin(minIdx);
            }
        }
    }

    void percolateDownMax(int idx) 
    {
        int maxIdx = maxDescendant(idx);
        if (maxIdx == -1) return;
        if (heap[maxIdx] > heap[idx]) 
        {
            swap(heap[maxIdx], heap[idx]);
            if (isGrandChild(maxIdx, idx)) 
            {
                if (heap[maxIdx] < heap[parent(maxIdx)]) 
                {
                    swap(heap[maxIdx], heap[parent(maxIdx)]);
                }
                percolateDownMax(maxIdx);
            }
        }
    }

    bool onMinLevel(int idx) const 
    {
        int level = 0;
        while (idx > 0) 
        {
            idx = parent(idx);
            level++;
        }
        return level % 2 == 0;
    }

    int parent(int idx) const { return (idx - 1) / 2; }
    int grandParent(int idx) const { return (idx <= 2) ? -1 : parent(parent(idx)); }

    bool hasChild(int idx) const { return (2 * idx + 1) < static_cast<int>(heap.size()); }
    bool isGrandChild(int childIdx, int idx) const { return grandParent(childIdx) == idx; }

    int minDescendant(int idx) const 
    {
        int m = -1;
    
        int start = 4 * idx + 3;
        int end = min(static_cast<int>(heap.size()), start + 4);

        for (int i = start; i < end; ++i) {
            if (m == -1 || heap[i] < heap[m]) {
                m = i;
            }
        }
        return m;
    }


    int maxDescendant(int idx) const {
        int m = -1;
        int start = 2 * idx + 1;
        int end = min(static_cast<int>(heap.size()), start + 2);
        for (int i = start; i < end; ++i) {
            if (m == -1 || heap[i] > heap[m]) {
                m = i;
            }
        }
        return m;
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
      catch(std::exception) {
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
