#include <iostream>
#include <limits>
#include <tuple>

using namespace std;

class LinkedListNode {
public:
    int val;
    LinkedListNode* next;
    
    LinkedListNode(int node_value) {
        val = node_value;
        next = NULL;
    }
};

LinkedListNode* _insert_node_into_singlylinkedlist(LinkedListNode* head, LinkedListNode* tail, int val) {
    if (!head) {
        head = new LinkedListNode(val);
        tail = head;
    } else {
        LinkedListNode* node = new LinkedListNode(val);
        tail->next = node;
        tail = tail->next;
    }
    
    return tail;
}

/*
For your reference:
LinkedListNode {
    int val;
    LinkedListNode* next;
};

*/

void node_swap(LinkedListNode* &first, LinkedListNode* &second)
{
    LinkedListNode* temp = first;
    first = second;
    second = temp;
}


tuple<LinkedListNode*, LinkedListNode*, int> get_kth_nodes_length(LinkedListNode* head, int k)
{
    int length = 0;
    LinkedListNode* head_copy = head;
    while(head) { ++length; head = head->next; }
    
    int nk = length - k; --k; //nk = k from back. --k to make it zero indexed.
    
    LinkedListNode *first = nullptr, *second = nullptr;
    
    cout << "k, nk, length = " << k << " " << nk  << " " << length << endl; 
    if (k > nk) {
        swap(k,nk);
        cout << "k, nk, length = " << k << " " << nk  << " " << length << endl; 
    }
    head = head_copy;
    while(head) {
        if (!k && !first) { first = head; }
        if (!nk && !second) { second = head; }
        --k; --nk;
        head = head->next;
    }
    
    return {first, second, length};
    
}

tuple<LinkedListNode*, LinkedListNode*> get_previous_nodes(LinkedListNode* head, LinkedListNode* first, LinkedListNode* second)
{
    LinkedListNode *previous_to_first = nullptr, *previous_to_second = nullptr;
    while(head) {
        if (head->next == first && !previous_to_first) { previous_to_first = head; }
        if (head->next == second && !previous_to_second) { previous_to_second = head; }
        head = head->next;
    }

    return {previous_to_first, previous_to_second};
}

LinkedListNode* swap_nodes(LinkedListNode* head, int k) {
/**
These are the cases:
1. Null list
2. Single node in a list 
3. Two nodes in a list
4. Head and tail of the list to be swapped (k = 1)
5. Two adjecent nodes somewhere in the list
6. Same/middle node (k results in single middle node)
7. Everything else

{1, 2, 6} --> do nothing
{5,7} --> swap(previous_to_first->next, previous_to_second->next); swap(first->next, second->next);
{3,4} --> previous_to_second->next = first; swap(first->next, second->next);
**/

    if (!head || !head->next) return head; /*1*/

    int length = 0;
    LinkedListNode *first = nullptr, *second = nullptr;
    LinkedListNode *previous_to_first = nullptr, *previous_to_second = nullptr;
    
    tie(first, second, length) = get_kth_nodes_length(head, k);
    
    cout << "first = " << first->val << " second = " << second->val << endl;

    if (length == 1 || first == second) return head; /* 2, 6*/

    tie(previous_to_first, previous_to_second) = get_previous_nodes(head, first, second);
    
    
    if (k == 1 || k == length || head->next == second) { /* 3,4 */
        previous_to_second->next = first; 
        node_swap(first->next, second->next);
        return second;
    }

    /*5, 7*/
    node_swap(previous_to_first->next, previous_to_second->next); 
    node_swap(first->next, second->next);
    return head;
}

int main()
{
    int head_size;
    cin >> head_size;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    LinkedListNode* head = NULL;
    LinkedListNode* head_tail = NULL;

    for (int head_i = 0; head_i < head_size; head_i++) {
        int head_item;
        cin >> head_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        head_tail = _insert_node_into_singlylinkedlist(head, head_tail, head_item);

        if (!head_i) {
            head = head_tail;
        }
    }


    int k;
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    LinkedListNode* res = swap_nodes(head, k);

    while (res) {
        cout << res->val;

        if (res->next) {
            cout << "\n";
        }

        res = res->next;
    }

    cout << "\n";
    
    return 0;
}

