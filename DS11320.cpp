#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <cstdio>
#include <iomanip>

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
	friend std::ostream &operator<<(std::ostream &out, Node n)
	{
		out<<*(n.data);
		return out;
	}
	friend std::ostream &operator<<(std::ostream &out, Node *n)
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
class ListNode : public Node<T>
{
public:
	ListNode() : Node<T>()
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(T d) : Node<T>(d)
	{
		prev = NULL;
		next = NULL;
	}
	ListNode(ListNode *p, ListNode *n) : Node<T>()
	{
		prev = p;
		next = n;
	}
	ListNode(T d, ListNode *p, ListNode *n) : Node<T>(d)
	{
		prev = p;
		next = n;
	}
	ListNode *getNext() const
	{
		return next;
	}
	ListNode *getPrev() const
	{
		return prev;
	}
	void setNext(ListNode *n)
	{
		next = n;
	}
	void setPrev(ListNode *p)
	{
		prev = p;
	}
	ListNode &operator=(T d)
	{
		this->setData(d);
		return *this;
	}
private:
	ListNode *prev, *next;
};

template<class T>
class LinkList
{
public:
	LinkList()
	{
		head = NULL;
		tail = NULL;
        size = 0;
	}
	void addFromHead(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(head != NULL)
		{
			head->setPrev(node);
		}
		node->setNext(head);
		head = node;
		if(tail == NULL)
			tail = node;
        size ++;
	}
	void addFromTail(T d)
	{
		ListNode<T> *node = new ListNode<T>(d);
		if(tail != NULL)
		{
			tail->setNext(node);
		}
		node->setPrev(tail);
		tail = node;
		if(head == NULL)
			head = node;
        size ++;
	}
	void addAfter(ListNode<T> *at, T d)
	{
		if(!exist(at))
			return;
		ListNode<T> *node = new ListNode<T>(d);
		if(at->getNext() != NULL)
			at->getNext()->setPrev(node);
		node->setNext(at->getNext());
		at->setNext(node);
		node->setPrev(at);
		if(node->getNext() == NULL)
			tail = node;
        size ++;
	}
	ListNode<T> *removeFromHead()
	{
		ListNode<T> *n = head;
		if(head != NULL)
		{
			head = head->getNext();
			if(head != NULL)
				head->setPrev(NULL);
			else
				tail = NULL;
			n->setNext(NULL);
		}
        size --;
		return n;
	}
	ListNode<T> *removeFromTail()
	{
		ListNode<T> *n = tail;
		if(tail != NULL)
		{
			tail = tail->getPrev();
			if(tail != NULL)
				tail->setNext(NULL);
			else
				head = NULL;
			n->setPrev(NULL);
		}
        size --;
		return n;
	}
	ListNode<T> *remove(ListNode<T> *n)
	{
		if(!exist(n))
			return NULL;
		if(n == head)
			return removeFromHead();
		if(n == tail)
			return removeFromTail();
		n->getPrev()->setNext(n->getNext());
		n->getNext()->setPrev(n->getPrev());
		n->setNext(NULL);
		n->setPrev(NULL);
        size --;
		return n;
	}
	ListNode<T> *exist(T d)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j->getData() == d)
				return j;
			j = j->getNext();
		}
		return NULL;
	}
	bool exist(ListNode<T> *n)
	{
		ListNode<T> *j = head;
		while(j != NULL)
		{
			if(j == n)
				return true;
			j = j->getNext();
		}
		return false;
	}
	ListNode<T> &operator[](int i) const
	{
		ListNode<T> *j = head;
		int k;
		for(k = 0;k < i && j != NULL;k ++)
			j = j->getNext();
		if(j == NULL)
			throw std::invalid_argument("index does not exist.");
		return *j;
	}
	void print() const
	{
		ListNode<T> *j;
		j = head;
		while(j != NULL)
		{
			std::cout<<(*j)<<" ";
			j = j->getNext();
		}
		std::cout<<std::endl;
	}
    void swap(ListNode<T> *a, ListNode<T> *b)
    {
        if(!exist(a) || !exist(b))
            return;
        T temp = a->getData();
        a->setData(b->getData());
        b->setData(temp);
    }
    void sort()
    {
        ListNode<T> *i, *j;
        for(i = head;i != NULL;i = i->getNext())
        {
            for(j = i->getNext();j != NULL;j = j->getNext())
            {
				if(i->getData()->getData() > j->getData()->getData())
                {
                    swap(i, j);
                }
            }
        }
    }
    
