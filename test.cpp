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
    public:
        T data;
        TreeNode *parent;
        vector<TreeNode*> children; // 新增：用於儲存子節點的向量

        TreeNode(T d, TreeNode *p) : data(d), parent(p) {}
    };

    

public:
    vector<TreeNode *> *nodeList; // 儲存樹中所有節點的向量
    TreeInLinkedList() 
    {
        nodeList = new vector<TreeNode *>();
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
            for(j = 0; j < k; j++) 
            {
                if(data % (*nodeList)[j]->data == 0) 
                {
                    TreeNode *newNode = new TreeNode(data, (*nodeList)[j]);
                    (*nodeList)[j]->children.push_back(newNode); // 新增節點為子節點
                    nodeList->push_back(newNode);
                    break; // 確保每個元素只有一個父節點
                }
            }
        }
    }

    void displayPreorder() 
    {
        if (nodeList->empty()) return;
        displayPreorderHelper(nodeList->front()); // 從根節點開始
    }

    void displayPostorder() 
    {
        if (nodeList->empty()) return;
        displayPostorderHelper(nodeList->front()); // 從根節點開始
    }
    void drawTree(TreeNode *node, int depth) 
    {
        if (!node) return;
        for (int i = 0; i < depth; i++) 
        {
            cout << "  ";
        }
        cout << node->data << endl;
        for (TreeNode *child : node->children) 
        {
            drawTree(child, depth + 1); // 遞迴繪製每個子節點
        }
    }
private:
    void displayPreorderHelper(TreeNode *node) 
    {
        if (!node) return;
        cout << node->data << " "; // 先輸出當前節點
        for (TreeNode *child : node->children) 
        {
            displayPreorderHelper(child); // 遞迴訪問每個子節點
        }
    }

    void displayPostorderHelper(TreeNode *node) 
    {
        if (!node) return;
        for (TreeNode *child : node->children) 
        {
            displayPostorderHelper(child); // 先遞迴訪問每個子節點
        }
        cout << node->data << " "; // 在輸出完子節點後輸出當前節點
    }

    
};

int main()
{
    TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
    int n;
    cin >> n;
    for(int j = 1; j <= n; j++)
        tree->addElement(j);

    tree->displayPreorder();
    cout << endl;
    tree->displayPostorder();
    cout << endl;
    tree->drawTree(tree->nodeList->front(), 0);

    delete tree;
}
