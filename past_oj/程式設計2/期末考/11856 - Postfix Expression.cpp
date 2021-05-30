#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int a, b, input_int;
    char input;
    stack<int> s;

    while(cin >> input){
        if(input=='0')
            break;
        else if(input==' ')
            continue;
        else if(isdigit(input)){
            cin.unget();
            cin >> input_int;
            s.push(input_int);
        }
        else if(input=='+'){
            a=s.top();
            s.pop();
            b=s.top();
            s.pop();
            s.push(a+b);
        }
        else if(input=='-'){
            a=s.top();
            s.pop();
            b=s.top();
            s.pop();
            s.push(b-a);
        }
        else if(input=='*'){
            a=s.top();
            s.pop();
            b=s.top();
            s.pop();
            s.push(a*b);
        }
        else if(input=='/'){
            a=s.top();
            s.pop();
            b=s.top();
            s.pop();
            s.push(b/a);
        }
    }
    cout << s.top() << endl;
}