public:
	ListNode<T> *getHead() const
	{
		return head;
	}
    size_t getSize() const
    {
        return size;
    }
protected:
	ListNode<T> *head, *tail;
    int size;
};

template<class V, class E>
class WeightedGraphEdge;

template<class V, class E>
class WeightedGraphVertex : public Node<V>
{
public:
	WeightedGraphVertex() :Node<V>()
	{
		list = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	WeightedGraphVertex(V d) :Node<V>(d)
	{
		list = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	void addEdge(WeightedGraphEdge<V, E> *edge)
	{
		list->addFromTail(edge);
	}
	void remove(WeightedGraphEdge<V, E> *node)
	{
	}
	ListNode<WeightedGraphEdge<V, E> *> *operator[](int n)
	{
		try
		{
			return (&(*list)[n]);
		}
		catch(std::invalid_argument e)
		{
			return NULL;
		}
	}
    LinkList<WeightedGraphEdge<V, E> *> *getEdgeList()
    {
        return list;
    }
private:
	LinkList<WeightedGraphEdge<V, E> *> *list;
};

template<class V, class E>
class WeightedGraphEdge : public Node<E>
{
public:
	WeightedGraphEdge() : Node<E>()
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeightedGraphEdge(E d) : Node<E>(d)
	{
		end[0] = NULL;
		end[1] = NULL;
	}
	WeightedGraphEdge(E d, WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2) : Node<E>(d)
	{
		end[0] = v1;
		end[1] = v2;
	}
	WeightedGraphVertex<V, E> *&getAnotherEnd(WeightedGraphVertex<V, E> *v)
	{
		if(v != end[0])
			return end[0];
		return end[1];
	}
private:
	WeightedGraphVertex<V, E> *end[2];
};

template<class V, class E>
class WeightedGraph
{
public:
	WeightedGraph()
	{
		vertex = new LinkList<WeightedGraphVertex<V, E> *>();
		edge = new LinkList<WeightedGraphEdge<V, E> *>();
	}
	WeightedGraphVertex<V, E> *operator[](int n)
	{
		try
		{
			return (*vertex)[n].getData();
		}
		catch(std::invalid_argument e)
		{
			return NULL;
		}
	}
	void addLink(WeightedGraphVertex<V, E> *v1, WeightedGraphVertex<V, E> *v2, E w)
	{
		/*if(v1 == v2)    return;
        for(size_t i = 0;i < v1->getEdgeList()->getSize();i ++)
        {
            auto e = (*v1->getEdgeList())[i];
            if(e.getData()->getAnotherEnd(v1) == v2)
            {
                if(w<e.getData()->getData())
                    e.getData()->setData(w);
                return;
            }
        }*/
        WeightedGraphEdge<V, E> *edge = new WeightedGraphEdge<V, E>(w, v1, v2);
		v1->addEdge(edge);
		if(v1 != v2)
			v2->addEdge(edge);
	}
	WeightedGraphVertex<V, E> *addVertex(V d)
	{
		WeightedGraphVertex<V, E> *v = new WeightedGraphVertex<V, E>(d);
		vertex->addFromTail(v);
		return v;
	}
	void BFS(WeightedGraphVertex<V, E> *v)
	{
        LinkList<WeightedGraphVertex<V, E> *> *queue = new LinkList<WeightedGraphVertex<V, E> *>();
        LinkList<WeightedGraphVertex<V, E> *> *visited = new LinkList<WeightedGraphVertex<V, E> *>();
        queue->addFromTail(v);
        while(queue->getHead() != NULL)
        {
            WeightedGraphVertex<V, E> *u = queue->removeFromHead()->getData();
            if(visited->exist(u))
                continue;
            visited->addFromTail(u);
            cout<<u->getData()<<" ";
            for(size_t i = 0;i < u->getEdgeList()->getSize();i ++)
            {
                WeightedGraphEdge<V, E> *e = (*u->getEdgeList())[i].getData();
                WeightedGraphVertex<V, E> *w = e->getAnotherEnd(u);
                if(!visited->exist(w))
                    queue->addFromTail(w);
            }
        }
	}
	void DFS(WeightedGraphVertex<V, E> *v)
	{
        LinkList<WeightedGraphVertex<V, E> *> *stack = new LinkList<WeightedGraphVertex<V, E> *>();
        LinkList<WeightedGraphVertex<V, E> *> *visited = new LinkList<WeightedGraphVertex<V, E> *>();
        stack->addFromHead(v);
        while(stack->getHead() != NULL)
        {
            WeightedGraphVertex<V, E> *u = stack->removeFromHead()->getData();
            if(visited->exist(u))
                continue;
            visited->addFromTail(u);
            cout<<u->getData()<<" ";
            for(size_t i = 0;i < u->getEdgeList()->getSize();i ++)
            {
                WeightedGraphEdge<V, E> *e = (*u->getEdgeList())[i].getData();
                WeightedGraphVertex<V, E> *w = e->getAnotherEnd(u);
                if(!visited->exist(w))
                    stack->addFromHead(w);
            }
        }
	}
    void print_graph()
    {
        for(size_t i = 0;i < vertex->getSize();i ++)
        {
            WeightedGraphVertex<V, E> *v = (*vertex)[i].getData();
            cout<<v->getData()<<": ";
            //v->getEdgeList()->sort();
            for(size_t j = 0;j < v->getEdgeList()->getSize();j ++)
            {
                WeightedGraphEdge<V, E> *e = (*v->getEdgeList())[j].getData();
                cout<<e->getAnotherEnd(v)->getData()<<"("<<e->getData()<<") ";
            }
            cout<<endl;
        }
    }
    void print_graph_matrix()
    {
        size_t n = vertex->getSize();
        E **matrix = new E*[n];
        for(size_t i = 0;i < n;i ++)
        {
            matrix[i] = new E[n];
            for(size_t j = 0;j < n;j ++)
                matrix[i][j] = 0;
        }
        for(size_t i = 0;i < n;i ++)
        {
            WeightedGraphVertex<V, E> *v = (*vertex)[i].getData();
            for(size_t j = 0;j < v->getEdgeList()->getSize();j ++)
            {
                WeightedGraphEdge<V, E> *e = (*v->getEdgeList())[j].getData();
				matrix[i][e->getAnotherEnd(v)->getData() - 'A'] = e->getData();
            }
        }
        cout<<"    ";
        for(size_t i = 0;i < n;i ++)
        {
            cout << setw(3) << (char)(i+65) << " ";
        }
        cout<<endl;
        for(size_t i = 0;i < n;i ++)
        {
            for(size_t j = 0;j < n;j ++)
            {
                if(j == 0)
					cout << setw(3) << (char)(i + 65) << " ";
                if(matrix[i][j] == 0)
                    cout << "  - ";
                else
                    cout << setw(3) << matrix[i][j]<< " ";
            }
            cout<<endl;
        }
    }
private:
	LinkList<WeightedGraphVertex<V, E> *> *vertex;
	LinkList<WeightedGraphEdge<V, E> *> *edge;
};



int main()
{
    WeightedGraph<char, int> *g = new WeightedGraph<char, int>();
    LinkList<WeightedGraphVertex<char, int> *> *node = new LinkList<WeightedGraphVertex<char, int> *>();
    int j, k, n, a, b, w;
    scanf("%d", &n);
    srand(n);
    for(j = 0;j < 26;j ++)
        node->addFromTail(g->addVertex(j + 'A'));
    k = rand() % 100;
    for(j = 0;j < k;j ++)
    {
        a = rand() % 26;
        b = rand() % 26;
        w = rand() % 100;
        g->addLink(((*node)[a]).getData(), ((*node)[b]).getData(), w);
    }
    /*g->print_graph();
    cout<<endl;
    g->print_graph_matrix();
    cout<<endl;*/
    g->BFS((*node)[rand() % 26].getData());
    cout<<endl;
    g->DFS((*node)[rand() % 26].getData());
	return 0;
}
