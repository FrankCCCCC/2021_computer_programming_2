#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

void Push(vector<string> out, string Name);
void Pop(vector<string> out);
void Front(vector<string> out);

int main()
{
    vector<string> Output;
    string Command;
    int i = 0;
    while(cin>>Command)
    {
        if(Command == "Push")
        {
            string input;
            cin >> input;
            Output.push_back(input);
            //cout << "Size ="  << Output.size() << endl;
        }
        else if(Command == "Pop")
        {
            if (i < Output.size() && !Output.empty())
            i++;
        }
        else if(Command == "Front")
            if(i < Output.size()&& !Output.empty())
            {
                string Out = Output.at(i);
                cout << Out << endl;
            }
            else
                cout << "empty\n";
    }
}

void Push(vector<string> out, string Name)
{
    out.push_back(Name);
}

void Pop(vector<string> out)
{
    string Begin = *(out.begin());
    string End = *(out.end());
    cout << "B:" << Begin << "E:" << End << endl;
    /*if ((*(out.begin())) != ((*out.end())))
        out.erase(out.begin());*/
    //else return;
}

void Front(vector<string> out)
{
    if(out.begin() != out.end())
    {
        cout << out[0];
    }
    else cout << "empty" << "\n";
}

