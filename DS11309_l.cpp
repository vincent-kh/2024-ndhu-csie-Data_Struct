#include <iostream>
#include <cmath>    
#include <queue>

using namespace std;

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
            root = new TreeNode(data); 
        else 
            addElementToCompleteTree(root, data);
    }

    void addElementToCompleteTree(TreeNode* node, T data) 
    {
        queue<TreeNode*> q;
        q.push(node);

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
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
    int j, n;
    cin >> n;
    for(j = 0;j < n;j ++) {
        tree->addElementAsCompleteTree(j);
    }
    tree->printTree();
    cout << endl;
    tree->displayInorder();
    cout << endl;
    tree->displayPreorder();
    cout << endl;
    tree->displayPostorder();
    cout << endl;
    return 0;
}
