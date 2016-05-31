/******************************************************************************
 因为题目要求复杂度为O(nlogn),故可以考虑归并排序的思想。
归并排序的一般步骤为：
1）将待排序数组（链表）取中点并一分为二；
2）递归地对左半部分进行归并排序；
3）递归地对右半部分进行归并排序；
4）将两个半部分进行合并（merge）,得到结果。

所以对应此题目，可以划分为三个小问题：
1）找到链表中点 （快慢指针思路，快指针一次走两步，慢指针一次走一步，快指针在链表末尾时，慢指针恰好在链表中点）；
2）写出merge函数，即如何合并链表。 （见merge-two-sorted-lists 一题解析）
3）写出mergesort函数，实现上述步骤。 
*******************************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *sortList(ListNode *head) 
    {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode* mid = getMid(head);
        ListNode* right = sortList(mid->next);
        mid->next = NULL;
        ListNode* left = sortList(head);
        
        return mergeList(left,right);
        
    }
private:
    ListNode *getMid(ListNode *head)
    {
        if(head == NULL)
            return NULL;
         ListNode* slow = head;
         ListNode* quick = head->next;
        while(quick != NULL && quick->next != NULL)
        {
            slow = slow->next;
            quick = quick->next->next;
        }
        return slow;     
    }
    ListNode *mergeList(ListNode *L1, ListNode *L2)
    {
        if(L1 == NULL)
            return L2;
        if(L2 == NULL)
            return L1;
        ListNode* Head  = new ListNode(0);
        ListNode* La = Head;
        while(L1 && L2)
        {
            if(L1->val <= L2->val)
            {
                La->next = L1;
                L1 = L1->next;
            }
            else
            {
                La->next = L2;
                L2 = L2->next;
            }
            La = La->next;
        }
        if(L1 == NULL)
            La->next = L2;
        if(L2 == NULL)
            La->next = L1;
        La = Head;
        Head = Head->next;
        delete La;
        return Head;
    }
};
/***************************************************************
利用快速排序的思想
思想是：选取第一个节点作为枢轴，然后遍历链表，
如果当前元素小于枢轴的元素，则采用头插法，把该位置的节点插入到链表的首位置，
如果当前元素大于枢轴元素，则当前元素向前移动一位。
遍历一遍链表以后，最后枢轴的位置，把链表分割为两部分，
前部分元素小于枢轴元素，后半部分元素大于枢轴元素。
****************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *sortList(ListNode *head) 
    {
        if (head == NULL || head->next == NULL)  
        return head;  
    ListNode *pHead = new ListNode(INT_MIN);  
    pHead->next = head;  
    partition(pHead, NULL);  
    return pHead->next;  
    }
private:
 //对链表中的元素进行划分  
void partition(ListNode *start, ListNode *last)  
{  
    if (start->next == last)  
        return;  
    ListNode *pre = start;  
    ListNode *cur = pre->next;  
    ListNode *privot = cur;  
    while (cur->next != NULL && cur->next != last)  
    {  
        if (privot->val > cur->next->val)  
        {  
            ListNode *tmp = pre->next;  
            pre->next = cur->next;  
            cur->next = cur->next->next;  
            pre->next->next = tmp;  
        }  
        else  
        {  
            cur = cur->next;  
        }  
    }  
    partition(start, privot);  
    while (privot->next != last && privot->next->val == privot->val)  
    {  
        privot = privot->next;  
    }  
    if (privot->next != last)  
        partition(privot, last);  
}  
};
