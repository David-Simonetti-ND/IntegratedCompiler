CXXFLAGS = -std=c++17 -Wall
GTEST_LIBS = -Lgoogletest/build/lib -Igoogletest/googletest/include -Igoogletest/googletest/include/gtest -lgtest 

RE_H = lexer/include/re.h
NFA_H = lexer/include/nfa.h
DFA_H = lexer/include/dfa.h
AUTOMATA_H = lexer/include/automata.h
LEXER_INCLUDE = -Ilexer/include

#####################  MAIN  ##########################

main: main.o nfa.o 
	clang $(CXXFLAGS) -lstdc++ objs/main.o objs/nfa.o -o bin/main

main.o: main/main.cpp $(NFA_H) main/compiler.h
	clang $(CXXFLAGS) $(LEXER_INCLUDE) main/main.cpp -c -o objs/main.o

run:
	./bin/main

##################### LEXER ###########################

# Lexer tests

test_re: re.o $(RE_H) lexer/test/test_re.cpp
	clang $(CXXFLAGS) -lstdc++ $(GTEST_LIBS) $(LEXER_INCLUDE) objs/re.o lexer/test/test_re.cpp -o bin/test_re

test_nfa: nfa.o $(NFA_H) lexer/test/test_nfa.cpp
	clang $(CXXFLAGS) -lstdc++ $(GTEST_LIBS) $(LEXER_INCLUDE) objs/nfa.o lexer/test/test_nfa.cpp -o bin/test_nfa

test_dfa: dfa.o $(DFA_H) lexer/test/test_dfa.cpp nfa.o
	clang $(CXXFLAGS) -lstdc++ $(GTEST_LIBS) $(LEXER_INCLUDE) objs/dfa.o objs/nfa.o lexer/test/test_dfa.cpp -o bin/test_dfa

nfa_dfa_speed_test: dfa.o nfa.o $(DFA_H) $(NFA_H) lexer/test/nfa_dfa_speed_test.cpp
	clang $(CXXFLAGS) -lstdc++ $(GTEST_LIBS) $(LEXER_INCLUDE) objs/dfa.o objs/nfa.o lexer/test/nfa_dfa_speed_test.cpp -o bin/nfa_dfa_speed_test

# Lexer objects

re.o: lexer/src/re.cpp $(RE_H)
	clang $(CXXFLAGS) $(LEXER_INCLUDE) lexer/src/re.cpp -c -o objs/re.o

nfa.o: lexer/src/nfa.cpp $(NFA_H) $(AUTOMATA_H)
	clang $(CXXFLAGS) $(LEXER_INCLUDE) lexer/src/nfa.cpp -c -o objs/nfa.o

dfa.o: lexer/src/dfa.cpp $(DFA_H) $(AUTOMATA_H)
	clang $(CXXFLAGS) $(LEXER_INCLUDE) lexer/src/dfa.cpp -c -o objs/dfa.o

###################### GTEST ###########################

gtest:
	cmake -Bgoogletest/build -Sgoogletest/
	make -C googletest/build

clean_gtest:
	rm -rf googletest/build

# clean

clean:
	rm -rf bin/*
	rm -rf objs/*