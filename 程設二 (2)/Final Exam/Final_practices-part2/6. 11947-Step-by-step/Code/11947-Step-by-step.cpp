#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int steps[11];

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

int check(int typeNum, int target) {
    int x = steps[0];
    for (int i=1; i<typeNum; i++) {
        x = gcd(steps[i], x);
    }
    return target%x == 0;
}

int solve(int typeNum, int target) {
    queue<pair<int, int>> myQueue; // first=location second=stepNum
    myQueue.push(make_pair(0, 0));
    set<int> passed;
    bool find = false;
    while(!myQueue.empty()) {
        if (find) break;
        pair<int, int> frontPair = myQueue.front();
        myQueue.pop();

        int loc = frontPair.first;
        int num = frontPair.second;
        if (passed.find(loc) != passed.end()) continue;

        passed.insert(loc);
        for (int i=0; i<typeNum; i++) {
            if (loc+steps[i] == target || loc-steps[i] == target) {
                cout << num+1 << endl;
                find = true;
                break;
            }
            myQueue.push(make_pair(loc+steps[i], num+1));
            myQueue.push(make_pair(loc-steps[i], num+1));
        }
    }
}

int main() {
    int testNum;
    cin >> testNum;


    for (int i=0; i<testNum; i++) {
        int typeNum, target;
        cin >> typeNum >> target;
        for (int j=0; j<typeNum; j++) {
            cin >> steps[j];
        }
        if (check(typeNum, target)) solve(typeNum, target);
        else cout << "-1" << endl;
    }
}
