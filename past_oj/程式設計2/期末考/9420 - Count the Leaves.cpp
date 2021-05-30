#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void Count_leaves(map<int, vector<int> > m, int root, int &count)
{
    vector<int>::iterator it;

    if (m[root].size()==0){
        count++;
        return;
    }

    for (it=m[root].begin(); it!=m[root].end(); it++) {
        Count_leaves(m, *it, count);
    }

}

int main()
{
    map<int, vector<int> > m;
    /*m[1].push_back(2);
    m[1].push_back(3);
    vector<int>::iterator it;

    for (it = m[1].begin(); it!=m[1].end(); it++){
        cout << *it << endl;
    }*/

    int N, key, value, count, root;
    //vector<int>::iterator it;

    while(1){
        cin >> N;
        if (N==0) break;

        while (N--) {
            cin >> key >> value;
            m[key].push_back(value);
        }
        cin >> root;
        count = 0;

        //it = m[root].begin();

        Count_leaves(m, root, count);

        cout << count << endl;

        m.clear();
    }
}
