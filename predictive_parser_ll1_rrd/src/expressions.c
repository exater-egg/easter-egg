#include "expressions.h"

// Const -> Num | Ids | strLit | boolLit | SignedConst | ArrayLit | null .
void Const(void)
{
	int expected_tokens[] = {ID, STRING_LITERAL, NULL_TOK, INT_LITERAL, BOOLEAN_LITERAL,FLOAT_LITERAL, '+', '-', '['};
	switch (tok)
	{
	case ID:
		Ids();
		return;
	case STRING_LITERAL:
		eat(STRING_LITERAL);
		return;
	case NULL_TOK:
		eat(NULL_TOK);
		return;
	case BOOLEAN_LITERAL:
		eat(BOOLEAN_LITERAL);
		return;
	case INT_LITERAL:
	case FLOAT_LITERAL:
		Num();
		return;
	case '+':
	case '-':
		SignedConst();
		return;
	case '[':
		ArrayLit();
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
		error_verbose(tok, 2, expected_tokens);
		return;

	default:
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
		error_verbose(tok, 2, expected_tokens);
		return;

	default:
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
		error_verbose(tok, 2, expected_tokens);
		return;

	default:
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
		error_verbose(tok, 1, expected_tokens);
		return;

	default:
		error();
		return;
	}
}

// ExpList -> | Exp comma ExpList .
void ExpList(void)
{
	int expected_tokens[] = {ID, STRING_LITERAL, NULL_TOK, INT_LITERAL, FLOAT_LITERAL, '+', '-', '['};
	switch (tok)
	{
	case ID:
	case STRING_LITERAL:
	case NULL_TOK:
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case '[':
	case '+':
	case '-':
		Exp();
		eat(',');
		ExpList();
		return;

	// follows - nullable
	case ']':
	case ')':
		return;

	default:
		error();
		return;
	}
}

//Ids -> id IdList | this IdList .
void Ids(void){
    switch (tok)
    {
    case ID:
        eat(ID); IdList(); return;
    case THIS:
        eat(THIS); IdList(); return;
    default:
        error();
    }
}

// IdList -> | dot id MethCall IdList .
void IdList(void){
    switch (tok)
    {
    case '.':
        eat('.'); eat(ID); MethCall(); IdList(); return;
    case ASSIGN_SIGN:
        return;
    default:
        error();
    }
}

// MethCall → |	( ExpList ) .
void MethCall() {
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
		return;
	}
}

//Exp -> TermoLogico LogicExp .
void Exp()
{
	int expected_tokens[] = {'(', ID, BOOLEAN_LITERAL, STRING_LITERAL, NULL_TOK, INT_LITERAL, FLOAT_LITERAL, NOT, '+', '-'};
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
		error_verbose(tok, 10, expected_tokens);
		return;
	default:
		error();
		return;
	}
}

//LogicExp -> or Exp | xor Exp | .
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
		return;
	default:
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
		return;
	default:
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
		error();
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
		return;
	default:
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
		return;
	default:
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
		error();
		return;
	}
}

//Termo' -> * Fator Termo' 
// | / Fator Termo' | mod Fator Termo' | .
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
		return;
	default:
		error();
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
		error();
		return;

	default:
		error();
	}
}
