#include <iostream>
#include <cmath>

using namespace std;

template<class T>
class BinaryTreeInArray 
{
private:
    T *array;
    int height;
    int numOfElement;
    
    void resize(int size) 
    {
        T *temp = new T[numOfElement];
        int j;
        for(j = 0;j < numOfElement;j ++)
            temp[j] = array[j];
        delete array;
        array = new T[static_cast<int>(pow(2, height + 1)) - 1];
        for(j = 0;j < numOfElement;j ++)
            array[j] = temp[j];
        height ++;
        delete temp;
    }
public:
    BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0) {}
    void addElementAsCompleteTree(T data) 
    {
        int cap = pow(2, height) - 1;
        if(numOfElement + 1 > cap)
            resize((cap + 1) * 2 - 1);
        array[numOfElement] = data;
        numOfElement ++;
    }
    
    int get_p(int index)            {return (index - 1) / 2;}

    int get_s(int index,bool lr)    {return 2*index+1+lr;}
    
    void displayInorder(int index=0) 
    {
        if(index>=numOfElement)
            return;
        displayInorder(get_s(index,0));
        cout<<array[index]<<' ';
        displayInorder(get_s(index,1)); 
    }
    
    void displayPreorder(int index=0) 
    {
        if(index>=numOfElement)
            return;
        cout<<array[index]<<' ';
        displayPreorder(get_s(index,0));
        displayPreorder(get_s(index,1)); 
    }
    
    void displayPostorder(int index=0) 
    {
        if(index>=numOfElement)
            return;
        displayPostorder(get_s(index,0));
        displayPostorder(get_s(index,1));
        cout<<array[index]<<' ';
    }
};

int main()
{
    BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
    int j, n;
    cin >> n;
    for(j = 0;j < n;j ++) {
        b->addElementAsCompleteTree(j);
    }
    b->displayInorder();
    cout << endl;
    b->displayPreorder();
    cout << endl;
    b->displayPostorder();
    cout << endl;
    return 0;
}
