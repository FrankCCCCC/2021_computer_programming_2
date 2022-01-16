#include <iostream>
#include <string.h>
#include "11020.h"

/////ArrayBST/////
Array_BST::Array_BST()
{
    int i;
    for(i=1;i<=1025;i++)
    {
        array[i] = 0;
    }
    Height = 0;
}

void Array_BST::insert(const int &Input)
{
    int index = 1;
    int h = 1;
    while(array[index] != 0)
    {
        if(Input > array[index])
        {
            index = 2*index+1;
            h = h + 1;
            if(h>=Height) Height = h;
        }
        else
        {
            index = 2*index;
            h = h + 1;
            if(h>=Height) Height = h;
        }
    }
    array[index] = Input;
}
bool Array_BST::search(const int &Input) const
{
    int index = 1;
    while(array[index] != 0)
    {
        if(Input > array[index]) index = 2*index+1;
        else if(Input < array[index]) index = 2*index;
        else return true;
    }
    return false;
}

/////ListBST/////

List_BST::List_BST()
{
    root = createLeaf(0);
    Height = 0;
}

ListNode* List_BST::createLeaf(int key) const
{
    ListNode* Node = new ListNode(key);
    return Node;
}

void List_BST::deleteTree(ListNode *root)
{
    if(root == NULL) return;
    else
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

void List_BST::insert(const int& Input)
{
    ListNode* tmp = root;
    int h = 1;
    if(tmp->key == 0) tmp->key = Input;
    else
    {
        while(tmp->key != 0)
        {
            if(Input > tmp->key)
            {
                h = h+1;
                if(h >= Height) Height = h;
                if(tmp->right != NULL) tmp = tmp->right;
                else
                {
                    tmp->right = createLeaf(Input);
                    break;
                }
            }
            else
            {
                h = h+1;
                if(h >= Height) Height = h;
                if(tmp->left != NULL) tmp = tmp->left;
                else
                {
                    tmp->left = createLeaf(Input);
                    break;
                }
            }
        }
    }
}

bool List_BST::search(const int& Input) const
{
    ListNode* tmp = root;
    while(tmp != NULL)
    {
        if(tmp->key == Input) return true;
        else
        {
            if(Input > tmp->key) tmp = tmp->right;
            else tmp = tmp->left;
        }
    }
    return false;
}
