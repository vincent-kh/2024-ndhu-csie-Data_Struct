#include <iostream>
using namespace std;

class Frog
{
    public:
    Frog(int x, int y):x(x),y(y){}
    void moveLeft()
    {
        x--;
    }
    void moveRight()
    {
        x++;
    }
    void moveUp()
    {
        y++;
    }
    void moveDown()
    {
        y--;
    }
    int getCurrentPositionX()
    {
        return x;
    }
    int getCurrentPositionY()
    {
        return y;
    }
    private:
    int x,y;
};

int main()
{
    int x,y,x2,y2;
    cin>>x>>y>>x2>>y2;
    Frog frog(x,y);
    while(frog.getCurrentPositionX() != x2)
    {
        frog.getCurrentPositionX() < x2 ? frog.moveRight() : frog.moveLeft();
    }
    while(frog.getCurrentPositionY() != y2)
    {
        frog.getCurrentPositionY() < y2 ? frog.moveUp() : frog.moveDown();
    }
    return 0;
}