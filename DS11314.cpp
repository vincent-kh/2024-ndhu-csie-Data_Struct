#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

template<class T>
class MinMaxHeap {
public:
    MinMaxHeap() {}
    //The insert function in a Min-Max Heap adds a new element to the heap while maintaining its unique properties.
    void insert(const T& value) 
    {
        heap.push_back(value);
        percolateUp(heap.size() - 1);
    }
    // Retrieve the minimum element in the heap, throw an exception when heap is empty
    T getMin() const { return heap[0]; }
    // Retrieve the maximum element in the heap, throw an exception when heap is empty
    T getMax() const { return heap[1] > heap[2] ? heap[1] : heap[2]; }
    // Delete the minimum element in the heap, throw an exception when heap is empty
    void deleteMin() 
    {
        if (heap.empty()) throw std::exception();
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) percolateDown(0);
    }
    // Delete the maximum element in the heap, throw an exception when heap is empty
    void deleteMax() 
    {
        if (heap.empty()) throw std::exception();
        int maxIdx;
        if (heap.size() == 1)
        {
            heap.pop_back();
            return;
        }
        else if (heap.size() == 2)
            maxIdx = 1;
        else 
            maxIdx = (heap[1] > heap[2]) ? 1 : 2;
        
        heap[maxIdx] = heap.back();
        heap.pop_back();
        if (maxIdx < static_cast<int>(heap.size())) percolateDown(maxIdx);
    }

    void print()
    {
        for (const T& value : heap) cout << value << " ";
        cout << endl;
    }

private:
    vector<T> heap;
    int parent(int idx) { return (idx - 1) / 2;}
    bool isMinLevel(int idx) { return (int)log2(idx + 1) % 2 == 0; }
    int Grandchild(int idx,bool max)
    {
        int gc=4*idx+3;
        if(gc>=heap.size()) return -1;
        for(int i=1;i<=3;i++)
        {
            if(max)
            {
                if(heap[gc+i]>heap[gc]) gc=gc+i;
            }
            else
            {
                if(heap[gc+i]<heap[gc]) gc=gc+i;
            }
        }
        return gc;
    }
    void percolateUp(int idx) 
    {
        if(isMinLevel(idx))
        {
            if(idx==0) return;
            int parentIdx=parent(idx);
            if(heap[idx]>heap[parentIdx])
            {
                swap(heap[idx],heap[parentIdx]);
                percolateUpMax(parentIdx);
            }
            else
            {
                percolateUpMin(idx);
            }
        }
        else
        {
            if(idx==1) return;
            int parentIdx=parent(idx);
            if(heap[idx]<heap[parentIdx])
            {
                swap(heap[idx],heap[parentIdx]);
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
        int gp=parent(parent(idx));
        if(gp>=0&&heap[idx]<heap[gp])
        {
            swap(heap[idx],heap[gp]);
            percolateUpMin(gp);
        }
    }

    void percolateUpMax(int idx)
    {
        int gp=parent(parent(idx));
        if(gp>=0&&heap[idx]>heap[gp])
        {
            swap(heap[idx],heap[gp]);
            percolateUpMax(gp);
        }
    }

    void percolateDown(int idx) 
    {
        if(isMinLevel(idx))
        {
            percolateDownMin(idx);
        }
        else
        {
            percolateDownMax(idx);
        }
    }

    void percolateDownMin(int idx) 
    {
        int gc=Grandchild(idx,false);
        if(gc==-1) return;
        if(heap[gc]<heap[idx])
        {
            swap(heap[gc],heap[idx]);
            if(heap[gc]>heap[parent(gc)])
            {
                swap(heap[gc],heap[parent(gc)]);
            }
            percolateDownMin(gc);
        }
    }
};
int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for(j = 0;j < 10;j ++)
    {
      mmHeap.insert(rand() % 100);

    mmHeap.print();}
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
