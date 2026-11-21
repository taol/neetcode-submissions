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
        if (!head) return nullptr;

        // Step 1: 穿插克隆节点 (A -> A' -> B -> B')
        Node* curr = head;
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        // Step 2: 连接 random 指针
        curr = head;
        while (curr) {
            if (curr->random) {
                // 克隆节点的 random = 原节点 random 的克隆节点
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next; // 每次跳两步，走到下一个原节点
        }

        // Step 3: 拆分新旧链表，必须还原原链表
        curr = head;
        Node* copyHead = head->next;
        
        while (curr) {
            Node* copy = curr->next;
            
            // 还原原链表的 next
            curr->next = copy->next;
            curr = curr->next;
            
            // 连接新链表的 next
            if (curr) {
                copy->next = curr->next;
            }
        }

        return copyHead;
    }
};
