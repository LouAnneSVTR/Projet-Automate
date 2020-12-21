#ifndef SET_HPP_DEFINED
#define SET_HPP_DEFINED

/**
 * \file automaton.hpp
 * \brief Header file containing the declaration of the set type.
 * \author Matthieu Perrin 
 * \version 1
 * \date 11-16-2020
 */

#include <vector>
#include <iostream>

namespace univ_nantes {

  /**
   * \class set set.hpp 
   * \brief Encodes a type to manipulate sets algebrically 
   * 
   * This class defines the operators | for the union, & for the intersection, and - for the set difference.
   * Let S1 and S2 be sets. In the following examples, we define set<int> S1 = {1, 2, 3}; set<int> S2 = {3, 4, 5};
   *   - set union: S1 | S2 represents the union of S1 and S2. 
   *                For example, S1 | S2 == {1, 2, 3, 4, 5}, and S1 |= S2 is the same as S1 = {1, 2, 3, 4, 5};
   *   - set intersection: S1 & S2 represents the intersection of S1 and S2. 
   *                For example, S1 & S2 == {1, 2, 3, 4, 5}, and S1 |= S2 is the same as S1 = {1, 2, 3, 4, 5};
   */
  template<typename T>
  class set {
  private:
    std::vector<T> internal; /*!< The set is encoded internally as a vector. */
  public:

    /**
     * \fn set()
     * \brief Default constructor
     *
     * creates an empty set
     */
    set() {}
    /**
     * \fn set(const set & e)
     * \brief copy constructor
     * \param e a set to copy
     *
     * Allows to write set<T> s = e;
     */
    set(const set & e) : internal(e.internal) { }
    /**
     * \fn set(const std::initializer_list<T> & c)
     * \brief Initializer list constructor
     * \param c the initializer list
     *
     * Allows to write set<T> s = {1, 2, 3, 4};
     */
    set(const std::initializer_list<T> & c) : internal(c) { }
    /**
     * \fn ~set() 
     * \brief Default destructor
     */
    ~set() {}

    /**
     * std::size_t size() const 
     * \brief Gets the number of elements in the set
     * \return The number of elements contained in the set
     */
    std::size_t size() const {
      return internal.size();
    }

    /**
     * bool contains(const T& x) const
     * \brief Gets whether an element is contained in the set
     * \param x an element that may be contained in the set or not
     * \return true if x is in the set, false otherwise
     */
    bool contains(const T& x) const {
      for(T y:internal)
	if (x==y) return true;
      return false;
    }
    
    /**
     * \fn const set& operator=(const set& e)
     * \brief assignation operator
     * \param e a set to copy
     * \return the same set
     *
     * Allows to write s = e;
     */
    const set& operator=(const set& e) {
      if (this != &e)
	internal = e.internal;
      return *this;
    }
    
    /**
     * \fn friend std::ostream& operator<<(std::ostream& out, const set& e)
     * \brief Inserts the description of the set e into out.
     * \param out ostream object where the set is inserted.
     * \param e set object with the content to insert.
     * \return The same as parameter out.
     * 
     * The set is displayed as an enumeration between braces, e.g. "{1, 2, 3}".
     */
    friend std::ostream& operator<<(std::ostream& out, const set& e) {
      out << "{" ;
      for(size_t i = 0; i < e.internal.size(); i++) {
	if(i!=0) out << ", ";
	out << e.internal[i];
      }
      return out << "}" ;
    }

    /**
     * \fn const T & operator[] (std::size_t i) const
     * \brief Gives a read-only access to elements in the set
     * \param i An integer index between 0 and size()-1
     * \return Some element in the set
     * 
     * Allows to write for(int i = 0; i<s.size(); ++i) cout << s[i];
     *
     * If i and j are valid indices,
     *    - s[i]==s[j] must return true if, and only if, i==j;
     *    - s.contains(s[i]) must return true.
     */
    const T & operator[] (std::size_t i) const {
      return internal[i];
    }

    /*********************************
     *            Set union          *
     *********************************/
    
    /**
     * \fn set& operator|=(const set& rhs)
     * \brief Inserts all elements of rhs into the set
     * \param rhs A set of elements to be inserted
     * \return The resulting set
     * 
     * Allows to write s1 |= s2, interpreted as "s1 = s1 union s2"
     */
    set& operator|=(const set& rhs) {
      for(T y : rhs.internal)
	if(!contains(y))
	  internal.push_back(y);
      return *this;
    }

