#include <iostream>
#include "set.hpp"
#include "automaton.hpp"

using namespace std;
using namespace univ_nantes;

int main() {

    automaton a;
    a.initials |= 0;
    a.finals |= 2;

    transition t1;
    t1.start = 0;
    t1.terminal = 'a';
    t1.end = 1;

    a.transitions |= t1;

    transition t2;
    t2.start = 0;
    t2.terminal = 'a';
    t2.end = 2;

    a.transitions |= t2;

    transition t3;
    t3.start = 1;
    t3.terminal = 'b';
    t3.end = 2;

    a.transitions |= t3;

    transition t4;
    t4.start = 1;
    t4.terminal = 'b';
    t4.end = 1;

    a.transitions |= t4;

    cout << a << endl;

    automaton b = a.determine();

    cout << b << endl;

    return 0;


}
