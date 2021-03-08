all: eac.out

eac.out: lex.yy.c y.tab.c
	# compile
	gcc lex.yy.c y.tab.c -o $@

eac.lex: lex.yy.c
	gcc lex.yy.c -lfl -I ./ -o $@

# generate lexical code
lex.yy.c:
	lex --header-file=lex.yy.h lexer.l 

# generate sintax code
y.tab.c:
	yacc -d parser.y

run: eac.out
	./eac.out

clean:
	rm -f y.tab.c lex.yy.c eac.out


