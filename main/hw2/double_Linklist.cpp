#include<iostream>
using namespace std;

template<class T>


class DLinklist
{
public:
    class Node
    {
    public:
        Node(T d):data(d),next(nullptr),pre(nullptr){}
        T data;
        Node *next,*pre;
    };

    DLinklist():head(nullptr),back(nullptr),s(0){}
    ~DLinklist()
    {
        while(!isEmpty())
        {
            removeHeadElement();
        }
    }
    bool isEmpty()
    {
        return s==0;
    }
    const Node* getHead()
    {
        return head;
    }
    const Node* getTail()
    {
        return back;
    }
    void addElement_front(T d)
    {
        Node* n=new Node(d);
        if(isEmpty())
        {
            head=n;
            back=n;
        }
        else
        {
            n->next=head;
            head->pre=n;
            head=n;
        }
        s++;
    }

    void addElement_back(T d)
    {
        Node* n=new Node(d);
        if(isEmpty())
        {
            head=n;
            back=n;
        }
        else
        {
            n->pre=back;
            back->next=n;
            back=n;
        }
        s++;
    }

    void removeHeadElement()
    {
        if(isEmpty())
        {
            cout<<"List is empty"<<endl;
            return;
        }
        Node* temp=head;
        head=head->next;
        delete temp;
        s--;
    }

    void removeTailElement()
    {
        if(isEmpty())
        {
            cout<<"List is empty"<<endl;
            return;
        }
        Node* temp=back;
        back=back->pre;
        delete temp;
        s--;
    }

    void display()
    {
        if(isEmpty())
        {
            cout<<"List is empty"<<endl;
            return;
        }
        Node* temp=head;
        while(temp!=nullptr)
        {
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }

    int size()
    {
        return s;
    }

    
private:
    Node *head,*back;
    int s;
};
int main()
{
    DLinklist<int> l;
    string commend;
    int d;
    while (1)
    {
        cout<<"Enter commend: ";
        cin>>commend;
        if(commend=="add")
        {
            cin>>commend;
            if(commend=="front")
            {
                cin>>d;
                l.addElement_front(d);
            }
            else if(commend=="back")
            {
                cin>>d;
                l.addElement_back(d);
            }
            else
            {
                cout<<"Invalid commend"<<endl;
            }
        }
        else if(commend=="remove")
        {
            cin>>commend;
            if(commend=="head")
            {
                l.removeHeadElement();
            }
            else if(commend=="tail")
            {
                l.removeTailElement();
            }
            else
            {
                cout<<"Invalid commend"<<endl;
            }
        }
        else if(commend=="display")
        {
            l.display();
        }
        else if(commend=="size")
        {
            cout<<"Size: "<<l.size()<<endl;
        }
        else if(commend=="exit")
        {
            break;
        }
        else
        {
            cout<<"Invalid commend"<<endl;
        }
    }
    delete &l;
    return 0;
}