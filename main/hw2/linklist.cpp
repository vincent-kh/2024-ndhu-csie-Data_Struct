#include<iostream>
using namespace std;

template<class T>


class Linklist
{
public:
    class Node
    {
    public:
        Node(T d):data(d),next(nullptr){}
        T data;
        Node* next;
    };

    Linklist():head(nullptr),s(0){}
    Node* addElement(T d)
    {
        Node* temp = new Node(d);
        if (head == nullptr)
        {
            head = temp;
        }
        else
        {
            Node* cur = head;
            while (cur->next != nullptr)
            {
                cur = cur->next;
            }
            cur->next = temp;
        }
        s++;
        return temp;
    }
    
    void removeTailElement()
    {
        if (head == nullptr)
        {
            return;
        }
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            s--;
            return;
        }
        Node* cur = head;
        while (cur->next->next != nullptr)
        {
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
        s--;
    }

    void display()
    {
        Node* cur=head;
        while (cur!=nullptr)
        {
            cout<<cur->data<<' ';
            cur=cur->next;
        }
    }

    int size()  {return s;}
private:
    Node* head;
    int s;
};
int main()
{
    Linklist<int> l;
    for(int i=0;i<10;i++)
    {
        l.addElement(i);
    }
    cout<<l.size()<<endl;
    l.display();
    cout<<endl;
    l.removeTailElement();
    cout<<l.size()<<endl;
    l.display();
    cout<<endl;
    
    return 0;
}