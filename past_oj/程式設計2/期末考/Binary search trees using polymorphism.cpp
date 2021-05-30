#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST();
    virtual ~Array_BST() {}
    virtual void insert(const int &) override; //root node is stored at index 1.
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }

private:
    int array[1025];
};

Array_BST::Array_BST(): BST()
{
    for (int i=0; i<1025; i++) {
        array[i] = 0;
    }
}

void Array_BST::insert(const int &value)
{
    int index;

    if(array[1] == 0){
        array[1] = value;
    } else {
        index = 1;
        while(array[index] != 0) {
            if (value > array[index]) {
                index = 2*index+1;
            } else if (value < array[index]) {
                index = 2*index;
            } else {
                return;
            }
        }
        array[index] = value;

        int index1, i;
        for (i=1024; i>=0; i--) {
            if (array[i]!=0) {
                index1 = i;
                break;
            }
        }

        Height = 0;
        while (index1 != 0) {
            index1 /= 2;
            Height++;
        }
    }
}

bool Array_BST::search(const int &value) const
{
    int index = 1;
    while (array[index] != 0) {
        if (array[index]==value) return 1;
        else if (array[index] > value) index = 2*index;
        else index = 2*index+1;
    }
    return 0;
}

class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &) override;
    virtual bool search(const int &) const override;
    int getHeight (ListNode *root);
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    void deleteTree(ListNode *root);

    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};

List_BST::List_BST(): BST()
{
    root = nullptr;
}

void List_BST::deleteTree(ListNode *root)
{
    if (root!=nullptr) {
        List_BST::deleteTree(root->left);
        List_BST::deleteTree(root->right);
        delete root;
    }
}

int List_BST::getHeight (ListNode *root)
{
    int left, right;
    if (root==nullptr) return 0;

    left = getHeight(root->left);
    right = getHeight(root->right);

    return (left > right) ? (left+1) : (right+1);
}

void List_BST::insert(const int &value)
{
    ListNode *temp, *prev;
    if (root==nullptr){
        root = createLeaf(value);
    }
    else {
        temp = root;
        while(temp!=nullptr) {
            if(temp->key > value) {
                prev = temp;
                temp = temp->left;
            } else if (temp->key < value) {
                prev = temp;
                temp = temp->right;
            } else return;
        }

        if (prev->key > value) prev->left = createLeaf(value);
        else if (prev->key < value) prev->right = createLeaf(value);

        Height = getHeight(root);
    }
}

bool List_BST::search(const int &value) const
{
    ListNode *temp;
    temp = root;
    while (temp!=nullptr) {
        if (temp->key == value) return 1;
        else if (temp->key < value) temp = temp->right;
        else temp = temp->left;
    }
}

ListNode* List_BST::createLeaf(int key) const
{
    ListNode* temp;
    temp = new ListNode(key);
    return temp;
}

void BSTManipulator(BST& bstobj1,BST& bstobj2, char cmd ){
    int n;
    if (cmd == 'I') {
        cin >> n;
        bstobj1.insert(n);
        bstobj2.insert(n);
    }else if (cmd == 'S'){
        cin >> n;
        if (bstobj1.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (bstobj2.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }else if (cmd == 'H'){
        cout << bstobj1.height() << endl;;
        cout << bstobj2.height() << endl;;

    }else if (cmd == 'P'){
        bstobj1.print();
        cout << endl;
        bstobj2.print();
        cout << endl;
    }
}
int main(){
    Array_BST A_bst;
    List_BST B_bst;
    //Array_BST B_bst;
    char cmd;

    while (cin >> cmd)
        BSTManipulator(A_bst, B_bst, cmd);

    return 0;
}
