#include <iostream>
#include <string>

using namespace std;

template<class T>
class BinarySearchTree 
{
private:
    struct Node 
    {
        Node(T d):data{d},left{nullptr},right{nullptr}{}
        T data;
        Node *left, *right;
    };
    void inorder(Node *cur) 
    {
        if(!cur)
            return;
        inorder(cur->left);
        cout << cur->data << " ";
        inorder(cur->right);
    }
    Node *root;
public:
    BinarySearchTree() : root(nullptr) {}
    void insertElement(T d) 
    {
        if(root==nullptr)
        {
            root=new Node(d);
            return;
        }
        insertElement_r(d,root);
    }
    
    void insertElement_r(T d, Node *cur) 
    {
        if(d>cur->data)
        {
            if(cur->right==nullptr)
            {
                cur->right=new Node(d);
                return;
            }
            insertElement_r(d,cur->right);
        }
        else if (d<cur->data)
        {
            if(cur->left==nullptr)
            {
                cur->left=new Node(d);
                return;
            }
            insertElement_r(d,cur->left);
        }
        else
            return;
    }
    void print() 
    {
        inorder(root);
        cout << endl;
    }
    bool search(T d) 
    {
        return search_r(d,root);
    }
    bool search_r(T d,Node *cur)
    {
        if(d>cur->data)
        {
            if(cur->right==nullptr)
                return false;
            return search_r(d,cur->right);
        }
        else if (d<cur->data)
        {
            if(cur->left==nullptr)
                return false;
            return search_r(d,cur->left);
        }
        else
            return true;
    }
    
    int height() 
    {
        return maxDepth(root);
    }
    int maxDepth(Node *node) 
    {
        if (node == nullptr)
            return 0;

        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

        return max(lDepth, rDepth) + 1;
    }
};

int main() {
    int data;
    string command;
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    while(true) 
    {
        cin >> command;
        if(command == "insert") 
        {
            cin >> data;
            bst->insertElement(data);
        }
        else if(command == "search") 
        {
            cin >> data;
            if(bst->search(data))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        }
        else if(command == "height") 
        {
            cout << bst->height() << endl;
        }
        else if(command == "print") 
        {
            bst->print();
        }
        else if(command == "exit") 
        {
            break;
        }
    }
}
