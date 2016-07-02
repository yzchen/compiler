CC := clang++  -std=c++11 -g
LEX := lex
YACC := bison
CFLAGS := -Iinclude -Wno-duplicate-decl-specifier
YFLAGS :=
LFLAGS :=
LLVMFLAGS := `llvm-config --system-libs --cxxflags --libs all` `llvm-config --ldflags`
# LLVMFLAGS := `llvm-config --system-libs --cxxflags --libs core mcjit native` `llvm-config --ldflags`

all: bin/parser

bin/parser: bin/lexer.o bin/parser.o bin/main.o bin/util.o bin/global.o bin/node.o bin/codegen.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^ -rdynamic $(LLVMFLAGS)

src/parser.cc include/tok.hh: config/parser.y
	$(YACC) $(YFLAGS) -v --defines=include/tok.hh -o src/parser.cc $<

bin/parser.o: src/parser.cc include/node.hh include/util.hh include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

src/lexer.cc: config/lexer.l
	$(LEX) $(LFLAGS) -o $@ $<

bin/lexer.o: src/lexer.cc include/tok.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/node.o: src/node.cc include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/main.o: src/main.cc include/tok.hh include/util.hh include/global.hh include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/util.o: src/util.cc include/util.hh include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/global.o: src/global.cc include/global.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/codegen.o: src/codegen.cc include/node.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $< -ferror-limit=1000 -Wno-return-type

.PHONY: clean
clean:
	rm -f bin/*.o src/lexer.cc src/parser.cc include/tok.hh
	rm -f *.png *.dot
	rm -f test/*.ll test/*.a test/*.o test/*.~ test/*~
	rm -f *~ .*~
