#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>
using namespace std;

class ExpressionTree {
private:
    struct Node {
        string value;
        Node* left;
        Node* right;

        Node(const string& val) : value(val), left(nullptr), right(nullptr) {}
    };
    
    int evaluate(Node* t)
    {
        
    }

    Node* root;

public:
    ExpressionTree(const string &expression) 
    {

    }

    ~ExpressionTree() { deleteTree(root); }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    //print all element in infix order.
    void printInFixOrder() {
    }
    //print all element in prefix order.
    void printPreFixOrder() {
    }
    //print all element in postfix order.
    void printPostFixOrder() {
    }
    //evaluate the expression, this function return an int sience % can only work with integer in C
    int eval() {
        return evaluate(root);
    }
};

int main() {
    string infix = "( -12 + 3 ) * 4 % 5";
    //cin >> infix;
    ExpressionTree exprTree(infix);

    cout << "InFixOrder: ";
    exprTree.printInFixOrder();
    cout << "PreFixOrder: ";
    exprTree.printPreFixOrder();
    cout << "PostFixOrder: ";
    exprTree.printPostFixOrder();
    cout << "Evaluated result: " << exprTree.eval() << endl;

    return 0;
}
