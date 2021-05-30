#include <iostream>
#include <string.h>
#include <string>
using namespace std;

class Char{
	friend class Str;
	private:
		Char(char text):next(NULL){
			this->text=text;
		}

		~Char(){
            if(next)
                delete next;
		}

		void print(){
            cout<<text;
            if(next)
                next->print();
		}

		char text;
		Char *next;
};

class Str{
	public:
	    // construct a new Str by linked list of Char
		Str(char*);

		// copy constructor
		// have to copy all Chars of another Str
		Str (const Str &);
		// equality operator
        bool operator==( const Str & ) const;


		/** the following methods are already implemented **/
		Str():head(NULL),tail(NULL){} // default constructor

		~Str(){
            if(head)
                delete head;
		}

		Str& strInsert(const Str &s){
			Str tmp(s);

            tail->next=tmp.head;
            tail=tmp.tail;

            tmp.head=NULL;
            return *this;
		}

		Str& strSwap(Str &s){
			Str tmp(*this);
            this->~Str();

			*this=s;
            s=tmp;

            tmp.head=NULL;
			return *this;
		}

		void strPrint(){
            if(head)
                head->print();
            cout<<endl;
		}

	private:
		Char *head;
		Char *tail;
};

Str::Str(char* a)
{
    int i = 1;
    head = new Char(a[0]);
    Char *ptr = head;
    while(a[i]!='\0'){
        ptr->next = new Char(a[i]);
        ptr = ptr->next;
        i++;
    }
    tail = ptr;
    tail->next = nullptr;
}
Str::Str(const Str &sa)
{
    Char *h = sa.head;
    Char *ptr;
    head = new Char(h->text);
    ptr = head;
    while(h->next!=nullptr){
        h = h->next;
        ptr->next = new Char(h->text);
        ptr = ptr->next;
    }
    tail = ptr;
    tail->next = nullptr;
}
bool Str::operator==(const Str &s) const
{
    Char *temp1 = head;
    Char *temp2 = s.head;
	if(temp1==nullptr && temp2==nullptr) return 1;
    while(temp1!=nullptr && temp2!=nullptr){
        if(temp1->text!=temp2->text) return 0;
        else if (temp1->next==nullptr && temp2->next==nullptr) return 1;
        else {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    return 0;
}
typedef void (*FUNC)(Str &s1,Str &s2);

const int OPnum=5;
typedef struct _OPmap{
    const char *op;
    FUNC fp;
}OPmap;

void func_si(Str &s1,Str &s2){
    s1.strSwap(s2).strInsert(s2);
}

void func_is(Str &s1,Str &s2){
    s1.strInsert(s2).strSwap(s2);
}

void func_s(Str &s1,Str &s2){
    s1.strSwap(s2);
}

void func_i(Str &s1,Str &s2){
    s1.strInsert(s2);
}

void func_t(Str &s1,Str &s2){
    if(s1==s2){
        s1.strInsert(s2);
    }else{
        s1.strSwap(s2);
    }
}

OPmap MAP[OPnum]={{"si",func_si},{"is",func_is},{"s",func_s},{"i",func_i},{"t",func_t}};

void operate(char *op,Str &s1,Str &s2){
    for(int i=0;i<OPnum;i++)
        if(strcmp(MAP[i].op,op)==0){
            MAP[i].fp(s1,s2);
            break;
        }
}

int main() {

	int N;
	char input[100];

	int index=0;
	Str *s[100];

	cin>>N;
    for(int i=0;i<N;i++){
    	cin>>input;
    	s[index++]=new Str(input);
    }

    char op[3];//"si" || "is" || "s" || "i" || "t" || "e"
    while(1){
    	cin>>op;
    	if(op[0]=='e')break;

    	int idx1,idx2;
    	cin>>idx1;
    	cin>>idx2;

    	operate(op,*s[idx1],*s[idx2]);
	}

	for(int i=0;i<N;i++){
        s[i]->strPrint();
        delete s[i];
	}
	return 0;
}