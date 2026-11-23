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
    int depth(TreeNode* root, int& maxDiameter) {
        if (root == nullptr) {
            return 0;
        }
        int leftDepth = depth(root->left, maxDiameter);
        int rightDepth = depth(root->right, maxDiameter);

        maxDiameter = max(maxDiameter, leftDepth + rightDepth);
        return 1 + max(leftDepth, rightDepth);
    }

   public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDiameter = 0;
        depth(root, maxDiameter);
        return maxDiameter;
    }
};
