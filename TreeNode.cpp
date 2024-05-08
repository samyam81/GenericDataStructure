class TreeNode {
private:
    int val;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode() {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int val) {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int val, TreeNode* left, TreeNode* right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};
