CXXFLAGS = -std=c++17 -Wall
GMOCK_PATH = googletest/googletest/include/gest/

main: main.o lexer.o 
	clang $(CXXFLAGS) -lstdc++ objs/main.o objs/lexer.o -o bin/main

main.o: main/main.cpp lexer/lexer.h main/compiler.h
	clang $(CXXFLAGS) -Ilexer/ main/main.cpp -c -o objs/main.o

lexer.o: lexer/lexer.cpp lexer/lexer.h
	clang $(CXXFLAGS) lexer/lexer.cpp -c -o objs/lexer.o

gmock:
	cmake -Bgoogletest/build -Sgoogletest/
	make -C googletest/build

run:
	./bin/main
clean:
	rm -rf bin/*
	rm -rf objs/*
	rm -rf googletest/build