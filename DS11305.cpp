#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
	Node()
	{
		next = NULL;
		pre = NULL;
	}
	Node(int n)
	{
		data = n;
		next = NULL;
		pre = NULL;
	}
	int getData() { return data; }
	Node *getNext() { return next; }
	Node *getPre() { return pre; }
	void setData(int d) { data = d; }
	void setNext(Node *n) { next = n; }
	void setPre(Node *p) { pre = p; }
private:
	int data;
	Node *next, *pre; 
};

class List
{
public:
	List() { list = NULL; }
	List(int n) { generate(n); }
	
	void generate(int n)
	{
		int j;
		list = NULL;
		for(j = 0;j < n;j ++)
			generate();
	}
	
	void generate()
	{
		Node *buf = new Node(rand());
		buf->setNext(list);
		if(list != NULL)
			list->setPre(buf);
		list = buf;
	}
	
	void bubbleSort()
	{
        Node *cur;
		for(cur = list;cur != NULL;cur = cur->getNext())
		{
			for(Node *next = cur->getNext();next != NULL;next = next->getNext())
			{
				if(cur->getData() > next->getData())
					swap(cur, next);
			}
		}
	}
	
	void selectionSort()
	{
        Node *cur, *next, *min;
        for(cur = list;cur != NULL;cur = cur->getNext())
        {
            min = cur;
            for(next = cur->getNext();next != NULL;next = next->getNext())
                if(min->getData() > next->getData())
                    min = next;
            swap(cur, min);
        }
	}
	
	void insertionSort()
	{
	    if (list == nullptr || list->getNext() == nullptr) return;

	    Node* cur = list->getNext();
	    while (cur != nullptr)
	    {
	        Node* temp = cur;
	        while (temp->getPre() != nullptr && temp->getData() < temp->getPre()->getData())
	        {
	            swap(temp, temp->getPre());
	            temp = temp->getPre();
	        }
	        cur = cur->getNext();
	    }
	} 
	
    void swap(Node *a, Node *b)
    {
        int temp = a->getData();
        a->setData(b->getData());
        b->setData(temp);
    }

	void print()
	{
		Node *cur = list;
		while(cur != NULL)
		{
			cout<<cur->getData()<<" ";
			cur = cur->getNext();
		}
		cout<<endl;
	}
	
private:
	Node *list;
};

int main()
{
	srand(time(NULL));
	List *l = new List(10);
	l->print();
	l->bubbleSort();
	l->print();
	
	l = new List(10);
	l->print();
	l->insertionSort();
	l->print();
	
	l = new List(10);
	l->print();
	l->selectionSort();
	l->print();
}
