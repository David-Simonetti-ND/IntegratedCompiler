CXXFLAGS = -std=c++17 -Wall
GMOCK_PATH = googletest/googletest/include/gest/

main: main.o nfa.o 
	clang $(CXXFLAGS) -lstdc++ objs/main.o objs/nfa.o -o bin/main

main.o: main/main.cpp lexer/nfa.h main/compiler.h
	clang $(CXXFLAGS) -Ilexer/ main/main.cpp -c -o objs/main.o

test_nfa: nfa.o lexer/nfa.h lexer/test_nfa.cpp
	clang $(CXXFLAGS) -lstdc++ -Lgoogletest/build/lib -Igoogletest/googletest/include -Igoogletest/googletest/include/gtest -lgtest objs/nfa.o lexer/test_nfa.cpp -o bin/test_nfa

nfa.o: lexer/nfa.cpp lexer/nfa.h lexer/automata.h
	clang $(CXXFLAGS) lexer/nfa.cpp -c -o objs/nfa.o

test_dfa: dfa.o lexer/dfa.h lexer/test_dfa.cpp nfa.o
	clang $(CXXFLAGS) -lstdc++ -Lgoogletest/build/lib -Igoogletest/googletest/include -Igoogletest/googletest/include/gtest -lgtest objs/dfa.o objs/nfa.o lexer/test_dfa.cpp -o bin/test_dfa

dfa.o: lexer/dfa.cpp lexer/dfa.h lexer/automata.h
	clang $(CXXFLAGS) lexer/dfa.cpp -c -o objs/dfa.o

gtest:
	cmake -Bgoogletest/build -Sgoogletest/
	make -C googletest/build

clean_gtest:
	rm -rf googletest/build

run:
	./bin/main


clean:
	rm -rf bin/*
	rm -rf objs/*