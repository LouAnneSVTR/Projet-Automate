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

    automaton automaton::determine() const {

        if (is_deterministic()) {return *this;}

        std::string newName;              // Nouveau nom de l'automate déterministe
        set<int> newInitials;             // Ensemble des états initiaux de l'automate déterministe
        set<int> newFinals;               // Ensemble des états finaux de l'automate déterministe
        set<transition> newTransitions;   // Ensemble des transitions de l'automate déterministe
        std::vector<set<int>> newStates;

        newStates.push_back(epsilon_accessible(this->initials)); // newStates[0] : nouvel état initial = sous-ensemble {anciens états initiaux + e-accessible}

        newInitials = {0};
        set<char> alphabet = this->get_alphabet();

        for(int i = 0; i < newStates.size(); i++) {

            for (char a : alphabet) {

                set<int> newSet;
                newSet |= accessible(newStates[i], a);

                if (newSet.size() > 0) { // s'il existe au moins une transition

                    bool notFound = true;
                    int k = 0;

                    while (notFound && k < newStates.size()) {
                        if (newStates[k] == newSet) {
                            notFound = false;
                        } else {
                            k++;
                        }
                    }
                    if (notFound) {
                        newStates.push_back(newSet); // on ajoute le nouveau sous-ensemble
                        newTransitions |= transition(i, a, newStates.size() -1); // on crée la nouvelle transition de l'automate déterministe
                        bool final;
                        for (int s : newSet) {
                            final = this->finals.contains(s);
                            if (final) {
                                newFinals |= newStates.size() - 1;
                            }
                        }
                    } else {
                        newTransitions |= transition(i, a,
                                                     k);// on crée la nouvelle transition de l'automate déterministe
                    }

                }
            }
        }

        automaton newAutomaton = automaton();
        newAutomaton.initials = newInitials;
        newAutomaton.finals = newFinals;
        newAutomaton.transitions = newTransitions;
        newAutomaton.name = this->name + "det";
        return newAutomaton;
    }

    return 0;


}
