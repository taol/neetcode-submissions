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

class Solution {
private:
    int depth(TreeNode* root, int& maxDiameter)
    {
        if(root->left==nullptr && root->right==nullptr)
        {
            return 0;
        }

        int diameter = 0, leftDepth = 0, rightDepth = 0;
        if(root->left != nullptr)
        {
            leftDepth = 1 + depth(root->left, maxDiameter);
        }
        if(root->right != nullptr)
        {
            rightDepth = 1 + depth(root->right, maxDiameter);
        }
        diameter = leftDepth + rightDepth;
        maxDiameter = max(maxDiameter, diameter);
        return max(leftDepth, rightDepth);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDiameter = 0;
        depth(root, maxDiameter);
        return maxDiameter;
    }
};