    /**
     * \fn friend set operator|(set lhs, const set& rhs)
     * \brief Computes the union between lhs and rhs
     * \param lhs the first set in the union
     * \param rhs the second set in the union
     * \return The union of lhs and rhs
     * 
     * Allows to write s1 | s2, interpreted as "s1 union s2".
     */
    friend set operator|(set lhs, const set& rhs) { return lhs |= rhs; }

    /**
     * \fn set& operator|=(const T& rhs)
     * \brief Inserts rhs into the set
     * \param rhs A unique element to be inserted
     * \return The resulting set
     * 
     * Allows to write s1 |= x, interpreted as "s1 = s1 union {x}".
     */
    set& operator|=(const T& rhs) {
      if(!contains(rhs))
	internal.push_back(rhs);
      return *this;
    }

    /**
     * \fn friend set operator|(set lhs, const T& rhs)
     * \brief Computes the union between lhs and the set only containing rhs
     * \param lhs the first set in the union
     * \param rhs the value to add
     * \return The union of lhs and rhs
     * 
     * Allows to write s1 | x, interpreted as "s1 union {x}".
     */
    friend set operator|(set lhs, const T& rhs) { return lhs |= rhs; }
    
    /*********************************
     *      Set intersection         *
     *********************************/

    /**
     * \fn set& operator&=(const set& rhs)
     * \brief Removes from the set all elements that are not in rhs 
     * \param rhs A set of elements to be kept
     * \return The resulting set
     * 
     * Allows to write s1 &= s2, interpreted as "s1 = s1 intersection s2"
     */
    set& operator&=(const set& rhs) {
      std::vector<T> new_internal;
      for(T x : internal)
	if(rhs.contains(x))
	  new_internal.push_back(x);
      internal = new_internal;
      return *this;
    }

    /**
     * \fn friend set operator&(set lhs, const set& rhs)
     * \brief Computes the intersection between lhs and rhs
     * \param lhs the first set in the intersection
     * \param rhs the second set in the intersection
     * \return The intersection of lhs and rhs
     * 
     * Allows to write s1 & s2, interpreted as "s1 intersection s2".
     */
    friend set operator&(set lhs, const set& rhs) { return lhs &= rhs; }
 
    /**
     * \fn set& operator&=(const T& rhs)
     * \brief Removes all elements from the set, except rhs
     * \param rhs A unique element to be kept
     * \return The resulting set
     * 
     * Allows to write s1 &= x, interpreted as "s1 = s1 intersection {x}".
     */
    set& operator&=(const T& rhs) {
      if(contains(rhs))
	internal = std::vector<T>({rhs});
      else
	internal = std::vector<T>();
      return *this;
    }
    
    /**
     * \fn friend set operator&(set lhs, const T& rhs)
     * \brief returns {rhs} if lhs contains rhs, and the empty set otherwise
     * \param rhs A unique element to be kept in the intersection
     * \return The resulting set
     * 
     * Allows to write s1 & x, interpreted as "s1 intersection {x}".
     */
    friend set operator&(set lhs, const T& rhs) { return lhs &= rhs; }

    /*********************************
     *        Set difference         *
     *********************************/

    /**
     * \fn set& operator-=(const set& rhs)
     * \brief Removes from the set all elements in rhs 
     * \param rhs A set of elements to be removed
     * \return The resulting set
     * 
     * Allows to write s1 -= s2, interpreted as "s1 = s1 minus s2"
     */
    set& operator-=(const set& rhs) {
      std::vector<T> new_internal;
      for(T x : internal)
	if(!rhs.contains(x))
	  new_internal.push_back(x);
      internal = new_internal;
      return *this;
    }

    /**
     * \fn friend set operator-(set lhs, const set& rhs)
     * \brief Computes the set difference between lhs and rhs
     * \param lhs the first set in the set difference
     * \param rhs the second set in the set difference
     * \return The set difference of lhs and rhs
     * 
     * Allows to write s1 - s2, interpreted as "s1 minus s2".
     */
    friend set operator-(set lhs, const set& rhs) { return lhs -= rhs; }
 
    /**
     * \fn set& operator-=(const T& rhs)
     * \brief Removes rhs from the set
     * \param rhs A unique element to remove
     * \return The resulting set
     * 
     * Allows to write s1 -= x, interpreted as "s1 = s1 minus {x}".
     */
    set& operator-=(const T& rhs) {
      std::vector<T> new_internal;
      for(T x : internal)
	if(rhs != x)
	  new_internal.push_back(x);
      internal = new_internal;
      return *this;
    }

