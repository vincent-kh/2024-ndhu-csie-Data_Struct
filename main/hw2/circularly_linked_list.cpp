#include<iostream>
using namespace std;

template<class T>
class CLinklist
{
public:
    class Node
    {
    public:
        Node(T d):data(d),next(nullptr){}
        T data;
        Node* next; 
    };

    CLinklist():head(nullptr){}

    bool isEmpty()
    {
        return head==nullptr;
    }

    void addElement(T d)
    {
        Node* n=new Node(d);
        if(isEmpty())
        {
            head=n;
            n->next=head;
        }
        else
        {
            Node* temp=head;
            while(temp->next!=head)
            {
                temp=temp->next;
            }
            temp->next=n;
            n->next=head;
        }
    }

    void removeTailElement()
    {
        if(isEmpty())
        {
            cout<<"List is empty"<<endl;
            return;
        }
        Node* temp=head;
        while(temp->next->next!=head)
        {
            temp=temp->next;
        }
        delete temp->next;
        temp->next=head;
    }

    int size()
    {
        int s=0;
        if(isEmpty())
        {
            return s;
        }
        Node* temp=head;
        do
        {
            s++;
            temp=temp->next;
        }while(temp!=head);
        return s;
    }

    void display()
    {
        if(isEmpty())
        {
            cout<<"List is empty"<<endl;
            return;
        }
        Node* temp=head;
        do
        {
            cout<<temp->data<<" ";
            temp=temp->next;
        }while(temp!=head);
    }

private:
    Node *head;
};

int main()
{
    CLinklist<int> l;
    for(int i=0; i<10; i++)
    {
        l.addElement(i);
    }
    cout << "Size: " << l.size() << endl;
    l.display();
    cout << endl;
    
    l.removeTailElement();
    cout << "Size after removing tail: " << l.size() << endl;
    l.display();
    cout << endl;

    return 0;
}
