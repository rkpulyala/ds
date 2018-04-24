/*
Least Common Ancestor
Given an n-ary tree, find the LCA of a set of values.
There are no repeated values in the tree


struct node {
    int val;
    list<node*> children;
};

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
