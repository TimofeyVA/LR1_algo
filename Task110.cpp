#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()
        : val(0)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x)
        , left(left)
        , right(right)
    {
    }
};

class Solution {
public:
    bool is_balance = true;
    int balance(TreeNode* node)
    {
        if (node == nullptr)
            return 0;

        int left_depth = balance(node->left);
        int right_depth = balance(node->right);

        if (abs(left_depth - right_depth) > 1) {
            is_balance = false;
        }
        return std::max(left_depth, right_depth) + 1;
    }

    bool isBalanced(TreeNode* root)
    {
        balance(root);
        return is_balance;
    }
};