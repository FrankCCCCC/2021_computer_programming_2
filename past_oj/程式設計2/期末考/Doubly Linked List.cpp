#include <iostream>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

class ListNode{
private:
    int data;
    ListNode *next;
    ListNode *prev;
public:
    ListNode():data(0),next(nullptr), prev(nullptr){};
    ListNode(int a):data(a),next(nullptr), prev(nullptr){};

    friend class List;
};

class List {
private:
    ListNode* head;  // head of the doubly linked list
    ListNode* tail;  // tail of the doubly linked list
    ListNode* middle; // middle of the list
    int       cnt;   // total count of the elements in the list
    int       pos;   // the position of middle

    void reset(){
        head = nullptr;
        tail = nullptr;
        middle = nullptr;
        cnt = 0;
        pos = 0;
    }

    void clean(){
        ListNode* temp;
        while(head!=nullptr){
            temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    // constructor and destructor
    List(){
        reset();
    }

    ~List(){
        clean();
    }

    void InsertHead(int data);
    int  RemoveHead();
    void InsertTail(int data);
    int  RemoveTail();
    void Swap();
    int  getSize();
    int  getMiddle();

};

void List::InsertHead(int data){
    ListNode *tmp;
    if(head==nullptr){
        head = new ListNode;
        head->data = data;
        head->next = nullptr;
        head->prev = nullptr;
        tail = head;
        middle = head;
        cnt = 1;
        pos = 1;
    }
    else if(head!=nullptr && head->next==nullptr) {
        tmp = new ListNode;
        tmp->data = data;
        tmp->next = tail;
        tmp->prev = nullptr;
        head = tmp;
        tail->prev = head;
        cnt = 2;
        pos = 2;
    }
    else {
        tmp = new ListNode;
        tmp->data = data;
        tmp->next = head;
        tmp->prev = nullptr;
        head->prev = tmp;
        head = tmp;
        cnt++;
        pos = cnt/2+1;
        if (cnt%2 == 1) {
            middle = middle->prev;
        }
    }
}

int List::RemoveHead(){
    ListNode *tmp;
    int data1;

    if(head == nullptr) {
        throw out_of_range("empty list");
    } else {
        data1 = head->data;
        if (head==tail){
            delete head;
            head = nullptr;
            tail = nullptr;
            middle = nullptr;
            cnt = 0;
            pos = 0;
        } else {
            tmp = head;
            head = head->next;
            delete tmp;
            cnt--;
            pos = cnt/2+1;
            if (cnt%2 == 0) {
                middle = middle->next;
            }
        }
    }
    return data1;
}

void List::InsertTail(int data){
    ListNode *tmp;

    if (head==nullptr) {
        tail = new ListNode;
        tail->data = data;
        tail->next = nullptr;
        tail->prev = nullptr;
        head = tail;
        middle = tail;
        cnt = 1;
        pos = 1;
    } else if(head!=nullptr && head->next==nullptr){
        tmp = new ListNode;
        tmp->data = data;
        tmp->next = nullptr;
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
        middle = tmp;
        cnt = 2;
        pos = 2;
    } else {
        tmp = new ListNode;
        tmp->data = data;
        tmp->next = nullptr;
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
        cnt++;
        pos = cnt/2+1;
        if(cnt%2 == 0) middle = middle->next;
    }
}

int List::RemoveTail(){
    ListNode *tmp;
    int data1;

    if(head == nullptr) {
        throw out_of_range("empty list");
    } else {
        data1 = tail->data;
        if (head==tail){
            delete head;
            head = nullptr;
            tail = nullptr;
            middle = nullptr;
            cnt = 0;
            pos = 0;
        } else {
            tmp = tail;
            tail = tail->prev;
            delete tmp;
            cnt--;
            pos = cnt/2+1;
            if (cnt%2 == 1) {
                middle = middle->prev;
            }
        }
    }
    return data1;
}

void List::Swap(){
    ListNode *tmp, *tmp1;

    if(head==nullptr) return;
    else if (head->next == nullptr) return;
    else {
        //cout << middle->data << endl <<endl;
        tail->next = head;
        head->prev = tail;
        tmp = middle->prev;
        tmp->next = nullptr;
        middle->prev = nullptr;
        tmp1 = middle;

        if(cnt%2 == 1) middle = tail;
        else middle = head;

        head = tmp1;
        tail = tmp;


    }
}

int main(){
    List L;
    string cmd;
    int data, cnt=0, pos = 0;

    while(cin >> cmd){
        if(cmd=="IH"){ // insert an integer to the head
            cin >> data;
            L.InsertHead(data);
        } else if (cmd=="IT"){ // insert an integer to the end
            cin >> data;
            L.InsertTail( data);
        } else if (cmd=="RH"){   // print and remove a node from head
            try {
                cout<< L.RemoveHead() <<endl;
            } catch (const out_of_range &e){
                cout << endl;
            }
        } else if (cmd=="RT") {// print and remove a node from tail
            try {
                cout << L.RemoveTail()<<endl;
            } catch (const out_of_range &e){
                cout << endl;
            }
        } else if (cmd=="S"){
            L.Swap();
        }
    }
}