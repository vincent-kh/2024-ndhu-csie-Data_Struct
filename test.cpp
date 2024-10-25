#include <iostream>
#include <queue>

using namespace std;

template<class T>
class BinaryTreeInLinkedList 
{
private:
    class TreeNode 
    {
    public:
        TreeNode(T d) : data(d), left(nullptr), right(nullptr) {}
        TreeNode *left, *right;
        T data;
    };
    
    int numOfElement;

    // Queue to facilitate insertion in level-order fashion
    queue<TreeNode*> q;

    // Helper functions for traversals
    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(TreeNode* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(TreeNode* node) {
        if (node == nullptr) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << " ";
    }

public:
    TreeNode *root;
    BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

    TreeNode* addElementRecursively(TreeNode* node, T data) {
        if (node == nullptr) {
            return new TreeNode(data);
        }

        if (numOfElement % 2 == 0) {
            node->left = addElementRecursively(node->left, data);
        } else {
            node->right = addElementRecursively(node->right, data);
        }

        return node;
    }

    void addElementAsCompleteTree(T data) {
        numOfElement++;
        root = addElementRecursively(root, data);
    }

    // In-order traversal
    void displayInorder() {
        inorderTraversal(root);
        cout << endl;
    }

    // Pre-order traversal
    void displayPreorder() {
        preorderTraversal(root);
        cout << endl;
    }

    // Post-order traversal
    void displayPostorder() {
        postorderTraversal(root);
        cout << endl;
    }

    // print tree by recursion
    void printTree(TreeNode* node) 
    {
        if (node == nullptr) return;
        //cout << node->data << " ";
        if (node->left != nullptr) {
            cout << node->data << " -> " << node->left->data<<endl;
        }
        if (node->right != nullptr) {
            cout << node->data << " -> " << node->right->data<<endl;
        }
        printTree(node->left);
        printTree(node->right);
        
    }

    // Destructor to free memory
    ~BinaryTreeInLinkedList() {
        // Helper function to delete nodes in post-order traversal
        freeMemory(root);
    }

private:
    void freeMemory(TreeNode* node) {
        if (node == nullptr) return;
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
};

int main()
{
    BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
    int n;
    
    // Input the number of elements to be inserted into the tree
    cout << "Enter the number of elements to add: ";
    cin >> n;

    // Insert elements into the tree
    cout << "Adding elements to the tree..." << endl;
    for (int j = 0; j < n; j++) 
    {
        tree->addElementAsCompleteTree(j);
    }

    // Display the tree in level-order
    cout << "Level-order (breadth-first) traversal: "<<endl;
    tree->printTree(tree->root);

    // Display in-order traversal
    cout << "In-order traversal: ";
    tree->displayInorder();

    // Display pre-order traversal
    cout << "Pre-order traversal: ";
    tree->displayPreorder();

    // Display post-order traversal
    cout << "Post-order traversal: ";
    tree->displayPostorder();

    // Free allocated memory
    delete tree;

    return 0;
}
