/*************************************************************************
	> File Name: tree.cc
	> Author: wuxiangwei
	> Mail: wuxiangwei@corp.netease.com
	> Created Time: 日  2/25 18:40:04 2018
 ************************************************************************/

#include <iostream>
#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};

TreeNode* create() {
    const int num = 7;
    TreeNode* root = new TreeNode[num];
    if (root == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < num; ++i) {
        root[i].val = i;
        root[i].left = root[i].right = nullptr;
    }

    root[0].left = root + 1;
    root[0].right = root + 2;
    root[1].left = root + 3;
    root[1].right = root + 4;
    root[2].left = root + 5;
    root[2].right = root + 6;

    return root;
};

void process(const TreeNode *node) {
    if (node) {
        std::cout << node->val << " ";
    }
}

void preorder(const TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    process(root);
    if (root->left) {
        preorder(root->left);
    }

    if (root->right) {
        preorder(root->right);
    }
}

void zorder(const TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    std::stack<TreeNode*> stack1;
    std::stack<TreeNode*> stack2;

    process(root);
    if (root->right) {
        stack1.push(root->right);
    }

    if (root->left) {
        stack1.push(root->left);
    }

    while(!(stack1.empty() && stack2.empty())) {
        while(!stack1.empty()) {
            TreeNode* node = stack1.top();
            stack1.pop();
            process(node);
            if (node->left) {
                stack2.push(node->left);
            }
            if (node->right) {
                stack2.push(node->right);
            }
        }

        while(!stack2.empty()) {
            TreeNode* node = stack2.top();
            stack2.pop();
            process(node);

            if (node->left) {
                stack1.push(node->left);
            }

            if (node->right) {
                stack1.push(node->right);
            }
        }
    }
}


int main(int argc, char* argv[]) {
    TreeNode *root = create();

    // preorder(root);
    zorder(root);
    std::cout << std::endl;
    if (root) {
        delete [] root;
        root = nullptr;
    }

    return 0;
}

