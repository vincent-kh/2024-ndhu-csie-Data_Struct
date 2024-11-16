#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
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
        if (heap.empty()) throw std::exception();
        return heap[0];
    }

    T getMax() const 
    {
        if (heap.empty()) throw std::exception();
        if (heap.size() == 1) return heap[0];
        else if (heap.size() == 2) return heap[1];
        else return (heap[1] > heap[2]) ? heap[1] : heap[2];
    }

    void deleteMin() 
    {
        if (heap.empty()) throw std::exception();
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) percolateDown(0);
    }

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
                percolateUpMin(idx);
        }
        else
        {
            if (heap[idx] < heap[parentIdx]) 
            {
                swap(heap[idx], heap[parentIdx]);
                percolateUpMin(parentIdx);
            }
            else
                percolateUpMax(idx);
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

    void percolateUpMax(int idx)
    {
        while (grandParent(idx) >= 0 && heap[idx] > heap[grandParent(idx)])
        {
            swap(heap[idx], heap[grandParent(idx)]);
            idx = grandParent(idx);
        }
    }

    void percolateDown(int idx) {onMinLevel(idx) ? percolateDownMin(idx) : percolateDownMax(idx);}

    void percolateDownMin(int idx)
    {
        while (hasChild(idx))
        {
            int m = minDescendant(idx);
            if (heap[m] < heap[idx])
            {
                swap(heap[m], heap[idx]);
                if (isGrandChild(m, idx))
                {
                    int parentIdx = parent(m);
                    if (heap[m] > heap[parentIdx])
                        swap(heap[m], heap[parentIdx]);
                    idx = m;
                }
                else
                    break;
            }
            else
                break;
        }
    }

    void percolateDownMax(int idx) 
    {
        while (hasChild(idx)) 
        {
            int m = maxDescendant(idx);
            if (heap[m] > heap[idx]) 
            {
                swap(heap[m], heap[idx]);
                if (isGrandChild(m, idx)) 
                {
                    int parentIdx = parent(m);
                    if (heap[m] < heap[parentIdx]) 
                    {
                        swap(heap[m], heap[parentIdx]);
                    }
                    idx = m;
                }
                else    break;
            }
            else    break;
        }
    }

    bool onMinLevel(int idx) 
    {
        int level = 0;
        while (idx > 0) 
        {
            idx = parent(idx);
            level++;
        }
        return level % 2 == 0;
    }

    int parent(int idx) { return (idx - 1) / 2; }
    int grandParent(int idx) { return (idx <= 2) ? -1 : parent(parent(idx)); }

    bool hasChild(int idx) { return (2 * idx + 1) < static_cast<int>(heap.size()); }
    bool isGrandChild(int childIdx, int idx) {return grandParent(childIdx) == idx;}

    int minDescendant(int idx) //找到最小的孫結點
    {
        int m = 4 * idx + 3;
        int end = min((int)heap.size(), m + 4);
        for (int i = m; i < end; ++i) 
            if (heap[i] < heap[m]) m = i;
        return m;
    }

    int maxDescendant(int idx) 
    {
        int m = 4 * idx + 3;
        int end = min((int)heap.size(), m + 4);
        for (int i = m; i < end; ++i) 
            if (heap[i] > heap[m]) m = i;
        return m;
    }
};

int main() 
{
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for(j = 0;j < 10;j ++)
        mmHeap.insert(rand() % 100);

    while(true) 
    {
        try 
        {
            cout << mmHeap.getMin() << " ";
            mmHeap.deleteMin();
        }
        catch(std::exception) {break;}
    }
   cout <<endl;
    
    for(j = 0;j < 10;j ++)
      mmHeap.insert(rand() % 100);

    while(true) {
      try {
       cout << mmHeap.getMax() << " ";
        mmHeap.deleteMax();
      }
      catch(std::exception) {
        break;
      }
    }

    return 0;
}
