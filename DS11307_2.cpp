#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include <queue>

#define SIZE 15

using namespace std;

class Node
{
public:
	Node()
	{
		Node(0, 0);
	}
	Node(int r, int c)
	{
		row = r;
		col = c;
	}
	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int r)
	{
		if(r >= 0 && r < SIZE)
			row = r;
	}
	void setCol(int c)
	{
		if(c >= 0 && c < SIZE)
			col = c;
	}
private:
	int col, row;
};

class List
{
public:
	List()  {top = 0;}
	void addElement(int r, int c)   {data[top++]=Node(r,c);}
	Node *removeElement()	{return top ? &data[--top] : NULL;}
	void printList()
	{
		int j;
		for(j = 0;j < top;j ++)
		{
			cout<<"("<<data[j].getRow()<<", "<<data[j].getCol()<<")"<<endl;
		}
	}

	void reverse()
	{
		int i;
		for(i = 0;i < top / 2;i ++)
		{
			Node tmp = data[i];
			data[i] = data[top - i - 1];
			data[top - i - 1] = tmp;
		}
	}
private:
	Node data[SIZE * SIZE];
	int top;
};

class Maze
{
public:
	Maze()	{initMaze(SIZE);}

	void initMaze(int s)
	{
        maze = (int**)malloc(s*sizeof(int*));
		bfs = (int**)malloc(s*sizeof(int*));
        for(int i=0;i<s;i++)
		{
            maze[i]=(int*)calloc(s,sizeof(int));
			bfs[i]=(int*)calloc(s, sizeof(int));
		}
        int walls=s*s*0.2;
        for(int i=0;i<walls;)
        {
			int v=rand();
			int r=v%10,c=(v/10)%10;
			if(!maze[r][c] && (r!=0 && c!=0))
			{
				maze[r][c] = 1;
				bfs[r][c]=-1;
				i++;
			}
		}
				
        maze[0][0]=0;
        maze[s-1][s-1]=0;
		bfs[0][0]=0;
		bfs[s-1][s-1]=0;
	}

	List* getPath()
	{
		List* path = new List();
		if (!updateBFS())
			return path;
		int r = SIZE - 1, c = SIZE - 1;
		while (r != 0 || c != 0)
		{
			path->addElement(r, c);
			if (r > 0 && bfs[r - 1][c] == bfs[r][c] - 1)			r--;
			else if (r < SIZE-1 && bfs[r + 1][c] == bfs[r][c] - 1)	r++;
			else if (c > 0 && bfs[r][c - 1] == bfs[r][c] - 1)		c--;
			else if (c < SIZE-1 && bfs[r][c + 1] == bfs[r][c] - 1)	c++;
		}
		path->addElement(0, 0);
		path->reverse();
		return path;
	}
	
    void printMaze()
	{
		int j, k;
		for(j = 0;j < SIZE;j ++)
		{
			for(k = 0;k < SIZE;k ++)
			{
				if(maze[j][k] == 0)
					cout<<" ";
				else if(maze[j][k] == 1)
					cout<<"*";
			}
			cout<<"\n";
		}
	}

	void printBFS()
	{
		int j, k;
		for(j = 0;j < SIZE;j ++)
		{
			for(k = 0;k < SIZE;k ++)
				cout<<setw(2)<<bfs[j][k]<<" ";
			cout<<"\n";
		}
	}
	bool updateBFS()
	{
		queue<Node> q;
		q.push(Node(0, 0));
		bfs[0][0] = 1;

		int dir[4]={1,-1,0,0};
		while (!q.empty())
		{
			Node current = q.front();
			q.pop();
			int r = current.getRow();
			int c = current.getCol();

			for (int i = 0; i < 4; i++)
			{
				int newRow = r + dir[i];
				int newCol = c + dir[3-i];

				if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && !bfs[newRow][newCol] && !maze[newRow][newCol])
				{
					bfs[newRow][newCol] = bfs[r][c] + 1;
					q.push(Node(newRow, newCol));

					if (newRow == SIZE - 1 && newCol == SIZE - 1)
						return true;
				}
			}
		}
		return false;
	}
private:
	int **maze,**bfs;
};

int main()
{
	srand(time(NULL));
    Maze *maze = new Maze();
	maze->printMaze();
	
	maze->getPath()->printList();
	maze->printBFS();
}
