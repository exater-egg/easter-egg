#include "expressions.h"

// Const → Num | Ids | strLit | boolLit | SignedConst | ArrayLit | null .
void Const_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Const) := {
     *    strLit, boolLit, null, intLit, floatLit, id, this, openBkt, 
     *    plusSign, minusSign
     * }
     */
    case STRING_LITERAL:
        stack_push(stack, STRING_LITERAL);
        return;
    case BOOLEAN_LITERAL:
        stack_push(stack, BOOLEAN_LITERAL);
        return;
    case NULL_TOK:
        stack_push(stack, NULL_TOK);
        return;
    case INT_LITERAL:
    case FLOAT_LITERAL:
        stack_push(stack, Num);
        return;
    case ID:
    case THIS:
        stack_push(stack, Ids);
        return;
    case '[':
        stack_push(stack, ArrayLit);
        return;
    case '+':
    case '-':
        stack_push(stack, SignedConst);
        return;

    /**
     * non-nullable
     * Follow(Const) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq, 
     *    eqeq, neq, and, or, xor, attrSign, to, end, comma, then, do, 
     *    closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
    default:
        error();
        return;
    }
}

// SignedConst → Sign Const .
void SignedConst_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(SignedConst) := {plusSign, minusSign}
     */
    case '+':
    case '-':
        stack_push(stack, Const);
        stack_push(stack, Sign);
        return;

    /**
     * non-nullable
     * Follow(SignedConst) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, attrSign, to, end, comma, then, do,
     *    closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
    default:
        error();
        return;
    }
}

//Num → intLit | floatLit .
void Num_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Num) := {intLit, floatLit}
     */
    case INT_LITERAL:
        stack_push(stack, INT_LITERAL);
        return;
    case FLOAT_LITERAL:
        stack_push(stack, FLOAT_LITERAL);
        return;

    /**
     * non-nullable
     * Follow(Num) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, attrSign, to, end, comma, then, do,
     *    closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
    default:
        error();
        return;
    }
}

// Sign → plusSign | minusSign .
void Sign_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Sign) := {plusSign, minusSign}
     */
    case '+':
    case '-':
        stack_push(stack, Const);
        stack_push(stack, Sign);
        return;

    /**
     * non-nullable
     * Follow(Sign) := {
     *    strLit, boolLit, null, intLit, floatLit, id, this, openBkt,
     *    plusSign, minusSign
     * }
     */
    default:
        error();
        return;
    }
}

// ArrayLit → openBkt ExpList closeBkt .
void ArrayLit_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(ArrayLit) := {openBkt}
     */
    case '[':
        stack_push(stack, ']');
        stack_push(stack, ExpList);
        stack_push(stack, '[');
        return;

    /**
     * non-nullable
     * Follow(ArrayLit) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, openBkt, attrSign, to, end, comma,
     *    then, do, closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
    default:
        error();
        return;
    }
}

// ExpList → | Exp ExpList' .
void ExpList_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(ExpList) := {
     *    not, (, strLit, boolLit, null, intLit, floatLit, id, this, openBkt,
     *    plusSign, minusSign
     * }
     */
    case NOT:
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, ExpList_1);
        stack_push(stack, Exp);
        return;

    /**
     * nullable
     * Follow(ExpList) := {closeBkt, )}
     */
    case ']':
    case ')':
        return;
    default:
        error();
        return;
    }
}

// ExpList' → | comma Exp ExpList' .
void ExpList_1_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(ExpList') := {comma}
     */
    case ',':
        stack_push(stack, ExpList_1);
        stack_push(stack, Exp);
        stack_push(stack, ',');
        return;

    /**
     * nullable
     * Follows(ExpList') := {closeBkt, )}
     */
    case ']':
    case ')':
        return;
    default:
        error();
        return;
    }
}

