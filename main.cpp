#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"
#include "LO.h"
#include "Iterator.h"
#include <cassert>
#include <string>

bool f(TElement e1, TElement e2){
    return e1<=e2;
}

int main(){
    testAll();
    testAllExtins();
    std::cout<<"Finished LI Tests!"<<std::endl;


    LO l(f);
    l.adauga(7);
    l.adauga(5);
    l.adauga(4);
    l.adauga(3);
    l.adauga(6);
    l.adauga(1);
    l.adauga(2);


    for(Iterator i = l.iterator(); i.valid(); i.urmator())
        std::cout<<i.element()<<' ';
    std::cout<<'\n';

    try {
        l.eliminaDinKInK(0);
        assert(false);
    }
    catch(std::runtime_error&) {
        assert(true);
    }

    int nr = l.eliminaDinKInK(2);
    assert(nr == 4);
    for(Iterator i = l.iterator(); i.valid(); i.urmator())
        std::cout<<i.element()<<' ';
}