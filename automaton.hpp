#ifndef AUTOMATON_HPP_DEFINED
#define AUTOMATON_HPP_DEFINED

/**
 * \file automaton.hpp
 * \brief Header file containing the declaration of the transition and automaton types.
 * \author Matthieu Perrin 
 * \version 1
 * \date 11-16-2020
 */

#include "set.hpp"
#include <iostream>

/**
 * \namespace univ_nantes Protects all definitions in the LEA project
 */
namespace univ_nantes {

  /**
   * \struct transition automaton.hpp 
   * \brief Encodes transitions in an automaton
   * 
   * A transition is encoded as a tripple (start, terminal, end). Epsilon transitions are encoded as transitions with the character '\0' as terminal
   */
  struct transition {
  public:
    int  start;    /*!< State in which the transition can be activated. */
    char terminal; /*!< Label of the transition: the transition can be activated only when terminal is read. */
    int  end;      /*!< State in which the transition leads after it has been activated. */

    /**
     * \fn transition(int s, char t, int e)
     * \brief constructs a new transition
     * \param s State in which the transition can be activated
     * \param t Label of the transition
     * \param e State in which the transition leads after it has been activated
     */
    transition(int s, char t, int e) : start(s), terminal(t), end(e) {}
    /**
     * \fn transition(int s, int e)
     * \brief constructs a new epsilon transition
     * \param s State in which the transition can be activated
     * \param e State in which the transition leads after it has been activated
     */
    transition(int s, int e) : transition(s,'\0',e) { }
    /**
     * \fn transition()
     * \brief default constructor
     */
    transition() { }

    /**
     * \fn bool is_epsilon () const
     * \brief determines whether the transition is an epsilon transition or not
     * \return true if called on an epsilon transition, false otherwise
     */
    bool is_epsilon () const {return terminal == '\0';}

    /**
     * \fn bool operator== (const transition& t) const
     * \brief Compares two transitions
     * \param t a transition with which to compare *this
     * \return true if *this and t are the same transition, false otherwise
     *
     * Two transitions are considered equal if they have the same start and end states, and they are labelled by the same terminal.
     */
    bool operator== (const transition& t) const {
      return start==t.start && terminal == t.terminal && end == t.end;
    }

    /**
     * \fn friend std::ostream& operator<<(std::ostream& out, const transition& t)
     * \brief Inserts the description of the transition t into out
     * \param out ostream object where the transition is inserted.
     * \param t transition object with the content to insert.
     * \return The same as parameter out.
     * 
     * Examples: 
     * Textual display of a transition t(0, 'a', 1) is 
     * "0 |-a-> 1"
     *
     * Textual display of an epsilon transition t(0, 1) is 
     * "0 |--> 1"
     */
    friend std::ostream& operator<<(std::ostream& out, const transition& t) {
      return out << t.start << " |-" << t.terminal << "-> " << t.end;
    }
  };

  
  /**
   * \struct automaton automaton.hpp 
   * \brief Encodes non-deterministic finite state automata whose states are integers, and transitions are labelled by characters
   */
  struct automaton {
  public:
    std::string name;            /*!< Name of the automaton, or of the language recognized by the automaton. */
    set<int> initials;           /*!< Set of initial states of the automaton. */
    set<int> finals;             /*!< Set of final (a.k.a. accepting) states of the automaton. */
    set<transition> transitions; /*!< Set of transitions of the automaton. */

    /**
     * \fn set<int>  get_states() const
     * \brief Gets the set of states of the automaton
     * \return a set of states, including all states accessible from the initial states
     *
     * A state is contained in the set returned if it is contained in initials, finals, or at the start or and of any transition.
     */
    set<int>  get_states() const;

    /**
     * \fn set<char>  get_alphabet() const
     * \brief Gets the set of terminal symbols of the automaton
     * \return the set of lower-case letters that label at least one transition
     */
    set<char> get_alphabet() const;

    /**
     * \fn set<int> epsilon_accessible(set<int> from) const
     * \brief Gets the set of states accessible by following epsilon transitions
     * \param from a set of states of the automaton
     * \return the set of all states epsilon-accessible from some state in from
     * 
     * A state y is included in the returned set if, and only if, there exists a state x in from 
     * and a sequence of states x0=x, x1, ..., xn = y such that each epsilon-transition xi |--> x(i+1)
     * is contained in transitions.
     *
     * Example : a.epsilon_accessible(a.initials) returns all states accessible in a, through the empty word. 
     */
    set<int>  epsilon_accessible(set<int> from) const;

    /**
     * \fn set<int> accessible(set<int> from) const
     * \brief Gets the set of states accessible by following one transition 
     * \param from a set of states of the automaton
     * \param c a terminal character in the alphabet of the automaton
     * \return the set of all states accessible from some state in from, following a unique transition
     * 
     * A state y is included in the returned set if, and only if, there exists a state x in from 
     * such that x |-c-> y is contained in transitions.
     *
     * Example : a.epsilon_accessible(a.accessible(a.epsilon_accessible({1,2}),'a')) returns all states accessible in a, from states 1 or 2, through the word "a". 
     */
    set<int>  accessible(set<int> from, char c) const;

    set<char> caracteres() const;

    /**
     * \fn automaton determine() const
     * \brief Gets a new deterministic automaton that recognizes the same language
     * \return a deterministic automaton 
     *
     * TODO: Question 1. Complete the given implementation of this function! 
     */
    automaton determine() const;

    /**
     * \fn bool is_deterministic() const;
     * \brief Gets whether the automaton is deterministic or not
     * \return true if the automaton is deterministic, false otherwise
     *
     * An automaton is considered to be deterministic if, and only if, it has exactly one initial state, no epsilon-transition, 
     * and no two transitions starting in the same state and ending in a different states, with a different label.
     */
    bool      is_deterministic() const;
    
    /**
     * \fn bool operator== (const automaton& a) const
     * \brief Compares two automata.
     * \param a an automaton with which to compare *this
     * \return true if *this and a are the same automata, false otherwise
     *
     * Two automata are considered equal if they have the same name and sets of initial and final states, and transitions.
     * Set equality is defined by double inclusion (see univ_nantes::set).
     */
    bool operator== (const automaton& a) const {
      return name==a.name && initials == a.initials && finals==a.finals && transitions == a.transitions;
    }

    /**
     * \fn friend std::ostream& operator<<(std::ostream& out, const automaton& a)
     * \brief Inserts the description of the automaton a into out.
     * \param out ostream object where the automaton is inserted.
     * \param a automaton object with the content to insert.
     * \return The same as parameter out.
     * 
     * The format under which the automaton is displayed is the same as the input format expected in a .lea file
     */
    friend std::ostream& operator<<(std::ostream& out, const automaton& a) {
      out << a.name << " = { ";
      for(int i : a.initials) out << "initial " << i << "; ";
      for(int f : a.finals) out << "final " << f << "; ";
      for(transition t : a.transitions) out << t << "; ";
      return out << "}";
    }
  };
  
}

#endif // AUTOMATON_HPP_DEFINED
