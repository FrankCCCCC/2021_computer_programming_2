#include <iostream>
#include "function.h"
using namespace std;

int isSorted(State s) {
    int before = s.front();
    for(auto i : s)
        if(before > i)
            return 0;
        else
        	before = i;
    return 1;
}

set<State> SwapSort::extend(State s) {
    set<State> SS;
    State tmp = s;

    tmp[0] = tmp[0] + tmp[1];
    tmp[1] = tmp[0] - tmp[1];
    tmp[0] = tmp[0] - tmp[1];

    s.front() = s.front() + s.back();
    s.back() = s.front() - s.back();
    s.front() = s.front() - s.back();

    SS.insert(tmp);
    SS.insert(s);

    return SS;
}

void SwapSort::solve(int steps)
    {
        while (steps > 0) {
            set<list<State>> newPaths;
            set<list<State>> oldPaths;

            for (auto p : _paths) {
                _explored.insert(p.back());//last elem. of p
                auto nextStates = extend(p.back());
                for (auto s : nextStates) {
                    if (isSorted(s)) {
                        auto np = p;
                        np.push_back(s);
                        _solutions.insert(np);
                    } else {
                        auto search = _explored.find(s);
                        if (search == _explored.cend()) {
                            auto np = p;
                            np.push_back(s);
                            newPaths.insert(np);
                        }
                    }
                }
                oldPaths.insert(p);
            }

            for (auto p : oldPaths) {
                _paths.erase(p);
            }
            for (auto p : newPaths) {
                _paths.insert(p);
            }
            --steps;
        }

    }
