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
    ~Linklist()
    {
        while (head!=nullptr)
            remove_Head();  
    }
    Node* add_Tail(T d)
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
    Node* add_Head(T d)
    {
        Node* temp = new Node(d);
        if (head == nullptr)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
        s++;
        return temp;
    }
    void remove_Tail()
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
    void remove_Head()
    {
        if (head == nullptr)
        {
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
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
    bool isEmpty() {return s==0;}
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
        l.add_Tail(i*2);
        l.add_Head(i*2+1);
    }
    cout<<l.size()<<endl;
    l.display();
    cout<<endl;
    l.remove_Tail();
    cout<<l.size()<<endl;
    l.display();
    cout<<endl;
    
    return 0;
}