// Ids → id IdList AccessIndex | this IdList AccessIndex .
void Ids_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Ids) := {id, this}
     */
    case ID:
        stack_push(stack, AccessIndex);
        stack_push(stack, IdList);
        stack_push(stack, ID);
        return;
    case THIS:
        stack_push(stack, AccessIndex);
        stack_push(stack, IdList);
        stack_push(stack, THIS);
        return;

    /**
     * non-nullable
     * Follow(Ids) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, attrSign, to, end, comma, then, do,
     *    closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
    default:
        error();
        return;
    }
}

// IdList → | dot id MethCall IdList .
void IdList_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(IdList) := {id, this}
     */
    case '.':
        stack_push(stack, IdList);
        stack_push(stack, MethCall);
        stack_push(stack, ID);
        stack_push(stack, '.');
        return;

    /**
     * nullable
     * Follow(IdList) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, openBkt, attrSign, to, end, comma,
     *    then, do, closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
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
    case AND:
    case OR:
    case XOR:
    case '[':
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ',':
    case THEN:
    case DO:
    case ']':
    case ')':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// AccessIndex → | ArrayLit AccessIndex .
void AccessIndex_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(AccessIndex) := {openBkt}
     */
    case '[':
        stack_push(stack, AccessIndex);
        stack_push(stack, ArrayLit);
        return;

    /**
     * nullable
     * Follow(AccessIndex) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, attrSign, to, end, comma, then, do,
     *    closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
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
    case ')':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// MethCall → | ( ExpList ) .
void MethCall_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(ExpList) := {(}
     */
    case '(':
        stack_push(stack, ')');
        stack_push(stack, ExpList);
        stack_push(stack, '(');
        return;

    /**
     * nullable
     * Follow(ExpList) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, dot, openBkt, attrSign, to, end, comma,
     *    then, do, closeBkt, ), ;, begin, classes, variables, var, methods
     * }
     */
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
    case AND:
    case OR:
    case XOR:
    case '.':
    case '[':
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ',':
    case THEN:
    case DO:
    case ']':
    case ')':
    case ';':
    case BEGIN_TOK:
    case CLASSES:
    case VARIABLES:
    case METHODS:
        return;

    default:
        error();
        return;
    }
}

// Exp → TermoLogico LogicExp .
void Exp_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Exp) := {
     *    not, (, strLit, boolLit, null, intLit, floatLit, id,
     *    this, openBkt, plusSign, minusSign
     * }
     */
    case NOT:
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, LogicExp);
        stack_push(stack, TermLogic);
        return;

    /**
     * non-nullable
     * Follows(Exp) := {
     *    to, end, ;, comma, then, do, closeBkt, ), methods, begin
     * }
     */
    default:
        error();
        return;
    }
}

// LogicExp → or Exp | xor Exp | attrSign Exp | .
void LogicExp_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(LogicExp) := {or, xor, attrSign}
     */
    case OR:
        stack_push(stack, Exp);
        stack_push(stack, OR);
        return;
    case XOR:
        stack_push(stack, Exp);
        stack_push(stack, XOR);
        return;
    case ASSIGN_SIGN:
        stack_push(stack, Exp);
        stack_push(stack, ASSIGN_SIGN);
        return;

    /**
     * nullable
     * Follow(LogicExp) := {
     *    to, end, ;, comma, then, do, closeBkt, ), methods, begin
     * }
     */
    case TO:
    case END_TOK:
    case ';':
    case ',':
    case THEN:
    case DO:
    case ']':
    case ')':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// TermoLogico → FatorLogico TermoLogico' .
void TermLogic_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(TermoLogico) := {
     *    not, (, strLit, boolLit, null, intLit, floatLit, id,
     *    this, openBkt, plusSign, minusSign
     * }
     */
    case NOT:
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, TermLogic_1);
        stack_push(stack, FactorLogic);
        return;

    /**
     * non-nullable
     * Follow(TermoLogico) := {
     *    or, xor, attrSign, to, end, ;, comma, then, do, closeBkt, ),
     *    methods, begin
     * }
     */
    default:
        error();
        return;
    }
}

