#include <iostream>
#include <cmath>    
#include <queue>

using namespace std;
template<class T>
class BinaryTreeInArray 
{
private:
    T *array;
    int height;
    int numOfElement;
    
    void resize(int size) 
    {
        T *temp = new T[numOfElement];
        int j;
        for(j = 0;j < numOfElement;j ++)
            temp[j] = array[j];
        delete array;
        array = new T[static_cast<int>(pow(2, height + 1)) - 1];
        for(j = 0;j < numOfElement;j ++)
            array[j] = temp[j];
        height ++;
        delete temp;
    }
public:
    BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}
    void addElementAsCompleteTree(T data) 
    {
        int cap = pow(2, height) - 1;
        if(numOfElement + 1 > cap)
            resize((cap + 1) * 2 - 1);
        array[numOfElement] = data;
        numOfElement ++;
    }
    
    int get_p(int index)            {return (index - 1) / 2;}

    int get_s(int index,bool lr)    {return 2*index+1+lr;}
    
    void displayInorder(int index=0) 
    {
        if(index>=numOfElement)
            return;
        displayInorder(get_s(index,0));
        cout<<array[index]<<' ';
        displayInorder(get_s(index,1)); 
    }
    
    void displayPreorder(int index=0) 
    {
        if(index>=numOfElement)
            return;
        cout<<array[index]<<' ';
        displayPreorder(get_s(index,0));
        displayPreorder(get_s(index,1)); 
    }
    
    void displayPostorder(int index=0) 
    {
        if(index>=numOfElement)
            return;
        displayPostorder(get_s(index,0));
        displayPostorder(get_s(index,1));
        cout<<array[index]<<' ';
    }
};

template<class T>
class BinaryTreeInLinkedList 
{
private:
    class TreeNode 
    {
    private:
    public:
        TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
        TreeNode *left, *right;
        T data;
    };
    TreeNode *root;
    int numOfElement;
public:
    BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}
    
    void addElementAsCompleteTree(T data) 
    {
        numOfElement++;
        if (root == nullptr)
        {
            root = new TreeNode(data);
            return;
        } 
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) 
        {
            TreeNode* temp = q.front();
            q.pop();
            if (!temp->left) 
            {
                temp->left = new TreeNode(data);
                break;
            } 
            else 
                q.push(temp->left);
            if (!temp->right) 
            {
                temp->right = new TreeNode(data);
                break;
            } 
            else 
                q.push(temp->right);
        }
    }
    
    void displayInorder()
    {
        displayInorder_r(root);
    } 
    
    void displayPreorder() 
    {
        displayPreorder_r(root);
    }
    
    void displayPostorder() 
    {
        displayPostorder_r(root);
    }
    
    void displayInorder_r(TreeNode* node) 
    {
        if(node==nullptr)
            return;
        displayInorder_r(node->left);
        cout<<node->data<<' ';
        displayInorder_r(node->right);
    }
    
    void displayPreorder_r(TreeNode* node) 
    {
        if(node==nullptr)
            return;
        cout<<node->data<<' ';
        displayPreorder_r(node->left);
        displayPreorder_r(node->right);
    }
    
    void displayPostorder_r(TreeNode* node) 
    {
        if(node==nullptr)
            return;
        displayPostorder_r(node->left);
        displayPostorder_r(node->right);
        cout<<node->data<<' ';
    }
    
    void printTree()
    {
        printTree_r(root);
    }
    
    void printTree_r(TreeNode* node) 
    {
        if (node == nullptr) return;
        if (node->left != nullptr) {
            cout << node->data << " -> " << node->left->data<<endl;
        }
        if (node->right != nullptr) {
            cout << node->data << " -> " << node->right->data<<endl;
        }
        printTree_r(node->left);
        printTree_r(node->right);
    }
};

int main()
{
  BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
  BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
  int j, n;
  cin >> n;
  for(j = 0;j < n;j ++) {
    b->addElementAsCompleteTree(j);
    tree->addElementAsCompleteTree(j);
  }
  b->displayInorder();
  cout << endl;
  tree->displayInorder();
  cout << endl;
  b->displayPreorder();
  cout << endl;
  tree->displayPreorder();
  cout << endl;
  b->displayPostorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
  return 0;
}
