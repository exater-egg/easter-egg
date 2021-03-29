OBJDIR=obj
SRCDIR=src
BINDIR=bin
LIBDIR=lib
APPDIR=app

BIN=eeg

PPRRD_DIR=predictive_parser_ll1_rrd
PPRRD_LIBDIR=$(PPRRD_DIR)/lib
PPRRD_SRCDIR=$(PPRRD_DIR)/src
PPRRD_OBJDIR=$(PPRRD_DIR)/obj
PPRRD_BINDIR=$(PPRRD_DIR)/bin
PPRRD_APPDIR=$(PPRRD_DIR)/app

PPRRD_APP=$(PPRRD_APPDIR)/*.c

PPRDT_DIR=predictive_parser_ll1_rdt
PPRDT_LIBDIR=$(PPRDT_DIR)/lib
PPRDT_SRCDIR=$(PPRDT_DIR)/src
PPRDT_OBJDIR=$(PPRDT_DIR)/obj
PPRDT_BINDIR=$(PPRDT_DIR)/bin
PPRDT_APPDIR=$(PPRDT_DIR)/app

PPRDT_APP=$(PPRDT_APPDIR)/*.c

_DIRS=$(OBJDIR) $(BINDIR) $(PPRRD_OBJDIR) $(PPRRD_BINDIR) $(PPRDT_OBJDIR) $(PPRDT_BINDIR)

_OBJS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(_OBJS))

_PPRRD_OBJS=$(wildcard $(PPRRD_SRCDIR)/*.c)
PPRRD_OBJS=$(patsubst $(PPRRD_SRCDIR)/%.c,$(PPRRD_OBJDIR)/%.o,$(_PPRRD_OBJS))

_PPRDT_OBJS=$(wildcard $(PPRDT_SRCDIR)/*.c)
PPRDT_OBJS=$(patsubst $(PPRDT_SRCDIR)/%.c,$(PPRDT_OBJDIR)/%.o,$(_PPRDT_OBJS))

ALLOBJS=$(OBJS) $(PPRRD_OBJS) $(PPRDT_OBJS)

all: $(BIN).out

$(BIN).out: lex.yy.o y.tab.c
	# compile
	gcc lex.yy.o y.tab.c -o $@

$(BIN).lex: lex.yy.c $(OBJS)
	gcc lex.yy.c $(OBJS) -I ./ -I $(LIBDIR) -lfl -D YY_SKIP_YYWRAP -o $@

lex.yy.o: lex.yy.c
	gcc -c -I ./ -I $(LIBDIR) $< -o $@

# generate lexical code
lex.yy.c:
	lex --header-file=lex.yy.h lexer.l 

# generate sintax code
y.tab.c:
	yacc -d syntax_rules.y

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	gcc -c -I ./ -I $(LIBDIR) $< -o $@

$(BIN).pprrd: lex.yy.o mkdirs $(PPRRD_OBJS) $(OBJS)
	gcc $(PPRRD_APP) $(PPRRD_OBJS) $(OBJS) lex.yy.o -I ./ -I $(LIBDIR) -I $(PPRRD_LIBDIR) -o $@

$(BIN).pprdt: lex.yy.o mkdirs $(PPRDT_OBJS) $(OBJS)
	gcc $(PPRDT_APP) $(PPRDT_OBJS) $(OBJS) lex.yy.o -I ./ -I $(LIBDIR) -I $(PPRDT_LIBDIR) -o $@

$(PPRRD_OBJDIR)/%.o : $(PPRRD_SRCDIR)/%.c
	gcc -c -I ./ -I $(LIBDIR) -I $(PPRRD_LIBDIR) $< -o $@

$(PPRDT_OBJDIR)/%.o : $(PPRDT_SRCDIR)/%.c
	gcc -c -I ./ -I $(LIBDIR) -I $(PPRDT_LIBDIR) $< -o $@

mkdirs:
	mkdir -p $(_DIRS)

run: $(BIN).out
	./$(BIN).out

clean:
	rm -f y.tab.c lex.yy.c lex.yy.h lex.yy.o $(BIN).* $(ALLOBJS)
