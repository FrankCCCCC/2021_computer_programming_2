#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
// 9328 - Queueing
using namespace std;
int main()
{
    string s;
    queue<string> q;

    while (cin >> s) {
        if (s=="Push") {
            cin >> s;
            q.push(s);
        } else if (s=="Pop") {
            if (q.size()>0)
                q.pop();
        } else if (s=="Front") {
            if (q.size()==0)
                cout << "empty\n";
            else
                cout << q.front() << "\n";
        } else {
        }
    }

}
