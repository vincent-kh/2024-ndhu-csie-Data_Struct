#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class TrieNode
{
public:
    TrieNode(string s)
    {
        value = s;
    }
    vector<TrieNode*> children;
    string value;
    TrieNode* find(string s)
    {
        for(auto n:children)
            if(n->value == s)
                return n;
        return nullptr;
    }
};

class Trie
{
public:
	/*
	construct a Trie.
	*/
	Trie()
    {
        root = new TrieNode("[]");
    }
	/*
	search trie for key, return true if exist, false if not.
	*/
	bool search(string key)
    {
        TrieNode* node = root;
        key+="$";
        for(int i=0;i<static_cast<int>(key.size());i++)
        {
            string subs = key.substr(i,1);
            TrieNode* subn = node->find(subs);
            if(subn == nullptr)
                return false;
            node = subn;
        }
        return true;
    }
	/*
	insert value into trie.
	*/
	void insert(string value)
    {
        TrieNode* node = root;
        value+="$";
        for(int i=0;i<static_cast<int>(value.size());i++)
        {
            string subs = value.substr(i,1);
            TrieNode* subn = node->find(subs);
            if(subn == nullptr)
            {
                subn = new TrieNode(subs);
                node->children.push_back(subn);
            }
            node = subn;
        }
    }
	/*
	display trie in pre-order, each element in a line, display space befoer element base on the level of 	the element. level 1 for 2 space, level 2 for 4 space, level 3 for 6 space and so on, root is level 	0.
	*/
	void preorder()
    {
        preorder_r(root,0);
    }
private:
    TrieNode *root;
    bool single_child(TrieNode* node)
    {
        return node->children.size()==1 && (node->children[0]->children.size()<2 || (node->children[0]->children.size()==2 && node->children[0]->find("$")!=nullptr));
    }
    void preorder_r(TrieNode *node, int level,bool space=true)
    {
        
        if(node->value == "$")
            return;
        if(space)
        for(int i=0;i<level;i++)
            cout<<"  ";
        cout<<node->value;
        for(int i=0;i<static_cast<int>(node->children.size());i++)
        {
            if(single_child(node))
            {
                preorder_r(node->children[i],level,false);
            }
            else
            {
                cout<<endl;
                preorder_r(node->children[i],level+1);
            }
        }
    }
};

int main()
{
	Trie *trie = new Trie();
	string command, key, value;
	while(1)
	{
		cin>>command;
		if(command == "insert")
		{
			cin>>value;
			trie->insert(value);
		}
		else if(command == "search")
		{
			cin>>key;
			if(trie->search(key))
				cout << "exist" << endl;
			else
				cout << "not exist" << endl;
		}
		else if(command == "print")
		{
			trie->preorder();
		}
		else if(command == "exit")
		{
			break;
		}
	}
}
