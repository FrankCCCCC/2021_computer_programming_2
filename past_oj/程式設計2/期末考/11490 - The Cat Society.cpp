#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//enum Occupation{elder, nursy, kitty, warrior, apprentice, medicent, deputy, leader};

struct Cat
{
    string name;
    //Occupation occupation;
    //string occupation;
    int order;
    int age;
};

bool cmp(const Cat a, const Cat b)
{
    if (a.order > b.order)
        return 0;
    else if (a.order < b.order)
        return 1;
    else {
        if (a.order==4){
            if (a.age > b.age)
                return 0;
            else if (a.age < b.age)
                return 1;
            else {
                return a.name < b.name;
            }
        }
        else {
            if (a.age > b.age)
                return 1;
            else if (a.age < b.age)
                return 0;
            else {
                return a.name < b.name;
            }
        }
    }
}

int main()
{
    int N, food;
    string occupation;
    while (cin>>N) {
        cin >> food;
        Cat cat[N];
        //vector<Cat> v;
        //vector<Cat>::iterator it;
        for(int i=0; i<N; i++) {
            cin >> cat[i].name >> occupation >> cat[i].age;
            if (occupation=="elder")
                cat[i].order = 0;
            else if (occupation=="nursy")
                cat[i].order = 1;
            else if (occupation=="kitty")
                cat[i].order = 2;
            else if (occupation=="warrior")
                cat[i].order = 3;
            else if (occupation=="apprentice")
                cat[i].order = 4;
            else if (occupation=="medicent")
                cat[i].order = 5;
            else if (occupation=="deputy")
                cat[i].order = 6;
            else if (occupation=="leader")
                cat[i].order = 7;
            //v.push_back(cat);
        }
        //debug
        /*cout << endl;
        for (it=v.begin(); it!=v.end(); it++){
            cout << it->name << " " << it->occupation << " " << it->age << " " << it->order <<endl;
        }
        cout << endl;*/

        //sort
        sort(cat, cat+N, cmp);

        //debug
        /*for (it=v.begin(); it!=v.end(); it++){
            cout << it->name << " " << it->occupation << " " << it->age << " " << it->order <<endl;
        }*/
        if (food > N) {
            for (int i=0; i<N; i++)
                cout << cat[i].name <<"\n";
            }
        else{
            for (int i=0; i<food; i++)
                cout << cat[i].name <<"\n";
        }
    }
}
