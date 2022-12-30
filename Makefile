  
CPPFLAGS += -std=c++17 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

# compile parser
src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

# compile lexer
src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

# make a new bin/c_compiler new script
bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

# compile compiler, linking parser and lexer
bin/compiler : src/compiler.o src/parser.tab.o src/lexer.yy.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^
	
clean :
	rm -f src/*.o
	rm -f bin/*
	rm -f compiler_tests/out/*/*
	rm src/*.output
	rm src/*.tab.hpp
	rm src/*.tab.cpp
	rm src/*.yy.cpp
	
	
