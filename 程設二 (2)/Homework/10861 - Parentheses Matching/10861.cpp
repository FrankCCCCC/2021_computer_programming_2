#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <stack>

using namespace std;

int Cases;
string Input;
bool Valid = false;

bool FindParenthesesBalance(const string S,const int length)
{
    int i;
    stack<char> L;
    for(i = 0; i < length; i++)
    {
        char C = S[i];
        if(C == '{' || C == '[' || C == '(' || C == '<')
            {
                L.push(C);
                //cout << "Push" << C << endl;
            }
        else if(C == '\n' && L.empty()) return true;
        else
        {
            if(L.empty()) return false;
            char Temp = L.top();
            switch(C)
                {
                    case '}':
                        L.pop();
                        //cout << "Pop" << Temp << endl;
                        if(Temp != '{') return false;
                        break;
                    case ']':
                        L.pop();
                        //cout << "Pop" << Temp << endl;
                        if(Temp != '[') return false;
                        break;
                    case ')':
                        L.pop();
                        //cout << "Pop" << Temp << endl;
                        if(Temp != '(') return false;
                        break;
                    case '>':
                        L.pop();
                        //cout << "Pop" << Temp << endl;
                        if(Temp != '<') return false;
                        break;
                    default:
                        break;
                }
        }
    }
    if(L.empty()) return true;
    else return false;
}

int main()
{
    int i;
    scanf("%d\n", &Cases);
    for(i = 1; i<= Cases; i++)
    {
        char S[1001];
        fgets(S, 1001, stdin);
        Input = S;
        int len = Input.size();
        Valid = FindParenthesesBalance(S, len);
        if(Valid) cout << "Case" << " " << i << ":" << " " << "Yes" << endl;
        else cout << "Case" << " " << i << ":" << " " << "No" << endl;
    }
}
