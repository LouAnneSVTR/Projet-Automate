/**
 * \file lea.cpp
 * \brief File containing the main function of the program 
 * \author Matthieu Perrin 
 * \version 1
 * \date 11-16-2020
 */

#include "automaton.hpp"
#include "set.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace univ_nantes;
using namespace std;

/**
 * \fn set<automaton> read_lea_file(char* file)
 * \brief Parses the lea file whose name is file 
 * \param file the name of the input file
 * \return a set of automata, recognizing languages in the input file
 *
 * This functions is implemented in File parser.yxx 
 */
set<automaton> read_lea_file(char* file);

/**
 * \fn bool check(set<automaton> automata)
 * \brief Checks that the automata are well-formed to generate the output file 
 * \param automata the set of automata to check
 * \return true if everything is correct
 *
 * This functions does the following checks:
 * 1) There is at least one automaton
 * 2) all automata are deterministic
 * 3) all automata have a name
 * 4) all automata have a different name
 */
bool check(set<automaton> automata);

/**
 * \fn void generate_c_file(ostream & out, set<automaton> automata)
 * \brief Generates the c code executing the given automata
 * \param out the stream in which the c code must be included
 * \param automata the set of automata to print
 */
void generate_c_file(ostream& out, set<automaton> automata);


/**
 * \fn int main(int argc, char *argv[])
 * \brief Starts the program
 * \param argc number of arguments in the command line
 * \param argv arguments in the command line
 * \return a potential error code 
 */
int main(int argc, char *argv[]) {
  set<automaton> automata;
  string output = "output.c";

  // Read the arguments in the command line
  for(int i = 1; i<argc; i++) {
    if(argv[i][0]=='-') {
      // Interpret the option
      for(char* option = argv[i]+1; *option!='\0'; option++) {
	if(*option=='o') { // -o option: used to define an output file
	  output = (string)argv[i+1];
	  i++;
	} else if(*option=='h') { // -h option: prints the help
	  cout << "usage example: ./lea input.lea -o output.c" << endl;
	}
      }
    } else {
      // Read the input file (read_automata_file is implemented in parser.y)
      automata |= read_lea_file(argv[i]);

    }
  }

    cout << automata << endl;
  // Make additionnal verifications on the validity of the automata
  if(!check(automata)) {
    exit(1);
  }

  // Generate c output
  ofstream file;
  file.open (output);
  generate_c_file(file, automata);
  file.close();
}

bool check(set<automaton> automata) {
  bool is_correct = true;
  if(automata.size() == 0) {
    // Check that there are automata
    cerr << "erreur : aucun automate n'a été reconnu" << endl;
    is_correct = false;
  }
  for(size_t i = 0; i<automata.size(); ++i) {
    // Check that all automata are deterministic
    if(!automata[i].is_deterministic()) {
      cerr << "erreur : l'automate " << automata[i].name << " n'est pas déterministe" << endl;
      is_correct = false;
    }
    // Check that all automata have a name
    if(automata[i].name == "") {
      cerr << "erreur : un automate n'a pas de nom" << endl;
      is_correct = false;
    }
    // Check that all automata have a different name
    for(size_t j = i+1; j<automata.size(); ++j) {
      if(automata[i].name == automata[j].name) {
	cerr << "erreur : deux automates portent le nom " << automata[i].name << endl;
	is_correct = false;
      }
    }
  }
  return is_correct;
}

void generate_c_file(ostream & out, set<automaton> automata) {
  out   << "#include <stdio.h>\n\n"
    
        << "int main(int argc, char** argv){\n"
	<< "  char c;\n\n"
    
	<< "  // États internes des automates\n";
  for(automaton a : automata)
    out << "  int " << a.name << "=" << a.initials[0] << ";\n";
  out   << "  \n"
	<< "  while((c = fgetc(stdin)) != EOF) {\n\n";

  for(automaton a : automata){

    out << "    // Automate reconnaissant "<< a.name <<"\n"
	<< "    if (c == '\\n'"; for(int f:a.finals)out<<" && "<<a.name<<"!="<<f; out << ")\tprintf(\"non \");\n"
	<< "    if (c == '\\n')\t\t{printf(\"reconnu par " << a.name << "\\n\"); " << a.name << " = " << a.initials[0] << ";}\n";
    for(transition t : a.transitions)
      out<<"    else if(" << a.name << "==" << t.start << " && c=='" << t.terminal <<"')\t" << a.name << " = " << t.end << ";\n";
    out << "    else if(c!=' ' && c!='\\t')\t" << a.name << " = -1;\n\n";
  }

  out   << "  }\n"
	<< "  return 0;\n"
	<< "}\n";
}

