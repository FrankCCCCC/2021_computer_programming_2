#include <iostream>
#include <string>
using namespace std;

class ListNode
{
    friend class OWList; //make OWList a friend
    friend class TWList; //make TWList a friend

public:
    ListNode( const int &info ) //constructor
    : data( info ), nextPtr( NULL )
    {
    } //end ListNode constructor

private:
    int data; //data
    ListNode *nextPtr; // next node in list
}; //end class ListNode


class OWList
{
public:
    //default constructor
    OWList();
    //destructor
    ~OWList();
    //insert node at front of list
    void insertAtFront( const int &value );
    //remove node from front of list
    void removeFromFront();
    //is List empty?
    bool isEmpty() const;
    //display contents of List
    void print() const;

protected:
    ListNode *firstPtr; //pointer to first node
    ListNode *lastPtr;  //pointer to last node

}; // end class List

OWList::OWList()
{
    firstPtr = nullptr;
    lastPtr = nullptr;
}

OWList::~OWList()
{
    ListNode *temp1, *temp2;
    temp1 = firstPtr;
    while(temp1!=lastPtr && temp1!=nullptr){
        temp2 = temp1;
        temp1 = temp1->nextPtr;
        delete temp2;
    }
    firstPtr = nullptr;
    lastPtr = nullptr;
}

void OWList::insertAtFront( const int &value )
{
    if(firstPtr==nullptr) {
        firstPtr = new ListNode(value);
        firstPtr->nextPtr = nullptr;
        lastPtr = firstPtr;
    } else {
        ListNode *temp;
        temp = new ListNode(value);
        temp->nextPtr = firstPtr;
        firstPtr = temp;
    }
}

void OWList::removeFromFront()
{
    if(firstPtr!=nullptr && firstPtr->nextPtr!=nullptr){
        ListNode *temp;
        temp = firstPtr;
        firstPtr = firstPtr->nextPtr;
        delete temp;
    } else if(firstPtr!=nullptr){
        delete firstPtr;
        firstPtr = nullptr;
        lastPtr = nullptr;
    }
}

bool OWList::isEmpty() const
{
    if(firstPtr==nullptr) return 1;
    else return 0;
}

void OWList::print() const
{
    ListNode *temp;
    temp = firstPtr;
    while(temp->nextPtr!=nullptr){
        cout << temp->data << " ";
        temp = temp->nextPtr;
    }
    cout << temp->data;
}

class TWList:public OWList
{
public:
    //default constructor
    TWList()
    :OWList()
    {
        /*It will still work correctly if you omit the constructor call of the base
          class in the above member initializer list. The compiler will invoke this
          default constructor of OWList implicitly.*/
    }
    //destructor
    ~TWList()
    {
        /*You don't need to delete the list again because the compiler
          will invoke the destructor of the base class OWList to do this.*/
    }
    //insert node at back of list
    void insertAtBack( const int &value );
    //delete node from back of list
    void removeFromBack();

};

void TWList::insertAtBack( const int &value )
{
    if(lastPtr==nullptr) {
        lastPtr = new ListNode(value);
        lastPtr->nextPtr = nullptr;
        firstPtr =  lastPtr;
    } else {
        ListNode *temp;
        temp = new ListNode(value);
        temp->nextPtr = nullptr;
        lastPtr->nextPtr = temp;
        lastPtr = temp;
    }
}

void TWList::removeFromBack()
{
    if(firstPtr!=nullptr && firstPtr->nextPtr!=nullptr){
        ListNode *temp1, *temp2;
        temp1 = lastPtr;
        temp2 = firstPtr;

        while(temp2->nextPtr->nextPtr!=nullptr){
            temp2 = temp2->nextPtr;
        }

        temp2->nextPtr = nullptr;
        lastPtr = temp2;

        delete temp1;
    } else if(firstPtr!=nullptr){
        delete firstPtr;
        firstPtr = nullptr;
        lastPtr = nullptr;
    }
}

int main()
{
    TWList integerList;
    int command;
    int value; // store node value

    while (cin >> command)
    {
        switch(command)
        {
        case 1: // insert at beginning
            cin >> value;
            integerList.insertAtFront(value);
            break;
        case 2: // insert at end
            cin >> value;
            integerList.insertAtBack(value);
            break;
        case 3: // remove from beginning
            integerList.removeFromFront();
            break;
        case 4: // remove from end
            integerList.removeFromBack();
            break;
        }
    }
    integerList.print();
    cout<<endl;
}
