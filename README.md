# Easter Egg

## Requirements

* Yacc (Linux distros: [bison](https://www.gnu.org/software/bison/))
* Lex (Linux distros: [flex](https://github.com/westes/flex/))
* [GNU Make](https://www.gnu.org/software/make/)

## Basic commands

* generate lexical code

```bash
make lex.yy.c
```

* compile lexical without sintax

```bash
make eeg.lex
```

* create Descending Descending Recognizer (_portuguese_: _Reconhecedor Recursivo Descendente_) predictive parser

```bash
make eeg.pprrd
```

* create Table-Driven Recognizer (_portuguese_: _Reconhecedor Dirigido por uma Tabela_) predictive parser

```bash
make eeg.pprdt
```
