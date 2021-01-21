# Easter Egg

## Requirements

* Yacc (Linux distros: bison)
* Lex (Linux distros: flex)

## Basic commands

* generate lexical code

```bash
lex <file>.l
```

* compile lexical without sintax

```bash
gcc lex.yy.c -ll
```

* generate sintax code

```bash
yacc -d <file>.y
```

* compile

```bash
gcc lex.yy.c y.tab.c
```

