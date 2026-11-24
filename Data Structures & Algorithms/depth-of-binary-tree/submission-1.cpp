/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */


// top down
class Solution {
private:
    void calDepth(TreeNode* root, int& maxDepth)
    {
        if(root==nullptr)
        {
            return;
        }

        maxDepth += 1;
        calDepth(root->left, maxDepth);
        calDepth(root->left, maxDepth);
    }
public:
    int maxDepth(TreeNode* root) {
        int maxDepth = 0;
        calDepth(root, maxDepth);
        return maxDepth;
    }
};
