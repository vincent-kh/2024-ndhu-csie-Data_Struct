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
	int getData()const { return data; }
	Node *getNext() { return next; }
	Node *getPre() { return pre; }
	void setData(int d) { data = d; }
	void setNext(Node *n) { next = n; }
	void setPre(Node *p) { pre = p; }
	bool operator<(const Node& other) const { return data < other.getData(); }
    bool operator>(const Node& other) const { return data > other.getData(); }

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
		if (list == nullptr) return;

		bool swapped;
		while (swapped)
		{
			swapped = false;
			Node *cur = list;

			while (cur->getNext() != nullptr) 
			{
				if (*cur > *cur->getNext()) 
				{
					swap(cur, cur->getNext());
					swapped = true;
				} 
				else 
					cur = cur->getNext();
			}
		}
	}

	
void selectionSort()
{
    Node *sortedTail = nullptr, *cur = list;

    while (cur != nullptr) 
	{
        Node *min = cur;
        Node *next = cur->getNext();

        while (next != nullptr) 
		{
            if (*next < *min) 
                min = next;
            next = next->getNext();
        }

        if (min != cur) 
		{
            if (min->getPre() != nullptr) 
                min->getPre()->setNext(min->getNext());
            if (min->getNext() != nullptr)
                min->getNext()->setPre(min->getPre());

            min->setNext(cur);
            min->setPre(cur->getPre());

            if (cur->getPre() != nullptr)
                cur->getPre()->setNext(min);
            else 
                list = min;
            cur->setPre(min);
        }
        sortedTail = min;
        cur = sortedTail->getNext();
    }
}

	void insertionSort()
	{
		Node* cur = list->getNext();
		while (cur != nullptr) 
		{
			Node* temp = cur;
			while (temp->getPre() != nullptr && *temp < *temp->getPre()) 
				swap(temp->getPre(), temp);
			cur = cur->getNext();
		}
	}

	
	void swap(Node *a, Node *b)
	{
		Node *a_pre = a->getPre();
		Node *b_next = b->getNext();

		if (a_pre != nullptr)
			a_pre->setNext(b);

		b->setPre(a_pre);
		
		b->setNext(a);
		a->setPre(b);

		if (b_next != nullptr) 
			b_next->setPre(a);

		a->setNext(b_next);

		if (list == a) 
			list = b;
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
