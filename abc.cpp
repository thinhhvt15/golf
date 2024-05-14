#include <bits/stdc++.h>

using namespace std;

void removeAll(int k, Node* head)
{
    Node* cur = head->next;
    Node* prev = head;

    while(prev != nullptr && prev->val == k)
        prev = prev->next;

    Node* newHead = prev;
    while(cur != nullptr) {
        if (cur->value == k) {
            cur = cur->next;
            prev->next = cur;
        }
        else {
            prev = prev->next;
            cur = cur->next;
        }
    }

}
