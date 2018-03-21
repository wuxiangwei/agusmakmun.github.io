/*************************************************************************
	> File Name: list.cc
	> Author: wuxiangwei
	> Mail: wuxiangwei@corp.netease.com
	> Created Time: 日  2/25 12:25:52 2018
 ************************************************************************/

#include <iostream>

struct LinkNode {
    int val;
    struct LinkNode *next;
};


LinkNode* create() {
    const int len = 10;

    LinkNode *head = new LinkNode[len];
    if (head == nullptr) {
        return nullptr;
    }

    head[len-1].val = len - 1;
    head[len-1].next = nullptr;

    for (int i=0; i<len-1; ++i) {
        head[i].val = i;
        head[i].next = &head[i+1];
    }

    return head;
}

void print_link(const LinkNode* head) {
    if (head == nullptr) {
        return;
    }

    while(head) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

void reverse(LinkNode **head) {
    if (head == nullptr || *head == nullptr) {
        return;
    }

    LinkNode *temp = *head;
    LinkNode *prev = nullptr;
    LinkNode *next = nullptr;

    while (temp) {
        next = temp->next;

        temp->next = prev;
        prev = temp;
        temp = next;
    }

    *head = prev;
}

int main(int argc, char *argv[]) {
    LinkNode *origin_head = create();
    if (origin_head == nullptr) {
        return -1;
    }

    LinkNode *head = origin_head;

    print_link(head);
    reverse(&head);
    print_link(head);

    if (origin_head) {
        delete [] origin_head;
        origin_head = nullptr;
    }

    return 0;
}
