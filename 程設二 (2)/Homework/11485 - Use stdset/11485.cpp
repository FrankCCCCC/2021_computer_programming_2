#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int GetValue(vector<int> Target);
vector<int> ReadValue();
void PrintVector(vector<int> Target);
void Reverse(vector<int> Target);

struct Mycompare
{
    bool operator()(const vector<int>& Left, const vector<int>& Right) const
    {
        return GetValue(Left) < GetValue(Right);
    }
};

int GetValue(vector<int> Target)
{
    int i;
    int value = 0;
    int Size = Target.size();
    for(i = 0; i<Size; i++)
    {
        value += Target.at(i)*(Size-i);
    }
    return value;
}

vector<int> ReadValue()
{
    int i;
    vector<int> NewVector;
    while(cin>>i)
    {
        if(i == 0) break;
        NewVector.push_back(i);
    }
    return NewVector;
}

void PrintVector(vector<int> Target)
{
    int i;
    for(i = 0; i< Target.size(); i++)
    {
        cout << Target.at(i) << " ";
    }
    cout << "\n";
}

void Reverse(vector<int> Target)
{
    vector<int> temple;
    vector<int>::iterator Tit,Eit;

    temple = Target;
    Eit = temple.end();

    for(Tit = Target.begin(); Tit!=Target.end(); Tit++)
    {
        if(Eit != temple.begin())Eit--;
        *(Tit) = *(Eit);
    }
}

int main()
{
    set<vector<int>, Mycompare> Set;
    string command;

    while(cin>>command)
    {
        if(command == "insert")
        {
            vector<int> t = ReadValue();
            set<vector<int>, Mycompare>::iterator it;
            for(it = Set.begin(); it != Set.end(); it++)
            {
                vector<int> cur = *(it);
                if(GetValue(cur) == GetValue(t))
                {
                    cout << "exist" << endl;
                    Set.erase(cur);
                    Reverse(t);
                    break;
                }
            }
            Set.insert(t);
        }
        else if(command == "range_out")
        {
            int from = GetValue(ReadValue());
            int to = GetValue(ReadValue());

            set<vector<int>, Mycompare>::iterator it;
            for(it = Set.begin(); it!= Set.end(); it++)
            {
                vector<int> Cur = *(it);
                int value = GetValue(Cur);
                if(value >= from && value <= to)
                {
                    PrintVector(Cur);
                }
                else if(value > to) break;
            }
        }
        else if(command == "output")
        {
            set<vector<int>, Mycompare>::iterator it;
            for(it=Set.begin();it!=Set.end();it++)
            {
                vector<int> cur = *it;
                PrintVector(cur);
            }
        }
    }
}
