
eac.out: lex.yy.c
	# compile
	gcc lex.yy.c y.tab.c

# generate lexical code
lex.yy.c:
	lex lexer.l

# generate sintax code
y.tab.c:
	yacc -d parser.y

run: eac.out
	./eac.out

clean:
	rm -f y.tab.c lex.yy.c eac.out