    /**
     * \fn friend set operator-(set lhs, const T& rhs)
     * \brief returns the set difference of lhs and {rhs}
     * \param lhs the first set in the set difference
     * \param rhs A unique element to remove in the set difference
     * \return The resulting set
     * 
     * Allows to write s1 - x, interpreted as "s1 = s1 minus {x}".
     */
    friend set operator-(set lhs, const T& rhs) { return lhs -= rhs; }

    
    /*********************************
     *        Set comparison         *
     *********************************/

    /**
     * \fn friend bool operator<= (const set& lhs, const set& rhs)
     * \brief compares whether lhs is included into, or equal to, rhs
     * \param lhs the left hand side set in the comparison
     * \param rhs the right hand side set in the comparison
     * \return true if lhs in included into, or equal to, rhs; false otherwise
     * 
     * Allows to write s1 <= s2, interpreted as "s1 included into s2".
     */
    friend bool operator<= (const set& lhs, const set& rhs) {
      for(T x : lhs.internal)
	if(!rhs.contains(x))
	  return false;
      return true;
    }

    /**
     * \fn friend bool operator== (const set& lhs, const set& rhs)
     * \brief compares whether lhs and rhs contain the same elements
     * \param lhs the left hand side set in the comparison
     * \param rhs the right hand side set in the comparison
     * \return true if lhs and rhs contain the same elements; false otherwise
     * 
     * Allows to write s1 == s2, interpreted as "s1 equals s2".
     */
    friend bool operator== (const set& lhs, const set& rhs){ return lhs <= rhs && rhs <= lhs; }

    /**
     * \fn friend bool operator!= (const set& lhs, const set& rhs)
     * \brief compares whether lhs and rhs contain different elements
     * \param lhs the left hand side set in the comparison
     * \param rhs the right hand side set in the comparison
     * \return true if lhs and rhs contain different elements; false otherwise
     * 
     * Allows to write s1 != s2, interpreted as "s1 not equals to s2".
     */
    friend bool operator!= (const set& lhs, const set& rhs){ return !(lhs <= rhs) || !(rhs <= lhs); }

    /**
     * \fn friend bool operator>= (const set& lhs, const set& rhs)
     * \brief compares whether rhs is included into, or equal to, lhs
     * \param lhs the left hand side set in the comparison
     * \param rhs the right hand side set in the comparison
     * \return true if rhs in included into, or equal to, lhs; false otherwise
     * 
     * Allows to write s1 >= s2, interpreted as "s2 included into s1".
     */
    friend bool operator>= (const set& lhs, const set& rhs){ return rhs <= lhs; }

    /**
     * \fn friend bool operator< (const set& lhs, const set& rhs)
     * \brief compares whether lhs is strictly included into rhs
     * \param lhs the left hand side set in the comparison
     * \param rhs the right hand side set in the comparison
     * \return true if lhs is strictly included into rhs; false otherwise
     * 
     * Allows to write s1 < s2, interpreted as "s1 strictly included into s2".
     */
    friend bool operator<  (const set& lhs, const set& rhs){ return lhs <= rhs && !(rhs <= lhs); }

    /**
     * \fn friend bool operator> (const set& lhs, const set& rhs)
     * \brief compares whether rhs is strictly included into lhs
     * \param lhs the left hand side set in the comparison
     * \param rhs the right hand side set in the comparison
     * \return true if rhs is strictly included into rhs; false otherwise
     * 
     * Allows to write s1 > s2, interpreted as "s2 strictly included into s1".
     */
    friend bool operator>  (const set& lhs, const set& rhs){ return rhs <= lhs && !(lhs <= rhs); }

    /**
     * \fn auto begin() const
     * \brief Returns an iterator pointing to the first element in the set.
     * \return e An iterator to the beginning of the container.
     *
     * Necessary to write : for(T x : s), where s is of type set<T>
     */
    auto begin() const {return internal.begin();}
    /**
     * \fn auto end() const
     * \brief Returns an iterator referring to the past-the-end element in the set
     * \return e An iterator to the element past the end of the sequence.
     *
     * Necessary to write : for(T x : s), where s is of type set<T>
     */
    auto end() const {return internal.end();}
  };

}

#endif // SET_HPP_DEFINED
