CXX = g++
GCC = gcc
LEX = flex
YACC = bison

CXXFLAGS = -W -Wall -Wextra -g
LDFLAGS = -ll -lm

HEADERS = automaton.hpp set.hpp 
OBJ = lea.o automaton.o lexer.o parser.o

LEA_C := $(patsubst %.lea,%.c,$(wildcard *.lea))
LEA_EXE := $(patsubst %.lea,%.exe,$(wildcard *.lea))

.PHONY: init all clean cleanall

init: lea

all: lea $(LEA_EXE)

# Generate lexer and parser

parser.cpp: parser.yxx
	$(YACC) --output=parser.cpp --defines=parser.hpp parser.yxx

lexer.cpp: lexer.l
	$(LEX) -olexer.cpp lexer.l 

# Compile c++ files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Link executable

lea: parser.cpp lexer.cpp $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

# Compile .lea files

%.c: %.lea lea
	./lea $< -o $@

%.exe: %.c
	$(GCC) -o $@ $<

# Delete generated files

clean:
	rm -f $(OBJ) lexer.cpp parser.cpp parser.hpp $(LEA_C) *~

cleanall: clean
	rm -f lea $(LEA_EXE)
