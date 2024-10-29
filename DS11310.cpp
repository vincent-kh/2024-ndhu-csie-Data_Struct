#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

template<class T>
class TreeInLinkedList 
{
private:
    class TreeNode 
    {
    private:
    public:
        TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
        TreeNode *parent;
        T data;
    };
    vector<TreeNode *> *nodeList;
public:
    TreeInLinkedList() 
    {
        nodeList = new vector<TreeNode *>();
    }
    void print_list()
    {
        for(auto i : *nodeList)
        {
            cout << i->data << " ";
        }
    }

    void addElement(T data) 
    {
        int j, k = nodeList->size();
        if(data == 1) 
        {
            nodeList->clear();
            nodeList = new vector<TreeNode *>();
            TreeNode *newNode = new TreeNode(data, nullptr);
            nodeList->push_back(newNode);
        }
        else 
        {
            for(j = 0;j < k;j ++)
            {
                if(data % (*nodeList)[j]->data == 0) 
                {
                    TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
                    nodeList->push_back(newNode);
                }
            }
        }
    }
    void displayPreorder() 
    {
        displayPreorder_r((*nodeList)[0]);
    }
    void displayPreorder_r(TreeNode *node) 
    {
        cout << node->data << " ";
        for(auto i : *nodeList)
        {
            if(i->parent == node)
            {
                displayPreorder_r(i);
            }
        }
    }
    void displayPostorder() 
    {
        displayPostorder_r((*nodeList)[0]);
    }
    void displayPostorder_r(TreeNode *node) 
    {
        for(auto i : *nodeList)
        {
            if(i->parent == node)
            {
                displayPostorder_r(i);
            }
        }
        cout << node->data << " ";
    }
};

int main()
{
  TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
  int j;
  int n;
  cin >> n;
  for(j = 1;j <= n;j ++)
    tree->addElement(j);
  tree->displayPreorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
}