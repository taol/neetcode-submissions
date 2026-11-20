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
    unordered_map<Node*, Node*> visited;
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        if (auto it = visited.find(head); it != visited.end()) {
            return it->second;
        }

        // 先建新节点并立刻入表, 防止 random 指针成环导致死循环
        Node* copy = new Node(head->val);
        visited[head] = copy;

        copy->next = copyRandomList(head->next);
        copy->random = copyRandomList(head->random);
        return copy;
    }
};