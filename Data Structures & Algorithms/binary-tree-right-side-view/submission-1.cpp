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
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }

private:
    void dfs(TreeNode* root, int depth, vector<int>& res) {
        if (root == nullptr) return;
        
        // 【前序位置】如果当前深度等于 res 的大小，说明这是这一层我们看到的第一个（也就是最右边的）节点！
        if (depth == res.size()) {
            res.push_back(root->val);
        }
        
        // Top-down：派发给小弟，⚠️ 注意必须先右后左！
        dfs(root->right, depth + 1, res);
        dfs(root->left, depth + 1, res);
    }
};