// TermoLogico' → and TermoLogico | .
void TermLogic_1_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(TermoLogico') := {and}
     */
    case AND:
        stack_push(stack, TermLogic);
        stack_push(stack, AND);
        return;

    /**
     * nullable
     * Follow(TermoLogico') := {
     *    or, xor, attrSign, to, end, ;, comma, then, do, closeBkt, ),
     *    methods, begin
     * }
     */
    case OR:
    case XOR:
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ';':
    case ',':
    case THEN:
    case DO:
    case ']':
    case ')':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// FatorLogico → RelExp | not RelExp .
void FactorLogic_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(FatorLogico) := {
     *    not, (, strLit, boolLit, null, intLit, floatLit, id,
     *    this, openBkt, plusSign, minusSign
     * }
     */
    case NOT:
        stack_push(stack, RelExp);
        stack_push(stack, NOT);
        return;
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, RelExp);
        return;

    /**
     * non-nullable
     * Follow(FatorLogico) := {
     *    and, or, xor, attrSign, to, end, ;, comma, then, do, closeBkt, ),
     *    methods, begin
     * }
     */
    default:
        error();
        return;
    }
}

// RelExp → ArithExp Comparacao .
void RelExp_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(RelExp) := {
     *    (, strLit, boolLit, null, intLit, floatLit, id, this,
     *    openBkt, plusSign, minusSign
     * }
     */
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, Comparactive);
        stack_push(stack, ArithExp);
        return;

    /**
     * non-nullable
     * Follow(RelExp) := {
     *    and, or, xor, attrSign, to, end, ;, comma, then, do, closeBkt, ),
     *    methods, begin 
     * }
     */
    default:
        error();
        return;
    }
}

// Comparacao → less ArithExp | major ArithExp | lesseq ArithExp
//            | majoreq ArithExp | eqeq ArithExp | neq ArithExp | .
void Comparactive_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Comparacao) := {less, major, lesseq, majoreq, eqeq, neq}
     */
    case '<':
        stack_push(stack, ArithExp);
        stack_push(stack, '<');
        return;
    case '>':
        stack_push(stack, ArithExp);
        stack_push(stack, '>');
        return;
    case LESS_EQ_SIGN:
        stack_push(stack, ArithExp);
        stack_push(stack, LESS_EQ_SIGN);
        return;
    case MORE_EQ_SIGN:
        stack_push(stack, ArithExp);
        stack_push(stack, MORE_EQ_SIGN);
        return;
    case DOUB_EQ_SIGN:
        stack_push(stack, ArithExp);
        stack_push(stack, DOUB_EQ_SIGN);
        return;
    case NEG_EQ_SIGN:
        stack_push(stack, ArithExp);
        stack_push(stack, NEG_EQ_SIGN);
        return;

    /**
     * nullable
     * Follow(Comparacao) := {
     *    and, or, xor, attrSign, to, end, ;, comma, then, do, closeBkt, ),
     *    methods, begin
     * }
     */
    case AND:
    case OR:
    case XOR:
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ';':
    case ',':
    case THEN:
    case DO:
    case ']':
    case ')':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// ArithExp → Termo ArithExp' .
void ArithExp_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(ArithExp) := {
     *    (, strLit, boolLit, null, intLit, floatLit, id, this,
     *    openBkt, plusSign, minusSign
     * }
     */
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, ArithExp_1);
        stack_push(stack, Term);
        return;

    /**
     * non-nullable
     * Follow(ArithExp) := {
     *    less, major, lesseq, majoreq, eqeq, neq, and, or, xor, attrSign,
     *    to, end, ;, comma, then, do, closeBkt, ), methods, begin
     * }
     */
    default:
        error();
        return;
    }
}

