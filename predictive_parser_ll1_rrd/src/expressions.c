#include "expressions.h"

// Const -> Num | id | strLit | SignedConst | ArrayLit | null .
void Const(void)
{
	switch (tok)
	{
	case ID:
		eat(ID);
		return;
	case STRING_LITERAL:
		eat(STRING_LITERAL);
		return;
	case NULL_TOK:
		eat(NULL_TOK);
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

	// TODO follows - non-nullable
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
		error();
		return;

	default:
		error();
		return;
	}
}

// SignedConst → Sign Const .
void SignedConst(void)
{
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
		error();
		return;

	default:
		error();
		return;
	}
}

//Num → intLit | floatLit .
void Num(void)
{
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
		error();
		return;

	default:
		error();
		return;
	}
}

// Sign → plusSign | minusSign .
void Sign(void)
{
	switch (tok)
	{
	case '+':
		eat('+');
		return;
	case '-':
		eat('-');
		return;

	// follows - nullable
	case ID:
	case STRING_LITERAL:
	case NULL_TOK:
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case '[':
		error();
		return;

	default:
		error();
		return;
	}
}

//ArrayLit → openBkt ConstList closeBkt .
void ArrayLit(void)
{
	switch (tok)
	{
	case '[':
		eat('[');
		ConstList();
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
		error();
		return;

	default:
		error();
		return;
	}
}

// ConstList → | Const comma ConstList .
void ConstList(void)
{
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
		Const();
		eat(',');
		ConstList();
		return;

	// follows - nullable
	case ']':
		return;

	default:
		error();
		return;
	}
}

void Exp()
{
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
	case '-':
	case '+':
		TermLogic();
		LogicExp();
		return;
	default:
		error();
		return;
	}
}

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
	case TO:
	case THEN:
	case DO:
	case BEGIN_TOK:
	case '.':
	case ';':
	case METHODS:
	case END_TOK:
		return;
	default:
		error();
		return;
	}
}

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
	case '-':
	case '+':
	case '(':
		FactorLogic();
		TermLogic_1();
		return;

	default:
		error();
		return;
	}
}

void TermLogic_1()
{
	switch (tok)
	{
	case AND:
		eat(AND);
		TermLogic();
		return;
	case TO:
	case THEN:
	case OR:
	case XOR:
	case DO:
	case ';':
	case '.':
	case METHODS:
	case BEGIN_TOK:
		return;
	default:
		error();
		return;
	}
}

void FactorLogic()
{
	switch (tok)
	{
	case ID:
	case BOOLEAN_LITERAL:
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case STRING_LITERAL:
	case '-':
	case '+':
	case '(':
	case NULL_TOK:
		LogicAtom();
		return;
	case NOT:
		eat(NOT);
		LogicAtom();
		return;
	default:
		error();
		return;
	}
}

void LogicAtom()
{
	switch (tok)
	{
	case BOOLEAN_LITERAL:
		eat(BOOLEAN_LITERAL);
		return;
	case ID:
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case STRING_LITERAL:
	case NULL_TOK:
	case '-':
	case '+':
	case '(':
		RelExp();
		return;
	default:
		error();
		return;
	}
}

void RelExp()
{
	switch (tok)
	{
	case ID:
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case STRING_LITERAL:
	case NULL_TOK:
	case '-':
	case '+':
	case '(':
		ArithExp();
		Comparactive();
		return;
	default:
		error();
	}
}

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
	case TO:
	case THEN:
	case OR:
	case XOR:
	case DO:
	case ';':
	case '.':
	case METHODS:
	case BEGIN_TOK:
		return;
	default:
		error();
		return;
	}
}

void ArithExp()
{
	switch (tok)
	{
	case ID:
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case STRING_LITERAL:
	case NULL_TOK:
	case '-':
	case '+':
	case '(':
		Term();
		ArithExp_1();
		return;
	default:
		error();
		return;
	}
}

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

void Term()
{
	switch (tok)
	{
	case ID:
	case INT_LITERAL:
	case FLOAT_LITERAL:
	case STRING_LITERAL:
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

void Factor()
{
	switch (tok)
	{
	case '-':
	case '+':
	case STRING_LITERAL:
	case FLOAT_LITERAL:
	case INT_LITERAL:
	case ID:
	case NULL_TOK:
	case '[':
		Const();
		return;
	case '(':
		eat('(');
		ArithExp();
		eat(')');
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
		error();
		return;

	default:
		error();
	}
}
