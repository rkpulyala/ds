class PreorderBinaryTreeIterator {
  std::stack<node*> nodeStack;

public:
  PreorderBinaryTreeIterator(node* root) {
    if (root) nodeStack.push(root);
  }

  constexpr bool hasNext() const {
    return !nodeStack.empty();
  }

  node* next() {
    node *nxt = nodeStack.top(); nodeStack.pop();
    if (nxt->right) nodeStack.push(nxt->right);
    if (nxt->left)  nodeStack.push(nxt->left);
    return nxt;
  }
  
};

class PreorderBinaryTreeIterator {
  std::stack<node*> nodeStack;

public:
  PreorderBinaryTreeIterator(node* root) {
    while (root) {
      nodeStack.push(root);
      root = root->left;
    }
  }

  constexpr bool hasNext() const {
    return !nodeStack.empty();
  }

  node* next() {
    node *nxt = nodeStack.top(); nodeStack.pop();
    node *root = nxt->right;
    while (root) {
      nodeStack.push(root);
      root = root->left;
    }
    return nxt;
  }
  
};

class PostOrderBinaryTreeIterator {
  std::stack<node*> nodeStack;

  void pushTillLeftMostLeaf(const node* root) {
    while(root) {
      while (root) {
        nodeStack.push(root);
        root = root->left;
      }
      root = nodeStack.top()->right;
    }
  }

public:
  PostOrderBinaryTreeIterator(node* root) {
    pushTillLeftMostLeaf(root);
  }

  constexpr bool hasNext() const {
    return !nodeStack.empty();
  }

  node* next() {
    if (!hasNext()) return nullptr;
    node *nxt = nodeStack.top(); nodeStack.pop();
    node *parent = nodeStack.top();
    if (nxt != parent->right) pushTillLeftMostLeaf(parent->right);
    return nxt;
  }
  
};

