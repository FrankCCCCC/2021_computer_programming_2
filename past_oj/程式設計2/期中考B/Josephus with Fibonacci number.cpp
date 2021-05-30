#include <iostream>
using namespace std;

class Node
{
   friend class Josephus;
   public:
        Node():next( NULL ){
        }
      	Node( const int &info ) //constructor
   	 :number( info ), next( NULL )
   	 {
   	 } //end ListNode constructor
   private:
      	Node *next;
        int number;
};//end class Node

class Josephus
{
    public:
         Josephus();
         ~Josephus();
         Josephus(const int &);
         int kill() ; // return the survival's position

    private:
        void generatecircularlinkedList(const int &); // generate circular linked-list
        void generateFib(const int &); // generate a Fibonacci sequence table
        int sequence[50]; // store Fibonacci number
        int noOfPeople;
        Node *head;
};

Josephus::Josephus()
{
    for(int i=0; i<50; i++){
        sequence[i] = 0;
    }
    noOfPeople = 0;
    head = nullptr;
}

Josephus::~Josephus()
{
    delete [] head;
    head = nullptr;
}

Josephus::Josephus(const int &n)
{
    head = nullptr;
    noOfPeople = n;
    generatecircularlinkedList(n);
    generateFib(n);

}

int Josephus::kill()
{
    Node *tmp, *tail=nullptr;
    int i=0;
    while(head->next != head){
        if(noOfPeople == 1) break;
        int num = sequence[i]%noOfPeople;

        if (num == 0){
            for(int j=1; j<sequence[i]; j++){
                head = head->next;
            }
        } else {
            for(int j=1; j<num; j++){
                head = head->next;
            }
        }

        noOfPeople--;
        i++;

        tmp = head;
        head = head->next;
        tail = tmp->next;
        while(tail->next!=tmp){
            tail = tail->next;
        }

        delete tmp;
        tail->next = head;

    }
    return head->number;
}

void Josephus::generatecircularlinkedList(const int &n)
{
    Node *tmp;
    if(n>0){
        head = new Node;
        head->number = 1;
        head->next = nullptr;
    }

    if(n>1){
        head->next = new Node;
        tmp = head->next;
        tmp->number = 2;
        tmp->next = nullptr;

        for(int i=3; i<=n; i++){
            tmp->next = new Node;
            tmp->next->number = i;
            tmp = tmp->next;
            tmp->next = nullptr;
        }

        tmp->next = head;
    }

    /*int num = n+2;

    while(num--){
        cout << head->number << endl;
        head = head->next;
    }*/
}

void Josephus::generateFib(const int &n)
{
    sequence[0] = 1;
    sequence[1] = 1;
    for(int i=0; i<n; i++){
        sequence[i+2] = sequence[i+1] + sequence[i];
    }
}

int main(){
	int numofpeople;

	while(cin>>numofpeople){
		Josephus Jose(numofpeople);
		int survival = Jose.kill();
		cout<<survival<<endl;
    }
}

