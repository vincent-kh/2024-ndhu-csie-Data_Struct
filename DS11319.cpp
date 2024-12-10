#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template<class T>
class BinarySearchThreadedTree
{
private:

    T *data;
    bool isThread;
    BinarySearchThreadedTree *left, *right;

    BinarySearchThreadedTree* leftMost(BinarySearchThreadedTree* node) 
    {
        while(node && node->left && node->left->data) 
        {
            node = node->left;
        }
        return node;
    }

    BinarySearchThreadedTree* rightMost(BinarySearchThreadedTree* node) 
    {
        while(node && node->right && node->right->data && !node->right->isThread) 
        {
            node = node->right;
        }
        return node;
    }
public:
    void CreateThread(BinarySearchThreadedTree* node) 
    {
        if(!node) 
        {
            return;
        }
        if(node->left!=nullptr)
        {
            auto lr = rightMost(node->left);
            lr->right = node;
            lr->isThread = true;
            CreateThread(node->left);
        }
        if(node->right!=nullptr && !node->isThread) 
        {
            CreateThread(node->right);
        }
    }

    BinarySearchThreadedTree() : data(nullptr), isThread(false), left(nullptr), right(nullptr) {}
    BinarySearchThreadedTree *insert(T d) 
    {
        if(!this->data) 
        {
            this->data = new T {d};
            this->left = new BinarySearchThreadedTree();
            this->right = new BinarySearchThreadedTree();
            return this;
        }
        else 
        {
            if(*this->data > d)
                return (this->left)->insert(d);
            else if(*this->data < d)
                return (this->right)->insert(d);
            else
                return this;
        }
    }

    void print() 
    {
        CreateThread(this);
        auto current = leftMost(this);
        while(current!=nullptr) 
        {
            if(current->data != nullptr) {
                cout << *current->data << " ";
            }
            if(current->isThread) 
            {
                current = current->right;
            }
            else 
            {
                current = leftMost(current->right);
            }
        }
        cout << endl;
    }

    void printInOrder() 
    {
        if (data) 
        {
            left->printInOrder();
            cout << *data << " ";
            right->printInOrder();
        }
    }
};

int main() {
    int j;
    BinarySearchThreadedTree<int> bstt;
    srand(time(nullptr));
    for(j = 0;j < 10;j ++)
        bstt.insert(rand() % 100);
    bstt.print();
    return 0;
}