// ArithExp' → plusSign Termo ArithExp' | minusSign Termo ArithExp' | .
void ArithExp_1_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(ArithExp') := {plusSign, minusSign}
     */
    case '+':
        stack_push(stack, ArithExp_1);
        stack_push(stack, Term);
        stack_push(stack, '+');
        return;
    case '-':
        stack_push(stack, ArithExp_1);
        stack_push(stack, Term);
        stack_push(stack, '-');
        return;

    /**
     * nullable
     * Follow(ArithExp') := {
     *    less, major, lesseq, majoreq, eqeq, neq, and, or, xor, attrSign,
     *    to, end, ;, comma, then, do, closeBkt, ), methods, begin
     * }
     */
    case '>':
    case '<':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case AND:
    case OR:
    case XOR:
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ';':
    case ',':
    case THEN:
    case DO:
    case ']':
    case ')':
    case METHODS:
    case BEGIN_TOK:
        return;
    default:
        error();
        return;
    }
}

// Termo → Fator Termo' .
void Term_to_stack(int col)
{
    switch (col)
    {
    /**
     * Firs(Termo) := {
     *    (, strLit, boolLit, null, intLit, floatLit, id, this,
     *    openBkt, plusSign, minusSign
     * }
     */
    case '(':
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, Term_1);
        stack_push(stack, Factor);
        return;

    /**
     * non-nullable
     * Follow(Termo) := {
     *    plusSign, minusSign, less, major, lesseq, majoreq, eqeq, neq,
     *    and, or, xor, attrSign, to, end, ;, comma, then, do, closeBkt, ),
     *    methods, begin
     * }
     */
    default:
        error();
        return;
    }
}

// Termo' → * Fator Termo' | / Fator Termo' | mod Fator Termo' | .
void Term_1_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Term') := {*, /, mod}
     */
    case '*':
        stack_push(stack, Term_1);
        stack_push(stack, Factor);
        stack_push(stack, '*');
        return;
    case '/':
        stack_push(stack, Term_1);
        stack_push(stack, Factor);
        stack_push(stack, '/');
        return;
    case MOD:
        stack_push(stack, Term_1);
        stack_push(stack, Factor);
        stack_push(stack, MOD);
        return;

    /**
     * nullable
     * Follow(Term') := {
     *    plusSign, minusSign, less, major, lesseq, majoreq, eqeq, neq,
     *    and, or, xor, attrSign, to, end, ;, comma, then, do, closeBkt, ),
     *    methods, begin
     * }
     */
    case '+':
    case '-':
    case '<':
    case '>':
    case LESS_EQ_SIGN:
    case MORE_EQ_SIGN:
    case DOUB_EQ_SIGN:
    case NEG_EQ_SIGN:
    case AND:
    case OR:
    case XOR:
    case ASSIGN_SIGN:
    case TO:
    case END_TOK:
    case ';':
    case ',':
    case THEN:
    case DO:
    case ']':
    case ')':
    case METHODS:
    case BEGIN_TOK:
        return;

    default:
        error();
        return;
    }
}

// Fator → Const | ( ArithExp ) .
void Factor_to_stack(int col)
{
    switch (col)
    {
    /**
     * FirstN(Factor) := {
     *    (, strLit, boolLit, null, intLit, floatLit, id, this,
     *    openBkt, plusSign, minusSign
     * }
     */
    case '(':
        stack_push(stack, ')');
        stack_push(stack, ArithExp);
        stack_push(stack, '(');
        return;
    case STRING_LITERAL:
    case BOOLEAN_LITERAL:
    case NULL_TOK:
    case INT_LITERAL:
    case FLOAT_LITERAL:
    case ID:
    case THIS:
    case '[':
    case '+':
    case '-':
        stack_push(stack, Const);
        return;

    /**
     * non-nullable
     * Follow(Factor) := {
     *    *, /, mod, plusSign, minusSign, less, major, lesseq, majoreq,
     *    eqeq, neq, and, or, xor, attrSign, to, end, ;, comma, then, do,
     *    closeBkt, ), methods, begin
     * }
     */
    default:
        error();
        return;
    }
}
