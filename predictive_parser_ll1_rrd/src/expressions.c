#include "expressions.h"

// Const -> Num | Ids | strLit | boolLit | SignedConst | ArrayLit | null .
void Const(void)
{
    int expected_tokens[] = {ID, STRING_LITERAL, NULL_TOK, INT_LITERAL, BOOLEAN_LITERAL, FLOAT_LITERAL, '+', '-', '['};
    switch (tok)
    {
    case STRING_LITERAL:
        eat(STRING_LITERAL);
        return;
    case BOOLEAN_LITERAL:
        eat(BOOLEAN_LITERAL);
        return;
    case NULL_TOK:
        eat(NULL_TOK);
        return;
    case INT_LITERAL:
    case FLOAT_LITERAL:
        Num();
        return;
    case ID:
    case THIS:
        Ids();
        return;
    case '[':
        ArrayLit();
        return;
    case '+':
    case '-':
        SignedConst();
        return;

    // follows - non-nullable
    case '*':
    case '/':
    case MOD:
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case TO:
    case THEN:
    case DO:
    case END_TOK:
    case ',':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
        error_verbose(tok, 8, expected_tokens);
        return;

    default:
        printf("[ERROR] Const\n");
        error();
        return;
    }
}

// SignedConst → Sign Const .
void SignedConst(void)
{
    int expected_tokens[] = {'+', '-'};
    switch (tok)
    {
    case '+':
    case '-':
        Sign();
        Const();
        return;

    // follows - non-nullable
    case '*':
    case '/':
    case MOD:
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case TO:
    case THEN:
    case DO:
    case END_TOK:
    case ',':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
    case ASSIGN_SIGN:
        error_verbose(tok, 2, expected_tokens);
        return;

    default:
        printf("[ERROR] SignedConst\n");
        error();
        return;
    }
}

//Num → intLit | floatLit .
void Num(void)
{
    int expected_tokens[] = {INT_LITERAL, FLOAT_LITERAL};
    switch (tok)
    {
    case INT_LITERAL:
        eat(INT_LITERAL);
        return;
    case FLOAT_LITERAL:
        eat(FLOAT_LITERAL);
        return;

    // follows - non-nullable
    case '*':
    case '/':
    case MOD:
    case '+':
    case '-':
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case TO:
    case THEN:
    case DO:
    case END_TOK:
    case ',':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
    case ASSIGN_SIGN:
        error_verbose(tok, 2, expected_tokens);
        return;

    default:
        printf("[ERROR] Num\n");
        error();
        return;
    }
}

// Sign → plusSign | minusSign .
void Sign(void)
{
    int expected_tokens[] = {'+', '-'};
    switch (tok)
    {
    case '+':
        eat('+');
        return;
    case '-':
        eat('-');
        return;

    // follows - non-nullable
    case ID:
    case STRING_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case BOOLEAN_LITERAL:
    case '[':
    case ASSIGN_SIGN:
        error_verbose(tok, 2, expected_tokens);
        return;

    default:
        printf("[ERROR] Sign\n");
        error();
        return;
    }
}

//ArrayLit → openBkt ExpList closeBkt .
void ArrayLit(void)
{
    int expected_tokens[] = {'['};
    switch (tok)
    {
    case '[':
        eat('[');
        ExpList();
        eat(']');
        return;

    // follows - non-nullable
    case '*':
    case '/':
    case MOD:
    case '+':
    case '-':
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case TO:
    case THEN:
    case DO:
    case END_TOK:
    case ',':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
    case ']':
        error_verbose(tok, 1, expected_tokens);
        return;

    default:
        printf("[ERROR] ArrayLit\n");
        error();
        return;
    }
}

// ExpList -> | Exp ExpList' .
void ExpList(void)
{
    int expected_tokens[] = {ID, STRING_LITERAL, NULL_TOK, INT_LITERAL, FLOAT_LITERAL, '+', '-', '['};
    switch (tok)
    {
    case NOT:
    case '(':
    case BOOLEAN_LITERAL:
    case THIS:
    case ID:
    case STRING_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case '[':
    case '+':
    case '-':
        Exp();
        ExpList_1();
        return;

    // follows - nullable
    case ']':
    case ')':
        return;

    default:
        printf("[ERROR] ExpList\n");
        error();
        return;
    }
}

// ExpList' -> | comma Exp ExpList' .
void ExpList_1(void)
{
    int expected_tokens[] = {','};
    switch (tok)
    {
    case ',':
        eat(',');
        Exp();
        ExpList_1();
        return;

    // follows - nullable
    case ']':
    case ')':
        return;

    default:
        printf("[ERROR] ExpList_1\n");
        error();
        return;
    }
}

