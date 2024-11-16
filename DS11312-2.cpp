#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>
#include <sstream>
using namespace std;

class ExpressionTree 
{
private:
    struct Node 
    {
        string value;
        Node* left;
        Node* right;

        Node(const string& val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int evaluate(Node* t) 
    {
        if (!t) return 0;

        if (!isOperator(t->value)) 
            return stoi(t->value);

        int left = evaluate(t->left);
        int right = evaluate(t->right);

        if (t->value == "+") return left + right;
        if (t->value == "-") return left - right;
        if (t->value == "*") return left * right;
        if (t->value == "/") return right != 0 ? left / right : throw runtime_error("Division by zero");
        if (t->value == "%") return right != 0 ? left % right : throw runtime_error("Modulo by zero");

        throw runtime_error("Unknown operator");
    }

    bool isOperator(const string& s) 
    {
        return s == "+" || s == "-" || s == "*" || s == "/" || s == "%";
    }

    int precedence(const string& op) 
    {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/" || op == "%") return 2;
        return 0;
    }

    void inOrderTraversal(Node* node) 
    {
        if (!node) return;
        bool needParen = isOperator(node->value);
        if (needParen) cout << "(";
        inOrderTraversal(node->left);
        cout << node->value << " ";
        inOrderTraversal(node->right);
        if (needParen) cout << ")";
    }

    void preOrderTraversal(Node* node) 
    {
        if (!node) return;
        cout << node->value << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }

    void postOrderTraversal(Node* node) 
    {
        if (!node) return;
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << node->value << " ";
    }

public:
    ExpressionTree(const string& expression) 
    {
        stack<Node*> nodeStack;
        stack<string> operatorStack;
        istringstream iss(expression);
        string token;

        while (iss >> token) 
        {
            if (token == "(")
                operatorStack.push(token);
            else if (token == ")") 
            {
                while (!operatorStack.empty() && operatorStack.top() != "(") 
                {
                    string op = operatorStack.top();
                    operatorStack.pop();

                    Node* right = nodeStack.top(); nodeStack.pop();
                    Node* left = nodeStack.top(); nodeStack.pop();

                    Node* newNode = new Node(op);
                    newNode->left = left;
                    newNode->right = right;

                    nodeStack.push(newNode);
                }
                if (!operatorStack.empty()) operatorStack.pop();
            }
            else if (isOperator(token)) 
            {
                while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(token)) 
                {
                    string op = operatorStack.top();
                    operatorStack.pop();

                    Node* right = nodeStack.top(); nodeStack.pop();
                    Node* left = nodeStack.top(); nodeStack.pop();

                    Node* newNode = new Node(op);
                    newNode->left = left;
                    newNode->right = right;

                    nodeStack.push(newNode);
                }
                operatorStack.push(token);
            }
            else 
                nodeStack.push(new Node(token));
        }

        while (!operatorStack.empty()) 
        {
            string op = operatorStack.top();
            operatorStack.pop();

            Node* right = nodeStack.top(); nodeStack.pop();
            Node* left = nodeStack.top(); nodeStack.pop();

            Node* newNode = new Node(op);
            newNode->left = left;
            newNode->right = right;

            nodeStack.push(newNode);
        }

        if (nodeStack.size() != 1) throw runtime_error("Invalid expression");
        root = nodeStack.top();
    }

    ~ExpressionTree() { deleteTree(root); }

    void deleteTree(Node* node) 
    {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void printInFixOrder() 
    {
        inOrderTraversal(root);
        cout << endl;
    }

    void printPreFixOrder() 
    {
        preOrderTraversal(root);
        cout << endl;
    }

    void printPostFixOrder() 
    {
        postOrderTraversal(root);
        cout << endl;
    }

    int eval() 
    {
        return evaluate(root);
    }
};

int main() 
{
    string infix;
    getline(cin, infix);
    ExpressionTree exprTree(infix);

    cout << "Inorder: ";
    exprTree.printInFixOrder();
    cout << "Preorder: ";
    exprTree.printPreFixOrder();
    cout << "Postorder: ";
    exprTree.printPostFixOrder();
    cout << "Evaluated result: " << exprTree.eval() << endl;

    return 0;
}