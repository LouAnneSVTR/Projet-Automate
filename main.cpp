#include <iostream>
#include "set.hpp"

using namespace std;

int main() {

    univ_nantes::set<int> s = {1, 2, 3, 4};
    univ_nantes::set<int> sBis = {50};

    std::vector<univ_nantes::set<int>> etats;

    etats[1] = s; //On insère dans le premier set tous les états initiaux du "this"

    //cout << sBis[0] << endl;

    //sBis = s;

    for ( int i = 0 ; i<= 3; i++ )
    {
        cout<< s[i] << endl;
    }

   /*cout << "\n" ;
   for ( int i = 0 ; i<= 3; i++ ){
        cout << sBis[i] << endl;
    }

    operator[](s.size());*/
    return 0;
}
