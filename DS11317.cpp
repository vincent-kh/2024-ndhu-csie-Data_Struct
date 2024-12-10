//PREPEND BEGIN
/*some text*/
//PREPEND END

//TEMPLATE BEGIN
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <vector>

using namespace std;

template<class T>
class Node
{
public:
	Node()
	{
		data = new T;
	}
	Node(T d)
	{
		data = new T;
		(*data) = d;
	}
	Node &operator=(T d)
	{
		(*data) = d;
		return *this;
	}
	friend ostream &operator<<(ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend ostream &operator<<(ostream &out, Node *n)
	{
		out<<*(n->data);
		return out;
	}
	void setData(T d)
	{
		*data = d;
	}
	T &getData() const
	{
		return *data;
	}
protected:
	T *data;
};

template<class T>
class BinaryTreeNode : public Node<T>
{
public:
	BinaryTreeNode() : Node<T>()
	{
		left = NULL;
		right = NULL;
        factor = 0;
	}
	BinaryTreeNode(T d) : Node<T>(d)
	{
		left = NULL;
		right = NULL;
        factor = 0;
	}
	BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>()
	{
		left = l;
		right = r;
        factor = 0;
	}
	BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d)
	{
		left = l;
		right = r;
        factor = 0;
	}
	void setLeft(BinaryTreeNode<T> *l)
	{
		left = l;
	}
	void setRight(BinaryTreeNode<T> *r)
	{
		right = r;
	}
	BinaryTreeNode<T> *&getLeft()
	{
		return left;
	}
	BinaryTreeNode<T> *&getRight()
	{
		return right;
	}
	bool operator>(BinaryTreeNode<T> n)
	{
		if(*(this->data) > *(n.data))
			return true;
		return false;
	}
	bool operator==(BinaryTreeNode<T> n)
	{
		if(*(this->data) == *(n.data))
			return true;
		return false;
	}
    
    int factor;
private:
	BinaryTreeNode<T> *left, *right;
    
};

template<class T>
class AVLTree
{
private:
    BinaryTreeNode<T> *root;
void inorder(BinaryTreeNode<T> *cur, int n)
  {
    if(cur == NULL)
      return;
    inorder(cur->getRight(), n + 1);
    int j;
    for(j = 0;j < n;j ++)
      cout << "  ";
    cout << cur << endl;
    inorder(cur->getLeft(), n + 1);
  }

    int height(BinaryTreeNode<T> *cur)
    {
        if(cur == NULL)
            return 0;
        return 1 + max(height(cur->getLeft()), height(cur->getRight()));
    }

    int balanceFactor(BinaryTreeNode<T> *cur)
    {
        return height(cur->getLeft()) - height(cur->getRight());
    }

    void check_factor(BinaryTreeNode<T>* cur)
    {
        if(cur==nullptr)    return;
        cur->factor=balanceFactor(cur);
        check_factor(cur->getLeft());
        check_factor(cur->getRight());
    }

    BinaryTreeNode<T>* rR(BinaryTreeNode<T>* &cur)
    {
        BinaryTreeNode<T>* newRoot = cur->getLeft();
        cur->setLeft(newRoot->getRight());
        newRoot->setRight(cur);
        return newRoot;
    }
    
    BinaryTreeNode<T>* rL(BinaryTreeNode<T>* &cur)
    {
        BinaryTreeNode<T>* newRoot = cur->getRight();
        cur->setRight(newRoot->getLeft());
        newRoot->setLeft(cur);
        return newRoot;
    }

    BinaryTreeNode<T>* rLR(BinaryTreeNode<T>* node)
    {
        node->setLeft(rL(node->getLeft()));
        return rR(node);
    }

    BinaryTreeNode<T>* rRL(BinaryTreeNode<T>* node)
    {
        node->setRight(rR(node->getRight()));
        return rL(node);
    }
	
    BinaryTreeNode<T>* balance(BinaryTreeNode<T>* node)
    {
        if(node->factor > 1)
        {
            if(node->getLeft()->factor > 0)
                return rR(node);
            else
                return rLR(node);
        }
        else if(node->factor < -1)
        {
            if(node->getRight()->factor < 0)
                return rL(node);
            else
                return rRL(node);
        }
        return node;
    }

    void insert_r(T d, BinaryTreeNode<T>*& cur)
	{
		if(cur == nullptr)
			cur = new BinaryTreeNode<T>(d);
		else if(d > cur->getData())
		{
			if(cur->getRight() == nullptr)    cur->setRight(new BinaryTreeNode<T>(d));
			else                              insert_r(d, cur->getRight());
		}
		else if(d < cur->getData())
		{
			if(cur->getLeft() == nullptr)     cur->setLeft(new BinaryTreeNode<T>(d));
			else                              insert_r(d, cur->getLeft());
		}
        check_factor(cur);
        cur = balance(cur);
		
	}
public:
    AVLTree()
    {
        root = NULL;
    }
    
    void insert(T d)
    {
        insert_r(d,root);
    }

    void inorder()
    {
        inorder(root, 0);
    }
};

int main()
{
	AVLTree<int> *tree = new AVLTree<int>();
	srand(0);
	int j, k, i;
	for(j = 0;j < 20;j ++)
	{
		tree->insert(rand() % 100);
		tree->inorder();
	}
}