//Ids -> id IdList AccessIndex | this IdList AccessIndex .
void Ids(void)
{
    switch (tok)
    {
    case ID:
        eat(ID);
        IdList();
        AccessIndex();
        return;
    case THIS:
        eat(THIS);
        IdList();
        AccessIndex();
        return;
    default:
        printf("[ERROR] Ids\n");
        error();
        return;
    }
}

// IdList -> | dot id MethCall IdList .
void IdList(void)
{
    switch (tok)
    {
    case '.':
        eat('.');
        eat(ID);
        MethCall();
        IdList();
        return;

    case '*':
    case '/':
    case MOD:
    case '+':
    case '-':
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ',':
    case THEN:
    case DO:
    case ']':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
    case '[':
        return;

    default:
        printf("[ERROR] IdList\n");
        error();
        return;
    }
}

// AccessIndex -> | ArrayLit AccessIndex .
void AccessIndex()
{
    switch (tok)
    {
    case '[':
        ArrayLit();
        AccessIndex();
        return;

    case '*':
    case '/':
    case MOD:
    case '+':
    case '-':
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ',':
    case THEN:
    case DO:
    case ']':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        return;
    }
}

// MethCall → |	( ExpList ) .
void MethCall()
{
    switch (tok)
    {
    case '(':
        eat('(');
        ExpList();
        eat(')');
        return;

    // follows - nullable
    case '*':
    case '/':
    case MOD:
    case '+':
    case '-':
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case '.':
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ',':
    case THEN:
    case DO:
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        printf("[ERROR] MethCall\n");
        error();
        return;
    }
}

//Exp -> TermoLogico LogicExp .
void Exp()
{
    int expected_tokens[] = {'(', '[', ID, THIS, BOOLEAN_LITERAL, STRING_LITERAL, NULL_TOK, INT_LITERAL, FLOAT_LITERAL, NOT, '+', '-'};
    switch (tok)
    {
    case '(':
    case ID:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case NOT:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case STRING_LITERAL:
    case THIS:
    case '[':
    case '-':
    case '+':
        TermLogic();
        LogicExp();
        return;

    // follows - non-nullable
    case TO:
    case THEN:
    case DO:
    case END_TOK:
    case ',':
    case ';':
    case METHODS:
    case BEGIN_TOK:
    case ']':
    case ')':
        error_verbose(tok, 12, expected_tokens);
        return;
    default:
        printf("[ERROR] Exp\n");
        error();
        return;
    }
}

//LogicExp -> or Exp | xor Exp | attrSign Exp | .
void LogicExp()
{
    switch (tok)
    {
    case OR:
        eat(OR);
        Exp();
        return;
    case XOR:
        eat(XOR);
        Exp();
    case ASSIGN_SIGN:
        eat(ASSIGN_SIGN);
        Exp();
        return;

    // follows nullable
    case TO:
    case THEN:
    case DO:
    case BEGIN_TOK:
    case ',':
    case ';':
    case METHODS:
    case END_TOK:
    case ']':
    case ')':
        return;
    default:
        printf("[ERROR] LogicExp\n");
        error();
        return;
    }
}

//TermoLogico -> FatorLogico TermoLogico' .
void TermLogic()
{
    switch (tok)
    {
    case ID:
    case BOOLEAN_LITERAL:
    case NOT:
    case INT_LITERAL:
    case NULL_TOK:
    case FLOAT_LITERAL:
    case STRING_LITERAL:
    case THIS:
    case '-':
    case '+':
    case '(':
    case '[':
        FactorLogic();
        TermLogic_1();
        return;

    default:
        printf("[ERROR] TermLogic\n");
        error();
        return;
    }
}

//TermoLogico' -> and TermoLogico | .
void TermLogic_1()
{
    switch (tok)
    {
    case AND:
        eat(AND);
        TermLogic();
        return;

    // follows nullable
    case TO:
    case THEN:
    case OR:
    case XOR:
    case DO:
    case ';':
    case ',':
    case METHODS:
    case BEGIN_TOK:
    case END_TOK:
    case ']':
    case ')':
    case ASSIGN_SIGN:
        return;
    default:
        printf("[ERROR] TermLogic'\n");
        error();
        return;
    }
}

//FatorLogico -> RelExp | not RelExp  .
void FactorLogic()
{
    switch (tok)
    {
    case ID:
    case THIS:
    case BOOLEAN_LITERAL:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case STRING_LITERAL:
    case '-':
    case '+':
    case '(':
    case '[':
    case NULL_TOK:
        RelExp();
        return;
    case NOT:
        eat(NOT);
        RelExp();
        return;
    default:
        printf("[ERROR] FactorLogic\n");
        error();
        return;
    }
}

