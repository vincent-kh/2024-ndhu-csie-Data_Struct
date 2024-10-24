#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random>
#include<algorithm>
#include<vector>
#include<queue>
#include <iomanip>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid
{
public:
    int weight;
    Grid()
    {
        Grid(0);
        weight = 0;
    }
    Grid(int s)
    {
        state = s;
        weight = s?-1:0;
        dir[UP] = NULL;
        dir[DOWN] = NULL;
        dir[LEFT] = NULL;
        dir[RIGHT] = NULL;
    }
    Grid *getDir(int d) { return dir[d]; }
    int getState() { return state; }
    void setDir(int d, Grid *g, bool st = 1)
    {
        dir[d] = g;
        if (st)
        {
            g->setDir(d ^ 1, this, 0);
        }
    }
    int get_way()
    {
        int c=0;
        for(int i=0;i<4;i++)
        {
            if(dir[i]!=NULL)
                c++;
        }
        return c;
    }
    void setState(int s) { state = s; }
private:
    Grid *dir[4];
    int state;
};

struct List
{
public:
    List()
    {
        top = 0;
    }

    void addElement(Grid *g)
    {
        if (top < SIZE * SIZE)
        {
            data[top++] = g;
        }
    }

    Grid *removeElement()
    {
        if (top > 0)
        {
            return data[--top];
        }
        return NULL;
    }
    void printPath()
    {
        int j;
        for (j = 1; j < top; j++)
        {
            if (data[j] == data[j - 1]->getDir(UP))
            {
                cout << "UP\n";
            }
            else if (data[j] == data[j - 1]->getDir(DOWN))
            {
                cout << "DOWN\n";
            }
            else if (data[j] == data[j - 1]->getDir(LEFT))
            {
                cout << "LEFT\n";
            }
            else if (data[j] == data[j - 1]->getDir(RIGHT))
            {
                cout << "RIGHT\n";
            }
        }
    }
    void reverse()
	{
		int i;
		for(i = 0;i < top / 2;i ++)
		{
			auto tmp = data[i];
			data[i] = data[top - i - 1];
			data[top - i - 1] = tmp;
		}
	}
private:
    Grid *data[SIZE * SIZE];
    int top;
};

class Maze
{
public:
    Maze()
    {
        initMaze(SIZE);
        s = SIZE;
    }

    vector<int> rand_gen(int s, float p)
    {
        vector<int> v(s * s, 0);
        int c = s * s * p;
        fill(v.begin() + 1, v.begin() + c + 1, 1);
        shuffle(v.begin() + 1, v.end() - 1, default_random_engine(time(NULL)));
        return v;
    }

    void initMaze(int s)
    {
        vector<int> v = rand_gen(s, 0.2);
        int c = 0;
        maze = new Grid(v[c++]);
        Grid *cur2 = maze, *cur = cur2;
        Grid *prevRowStart = maze;
        Grid *prev = NULL;

        for (int j = 0; j < s; j++)
        {
            if (j != 0)
            {
                cur2->setDir(DOWN, new Grid(v[c++]));
                prevRowStart = cur2;
                cur2 = cur2->getDir(DOWN);
            }
            cur = cur2;
            prev = prevRowStart;
            
            for (int i = 1; i < s; i++) 
            {
                cur->setDir(RIGHT, new Grid(v[c++]));
                if (j != 0)
                {
                    cur->setDir(UP, prev);
                }
                prev = prev ? prev->getDir(RIGHT) : NULL;
                cur = cur->getDir(RIGHT);
            }

            if (j != 0 && prev != NULL)
                cur->setDir(UP, prev);
        }
        end = cur;
    }

    bool updateBFS()
    {
        queue<Grid*> q;
        maze->weight = 1;
        q.push(maze);

        int dir[4] = {UP, DOWN, LEFT, RIGHT};
        while (!q.empty())
        {
            Grid *current = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                Grid *nex = current->getDir(dir[i]);
                if (nex != NULL && nex->weight == 0)
                {
                    nex->weight = current->weight + 1;
                    q.push(nex);

                    if (nex==end)
                        return true;
                }
            }
        }
        return false;
    }

    List *getPath()
    {
        List* path=new List();
        if(!updateBFS())
            return path;
        Grid* current = end;
        while (current != NULL && current->weight != 1)
        {
            path->addElement(current);
            for (int i = 0; i < 4; i++)
            {
                Grid* prev = current->getDir(i);
                if (prev != NULL && prev->weight == current->weight - 1)
                {
                    current = prev;
                    break;
                }
            }
        }
        path->addElement(maze);
        path->reverse();
        return path;
    }

    void printMaze()
    {
        Grid *j = maze, *k;
        while (j != NULL)
        {
            k = j;
            while (k != NULL)
            {
                cout << k->getState();
                k = k->getDir(RIGHT);
            }
            cout << endl;
            j = j->getDir(DOWN);
        }
    }

    void print_way()
    {
        Grid *j = maze, *k;
        while (j != NULL)
        {
            k = j;
            while (k != NULL)
            {
                cout << k->get_way();
                k = k->getDir(RIGHT);
            }
            cout << endl;
            j = j->getDir(DOWN);
        }
    }

    void printBFS()
    {
        Grid *j = maze, *k;
        while (j != NULL)
        {
            k = j;
            while (k != NULL)
            {
                cout <<setw(2)<< k->weight<<' ';
                k = k->getDir(RIGHT);
            }
            cout << endl;
            j = j->getDir(DOWN);
        }
    }

private:
    Grid *maze,*end;
    int s;
};

int main()
{
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printPath();
}
