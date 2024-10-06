#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
public:
    Queue()
    {
        top = 0;
        bot = 0;
    }
    int enqueue(int dt)
    {
        if(top == SIZE-1)
        {
            if(bot == 0)
                return -1;
            else
                top = 0;
        }
        data[top] = dt;
        top++;
        return 1;
    }
    int *dequeue()
    {
        if(bot == top)
            return NULL;
        auto addr=&data[bot];
        if(bot == SIZE-1)
            bot = 0;
        else
            bot++;
        return addr;
    }
private:
    int data[SIZE];
    int top, bot;
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(queue->enqueue(data) == 1)
            {
                cout<<"Successfully enqueue data "<<data<<" into queue."<<endl;
            }
            else
            {
                cout<<"Failed to enqueue data into queue."<<endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout<<"Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout<<"Dequeue data "<<*temp<<" from queue."<<endl;
            }
        }
    }
}
