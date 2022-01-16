#include<iostream>
#include<string.h>
#include "10998.h"

using namespace std;

List_stack::List_stack()
{
    head = tail = NULL;
}
List_stack::~List_stack()
{
    ListNode *Tmp;
    while(head)
    {
        Tmp = head;
        head = head->nextPtr;
        delete Tmp;
    }
}
void List_stack::push(const int &data )
{
    ListNode* Tmp = new ListNode(data);
    if(tail)
    {
        Tmp->nextPtr = NULL;
        Tmp->prevPtr = tail;
        tail->nextPtr = Tmp;
        tail = tail->nextPtr;
    }
    else head = tail = Tmp;
}

void List_stack::pop()
{
    if(tail == NULL) return;

    ListNode* P = tail;

    if (tail == head) head = tail = NULL;
    else
    {
        tail = tail->prevPtr;
        tail->nextPtr = NULL;
        delete P;
    }
}

void List_stack::print()
{
    if(tail != NULL)
    {
        ListNode* Now = tail;
        while(Now != head)
        {
            cout << Now->data << " ";
            Now = Now->prevPtr;
        }
        cout << Now->data;
    }
    else return;
}
