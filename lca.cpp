/*
Least Common Ancestor
Given an n-ary tree, find the LCA of three values.
There are no repeated values in the tree
node {
    int val;
    list<node&> children;
}
                                4
                             / / \ \
                            2 16 7 8
                           /\
                         100 5
                         / \
                        121 1

Nodes              LCA
100, 5, 1           2
100, 5, 121         2
100, 5 ,2           4
4, 121, 5           null
100, 5, 2000        null

node& findLCA(const node &root, unordered_set<int> &values )
{
    for( auto &child : root->children) {
        if( values.find(child->val) != values.end() )
        {
            values.remove(child->val);
        }
    }
    
    if(values.empty()) 
    {
        return root;
    }

    int count = 0;
    node lca;
    for( auto &child : root->children) {
        lca = findLCA(child, values);
        if (lca) count++;
          
        if(values.empty()) {
            break;
        }
    }

    if (count == 0) return nullptr;
    if (count == 1) return lca;
    return root;
}

node findLCA(int a, int b, int c, const node &root) {
    unordered_set<int> &values {a,b,c};
    if (values.find(root->val) != values.end()) return nullptr;
    return findLCA(root, values);
}

*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <optional>
#include <queue>

using namespace std;

struct node {
  int val;
  vector<node*> children;
};

pair<node*, int> findLCA( node *root, unordered_set<int> &values )
{
  int total = 0;
  for(auto child : root->children) {
    auto [n ,c] = findLCA(child, values);
    if (n) return {n,c};
    total += c;
  }

  if (total == values.size())  return {root,total};

  if (values.find(root->val) != values.end()) total++;
  
  return {nullptr,total};
}

node* buildTree(vector<int> &values)
{
  deque<node *> dq;

  node *root = new node { values[0], {} };
  dq.push_back(root);
  
  for(int i=1; i < values.size(); ++i)
  {
    cout << values[i] << endl;
    if (values[i] == -1) { dq.pop_front(); if (dq.empty()) break; continue; }
    node * r = dq.front();
    cout << r->val << " is the top" << endl;
    node *child = new node { values[i], {} };
    r->children.push_back(child);
    dq.push_back(child);
  }
  cout << "++++++" << endl;
  return root;
}

void printTree(const node* root)
{
  cout << root->val <<" : ";
  for(auto c : root->children) cout << c->val << " "; cout << endl;
  for(auto c : root->children) printTree(c);
}


int main()
{
  vector<int> v { 4, 2, 16, 7, 8, -1, 100, 5, -1, -1, -1, 200, 22, 3, 14, -1, 111, 121, 1};
  unordered_set<int> lca_input {3, 14, 100, 1};
  node* root = buildTree(v);
  printTree(root);
  cout << "++++++" << endl;
  auto lca = findLCA(root, lca_input);
  if (lca.first)
    cout << "LCA " << lca.first->val << endl;
  else
    cout << "LCA can't be determined" << endl;
  return 0;
}
