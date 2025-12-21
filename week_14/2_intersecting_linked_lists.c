/*struct ListNode *getIntersectionNode(struct ListNode *headA,
                                     struct ListNode *headB)
{
    if (!headA || !headB) return NULL;

    struct ListNode *a = headA, *b = headB;

    while (a != b) {          // 比较地址，不是比较 val
        a = a ? a->next : headB;
        b = b ? b->next : headA;
    }
    return a;                 // 相遇即相交节点，同为 NULL 表示不相交
}*/