//RelExp -> ArithExp Comparacao .
void RelExp()
{
    switch (tok)
    {
    case ID:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case THIS:
    case NULL_TOK:
    case '-':
    case '+':
    case '(':
    case '[':
        ArithExp();
        Comparactive();
        return;
    default:
        printf("[ERROR] RelExp\n");
        error();
        return;
    }
}
//Comparacao -> less ArithExp | major ArithExp | lesseq ArithExp | majoreq ArithExp | eqeq ArithExp | neq ArithExp | .
void Comparactive()
{
    switch (tok)
    {
    case '<':
        eat('<');
        ArithExp();
        return;
    case '>':
        eat('>');
        ArithExp();
        return;
    case LESS_EQ_SIGN:
        eat(LESS_EQ_SIGN);
        ArithExp();
        return;
    case MORE_EQ_SIGN:
        eat(MORE_EQ_SIGN);
        ArithExp();
        return;
    case DOUB_EQ_SIGN:
        eat(DOUB_EQ_SIGN);
        ArithExp();
        return;
    case NEG_EQ_SIGN:
        eat(NEG_EQ_SIGN);
        ArithExp();
        return;

    // Follows nullable
    case TO:
    case THEN:
    case OR:
    case XOR:
    case DO:
    case ';':
    case ',':
    case METHODS:
    case BEGIN_TOK:
    case END_TOK:
    case AND:
    case ']':
    case ')':
    case ASSIGN_SIGN:
        return;
    default:
        printf("[ERROR] Comparactive\n");
        error();
        return;
    }
}

//ArithExp -> Termo ArithExp' .
void ArithExp()
{
    switch (tok)
    {
    case ID:
    case THIS:
    case INT_LITERAL:
    case BOOLEAN_LITERAL:
    case FLOAT_LITERAL:
    case STRING_LITERAL:
    case NULL_TOK:
    case '-':
    case '+':
    case '(':
    case '[':
        Term();
        ArithExp_1();
        return;
    default:
        printf("[ERROR] ArithExp\n");
        error();
        return;
    }
}

//ArithExp' -> plus Termo ArithExp' | minus Termo ArithExp' | .
void ArithExp_1()
{
    switch (tok)
    {
    case '+':
        eat('+');
        Term();
        ArithExp_1();
        return;
    case '-':
        eat('-');
        Term();
        ArithExp_1();
        return;
    // Follows nullable
    case TO:
    case THEN:
    case AND:
    case OR:
    case XOR:
    case END_TOK:
    case DO:
    case ';':
    case ',':
    case METHODS:
    case BEGIN_TOK:
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case ']':
    case ASSIGN_SIGN:
        return;
    default:
        printf("[ERROR] ArithExp'\n");
        error();
        return;
    }
}

//Termo -> Fator Termo' .
void Term()
{
    switch (tok)
    {
    case ID:
    case THIS:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case '-':
    case '+':
    case '(':
    case '[':
        Factor();
        Term_1();
        return;
    default:
        printf("[ERROR] Term");
        error();
        return;
    }
}

//Termo' -> * Fator Termo' | / Fator Termo' | mod Fator Termo' | .
void Term_1()
{
    switch (tok)
    {
    case '*':
        eat('*');
        Factor();
        Term_1();
        return;
    case '/':
        eat('/');
        Factor();
        Term_1();
        return;
    case MOD:
        eat(MOD);
        Factor();
        Term_1();
        return;
    // Follows nullable
    case '+':
    case '-':
    case TO:
    case THEN:
    case AND:
    case OR:
    case XOR:
    case DO:
    case END_TOK:
    case ',':
    case ';':
    case METHODS:
    case BEGIN_TOK:
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case ']':
    case ASSIGN_SIGN:
        return;
    default:
        printf("[ERROR] Term_1");
        error();
        return;
    }
}

//Fator -> Const | ( ArithExp ) .
void Factor()
{
    switch (tok)
    {
    case '(':
        eat('(');
        ArithExp();
        eat(')');
        return;
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '-':
    case '+':
    case '[':
        Const();
        return;

    // follows - non-nullable
    case '*':
    case '/':
    case MOD:
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case ')':
    case AND:
    case OR:
    case XOR:
    case TO:
    case END_TOK:
    case ';':
    case ',':
    case THEN:
    case DO:
    case BEGIN_TOK:
    case METHODS:
    case ASSIGN_SIGN:
    case ']':
        error();
        return;

    default:
        printf("[ERROR] Factor");
        error();
        return;
    }
}
