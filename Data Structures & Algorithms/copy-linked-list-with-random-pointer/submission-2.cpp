/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mapping;
        Node* curr = head;
        while(curr)
        {
            Node* copy = new Node(curr->val);
            mapping[curr] = copy;
            curr = curr->next;
        }    

        curr = head;
        while(curr)
        {
            mapping[curr]->next = mapping[curr->next];
            if(curr->random)
            {
                mapping[curr]->random = mapping[curr->random];
            }
            curr = curr->next;
        }

        return mapping[head];
    }
};
