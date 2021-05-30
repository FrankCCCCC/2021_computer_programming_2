#include<cstddef>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<string>
//#ifdef ONLINE_JUDGE
//#include"NTHUOJLock"
//#endif

#include<iosfwd>

using namespace std;

namespace oj
{
	class Memory_leak_count	//check whether the process has memory leak
	{
		friend void memory_leak_count_check();
		static unsigned count_;
	public:
		Memory_leak_count();
		~Memory_leak_count();
	};

	struct Int	//you can treat Int as int
	{
		int val;	//store int in val, you this val
		Int();
		Int(int val);
		Int(const Int &);	//copy constructor
		operator int&()	//treat Int as int, conversion function
		{
			return val;
		}
		operator int() const	//treat Int as int, conversion function
		{
			return val;
		}
		Int& operator=(const Int &);	//copy constructor
	private:
		Memory_leak_count count_;	//you don't have to pay attention on this
	};

	typedef Int data_t;

	class Vector
	{
	public:
		typedef std::size_t size_type;
		typedef Int value_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
	private:
		pointer begin_;	//begin of array
		pointer end_;	//end of array
		pointer last_;	//end of current element
	public:
		Vector();


		size_type capacity() const;

		size_type size() const;

		//ignore the keyword "inline"
		//operator[] makes Vector like a C-array, for example
		//int a[2]{2,1};
		//Vector vec;
		//vec.push_back(1);
		//vec.push_back(2);
		//vec[0] is equal to a[1]
		//vec[1] is equal to a[0]
		inline reference operator[](const size_type pos)
		{
			return begin_[pos];
		}
		inline const_reference operator[](const size_type pos) const
		{
			return begin_[pos];
		}

		void pop_back();
		void push_back(value_type val);
		void insert(size_type pos,size_type count,value_type val);

		void reserve(size_type new_capacity);
		void resize(size_type new_size);

		~Vector();
	};

	std::ostream& operator<<(std::ostream &os,const Vector &vec);	//for cout

	void memory_leak_count_check();	//you don't have to pay attention on this
}
oj::Vector::Vector(){
	begin_ = NULL;
	end_ = NULL;
	last_ = NULL;
}
size_t oj::Vector::capacity()const{
	return end_ - begin_;
}
size_t oj::Vector::size()const{
	return last_ - begin_;
}
void oj::Vector::pop_back(){
    if(size()>0)
        last_--;
}

void oj::Vector::push_back(data_t val)
{
    if(size() >= capacity())
        reserve(std::max(capacity()+1,capacity()*3));
    begin_[size()] = val;
    last_++;
}

void oj::Vector::reserve(std::size_t new_capacity)
{
    if(capacity() < new_capacity){
        data_t *new_begin=new data_t[new_capacity];
        for(int i=0;i<size();i++){
            new_begin[i]=begin_[i];
        }
        delete []begin_;
        last_ = new_begin + size();
        end_ = new_begin + new_capacity;
        begin_ = new_begin;
    }
}
void oj::Vector::insert(std::size_t pos,std::size_t count,data_t val){
	int oldsize = size();
	if(count>capacity()-size()){
		reserve( max( (capacity()+capacity()/2) , capacity()+count ) );
	}
	for(int i=0;i<oldsize-pos;i++){
		begin_[oldsize+count-i-1] = begin_[oldsize-i-1];
	}
	for(int i=0;i<count;i++){
		begin_[pos+i] = val;
		last_++;
	}

}
void oj::Vector::resize(std::size_t new_size){

	if(new_size > capacity()){
        data_t *new_begin=new data_t[new_size];
        for(int i=0;i<size();i++){
            new_begin[i]=begin_[i];
        }
        for(int i=size();i<new_size;i++){
        	new_begin[i]=0;
		}
        delete []begin_;
        last_ = new_begin + new_size;
        end_ = new_begin + new_size;
        begin_ = new_begin;
	}else if( new_size>size() && new_size<capacity() ){
		for(int i=size();i<new_size;i++){
			begin_[i] = 0;
		}
		last_ = last_+(new_size - size());
	}else if(new_size<size()){
		int minus = size()-new_size;
		for(int i=0;i<minus;i++){
			last_--;
		}
	}
}

oj::Vector::~Vector()
{
    /*delete []begin_;*/
    delete []begin_;
}

namespace oj
{
	Int::Int()
		:val(0){}	//set val as 0

	Int::Int(const int val_)
		:val(val_){}

	Int::Int(const Int &rhs)
		:val(rhs.val){}	//copy from rhs.val

	Int& Int::operator=(const Int &rhs)
	{
		val=rhs.val;	//copy from rhs.val
		return *this;
	}

	std::ostream& operator<<(std::ostream &os,const Vector &vec)
	{
		for(std::size_t i(0);i!=vec.size();++i)
			os<<vec[i]<<' ';
		return os;
	}
}

int main()
{
	using namespace std;
	srand(time(NULL));
	{
		oj::Vector v,v2;
		string command;

		for(oj::data_t n;cin>>command;)
		{
			if(command=="pop_back")
			{
				if(rand()&1&&v2.size())
					v2.pop_back();
				v.pop_back();
				if(rand()&1&&v2.size())
					v2.pop_back();
				cout<<v<<endl;
			}
			else if(command=="push_back")
			{
				cin>>n;
				if(rand()&1)
					v2.push_back(n);
				v.push_back(n);
				if(rand()&1)
					v2.push_back(n);
				cout<<v<<endl;
			}
			else if(command=="insert")
			{
				size_t pos,count;
				cin>>pos>>count>>n;
				if(rand()&1&&pos<=v2.size())
					v2.insert(pos,count,n);
				v.insert(pos,count,n);
				if(rand()&1&&pos<=v2.size())
					v2.insert(pos,count,n);
				cout<<v<<endl;
			}
			else if(command=="capacity")
				cout<<v.capacity()<<endl;
			else if(command=="size")
				cout<<v.size()<<endl;
			else if(command=="reserve")
			{
				cin>>n;
				if(rand()&1)
					v2.reserve(n);
				v.reserve(n);
				if(rand()&1)
					v2.reserve(n);
				cout<<v<<endl;
			}
			else if(command=="resize")
			{
				cin>>n;
				if(rand()&1)
					v2.resize(n);
				v.resize(n);
				if(rand()&1)
					v2.resize(n);
				cout<<v<<endl;
			}
		}
		cout<<v<<endl;
	}
	oj::memory_leak_count_check();	//you don't have to pay attention on this
#ifdef ONLINE_JUDGE
	nthuoj_unlock();
#endif
}

namespace oj
{
	Memory_leak_count::Memory_leak_count()
	{
		++count_;	//memory request + 1
	}

	Memory_leak_count::~Memory_leak_count()
	{
		--count_;	//memory request - 1
	}

	unsigned Memory_leak_count::count_(0);

	void memory_leak_count_check()
	{
		if(Memory_leak_count::count_!=0)	//memory leak if count_ is not equal to 0
			std::cout<<"memory leak"<<std::endl;
	}
}
