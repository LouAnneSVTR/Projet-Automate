/**
 * \file automaton.cpp
 * \brief Implementation file containing the code for the functions that could not be implemented in "automaton.hpp"
 * \author Matthieu Perrin 
 * \version 1
 * \date 11-16-2020
 */

#include "automaton.hpp"
#include "set.hpp"
#include <iostream>

using namespace univ_nantes;

automaton automaton::determine() const {
  /*
   * TODO: Question 1. retourner un automate déterminisé équivalent
   * 
   * indice : utiliser un objet de type std::vector<set<int>> pour stocker
   * les ensembles d'états créés par l'algorithme de déterminisation. 
   * Les états de l'automate déterministe retourné seront les indices 
   * des ensembles d'états dans le vecteur.
  */
  /*  univ_nantes::vector<set<int>> etats;
  if ( automaton.is_deterministic ) {
      univ_nantes::cout << "Cet automate est déjà deterministe, il est inutile d'appliquer la fonction ! " << endl;
  } else {
      //TODO 1- INSERER dans le 1er SET du vector d'état deterministe, tous les etats INITIAUX de l'automate de base
      // ainsi que les états reliés par des E-transitions

      //TODO 2- Trouver un moyen de choper les elements pour regrouper les transitions du futur automate

      //TODO 3- RECREER en commencer a partir de l'éatat initial tous les nouveaux etats de l'automate determiniqtes
      // todo → faire attention a pendre les états qui menent vers les bonnes transiont avec le bon carac ET permi eux, ajouter leur E-transitions
      //todo → Faire attention a ne pas recreer un état de l'automate deterministe deja existant dans le vector de set ETATS

      //TODO 4- RECREER les transitions de l'automate, PAS 2 TRANSITION PAREILS
  }
  return *this;*/
}


/*
 * Gets whether the automaton is deterministic or not
 *
 * An automaton is considered to be deterministic if, and only if, it has exactly one initial state, no epsilon-transition, 
 * and no two transitions starting in the same state and ending in a different states, with a different label.
 */
bool automaton::is_deterministic() const {
    // Check that there is a unique initial state
    if(initials.size() != 1) return false;
    for(transition t1 : transitions) {
        // Check that there is no epsilon transition
        if(t1.is_epsilon()) return false;
        for(transition t2 : transitions) {
            // Check that there are no two transitions starting in the same state, with the same label
            if(t1.start == t2.start && t1.terminal == t2.terminal && t1.end != t2.end) return false;
        }
    }
    return true;
}

/**
 * Gets the set of states accessible from some state in from by following epsilon transitions
 * 
 * A state y is included in the returned set if, and only if, there exists a state x in from 
 * and a sequence of states x0=x, x1, ..., xn = y such that each epsilon-transition xi |--> x(i+1)
 * is contained in transitions.
 *
 * Example : a.epsilon_accessible(a.initials) returns all states accessible in a, through the empty word. 
 */
set<int> automaton::epsilon_accessible(set<int> from) const {
  set<int> result = from;
  bool go_on = true;
  while (go_on) {
    go_on = false;
    for(transition t : transitions) {
      if(result.contains(t.start) && t.terminal == '\0' && !result.contains(t.end)) {
	result |= t.end;
	go_on = true;
      }
    }
  }
  return result;
}

/**
 * Gets the set of states accessible from some state in from by following one transition labeled by c 
 *
 * A state y is included in the returned set if, and only if, there exists a state x in from 
 * such that x |-c-> y is contained in transitions.
 *
 * Example : a.epsilon_accessible(a.accessible(a.epsilon_accessible({1,2}),'a')) returns all states accessible in a, from states 1 or 2, through the word "a". 
 */
set<int> automaton::accessible(set<int> from, char c) const {
  set<int> result;
  for(transition t : transitions) {
    if(from.contains(t.start) && t.terminal == c)
      result |= t.end;
  }
  return result;
}

/*
 * Returns the set of states of the automaton, including all states accessible from the initial states
 *
 * A state is contained in the set returned if it is contained in initials, finals, or at the start or and of any transition.
 */
set<int> automaton::get_states() const {
  set<int> states = initials | finals;
  for(transition t : transitions)
    states |= {t.start, t.end};
  return states;
}

/*
 * Returns the set of terminal symbols (lower-case letters) that label at least one transition of the automaton
 */
set<char> automaton::get_alphabet() const {
  set<char> alphabet;
  for(transition t : transitions)
    if(!t.is_epsilon())
      alphabet |= {t.terminal};
  return alphabet;
}
