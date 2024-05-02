#include <iostream>
#include <vector>

using namespace std;

class Base{
public:
    virtual void foo(int arg=5) = 0;
    virtual void onlyD2() = 0;
};

class D1 : public Base{
public:
    D1(){};
    void foo(int arg = 0) override{
        cout<<"not overloaded ver"<<endl;
    }
    void onlyD2()override{};

};

class D2 : public Base{
public:
    D2(){};
    void foo(int arg) override{
        cout<<"not overloaded ver: param: "<<arg<<endl;
    }

    void onlyD2()override{
        cout<<"this is from inheritance"<<endl;
    }

};

#include "systems/collisionSystem.h"
#include "systems/entitySystem.h"
int main(){
//    D1 ob1;
//    D2 ob2;
//    ob1.foo();
//    ob2.foo(3);
//
//    vector<Base*> collection;
//    collection.push_back(&ob2);
//    collection[0]->onlyD2();
vector<vector<int>> map = {
        {0,1,1},
        {1,0,1},
        {1,1,0}
};

Entity ent0;
Entity ent1(5);
CollisionSystem system(map);
system.occupancyMap[pair(0,1)].first = &ent0;
    system.occupancyMap[pair(1,1)].first = &ent0;
cout << system.occupancyMap[pair(0,1)].first->id<<" shld be 3"<<endl;
    cout << system.occupancyMap[pair(1,1)].first->id<<" shld be 5"<<endl;
    return 0;
}