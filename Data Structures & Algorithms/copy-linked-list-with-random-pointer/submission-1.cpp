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
private:
    unordered_map<Node*, Node*> nodeCopyMap;
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr)
        {
            return nullptr;
        }    
        if(nodeCopyMap.contains(head))
        {
            return nodeCopyMap[head];
        }
        Node* copy = new Node(head->val);
        nodeCopyMap[head] = copy;
        copy->next = copyRandomList(head->next);
        copy->random = copyRandomList(head->random);
        return copy;
    }
};
