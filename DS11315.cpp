#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include<algorithm>
using namespace std;

//design your won SuffixTreeNode using in SuffixTree
class SuffixTreeNode 
{
public:
    SuffixTreeNode(const string &text):text(text){}
    string text;
    vector<SuffixTreeNode*> child; 
    SuffixTreeNode* find(string s)
    {
        for(auto n:child)
            if(n->text==s)
                return n;
        return nullptr;
    }
    ~SuffixTreeNode()
    {
        for(auto n:child)
            delete n;
    }
};

class SuffixTree {
private:
    SuffixTreeNode *root;
    string text;
public:
    SuffixTree(string text) : text(text) 
    {
        root = new SuffixTreeNode("");
        for(int i=0;i<static_cast<int>(text.size());i++)
        {
            string subs=text.substr(i)+"$";
            SuffixTreeNode* subn = root;
            for(char c:subs)
            {
                string subs_c(1, c);
                subn = build(subn, subs_c);
            }     
        }
        //compress(root);
        
    }
    SuffixTreeNode* build(SuffixTreeNode* node,string ch)
    {
        auto subn=node->find(ch);
        if(subn==nullptr)
        {
            subn=new SuffixTreeNode(ch);
            node->child.push_back(subn);
        }
        return subn;
    }
    
    void compress(SuffixTreeNode* node)
    {
        if(node->child.size()==1)
        {
            SuffixTreeNode* child=node->child[0];
            node->text+=child->text;
            node->child=child->child;
            compress(node);
        }
        else
        {
            for(auto n:node->child)
                compress(n);
        }
    }
    bool exist(const string &substring) 
    {
        SuffixTreeNode* subn = root;
        for(char c:substring)
        {
            string subs_c(1, c);
            subn = subn->find(subs_c);
            if(subn==nullptr)
                return false;
        }
        return true;   
    }
        

    int count(const string &substring) 
    {
        int count = 0;
        size_t pos = text.find(substring);
        while(pos != string::npos)
        {
            count++;
            pos = text.find(substring, pos + 1);
        }
        return count;
    }

    ~SuffixTree() 
    {
        delete_r(root);
    }

    void print_r()
    {
        print(root,0);
    }
    void print(SuffixTreeNode* node,int level)
    {
        for(int i=0;i<level;i++)
            cout<<" ";
        cout<<node->text<<endl;
        for(auto n:node->child)
            print(n,level+1);
    }

    void delete_r(SuffixTreeNode* node)
    {
        for(auto n:node->child)
            delete_r(n);
        delete node;
    }
};

int main() {
    
    string text = "";
    while(true) {
      string temp;
      getline(cin, temp);
      if(temp == "")
        break;
      text += temp;
    }
    SuffixTree tree(text);
    //tree.print_r();
    string query;
    while(true) {
      getline(cin, query);
      if(query == "")
        break;
      cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << endl;
      cout << "Count of '" << query << "': " << tree.count(query) << endl;
    }

    return 0;
}
