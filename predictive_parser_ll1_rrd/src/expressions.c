#include "expressions.h"


void Exp(){
	switch(tok){
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
			TermLogic_0(); LogicExp();
			break;
		default: 
			error();
			break;
	}
}

void LogicExp(){
	switch(tok){
		case OR:
			eat(OR); Exp();
			break;
		case XOR:
			eat(XOR); Exp();
			break;
		case TO:
		case THEN:
		case DO:
		case BEGIN_TOK:
		case '.':
		case ';':
		case METHODS:
		case END_TOK:
			break;
		default:
			error();
			break;
	}
}

void TermLogic_0(){
	switch(tok){
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
			FactorLogic();TermLogic_1(); 
			break;
			
		default:
			error();
			break;
	}
}

void TermLogic_1(){
	switch(tok){
		case AND:
			eat(AND); TermLogic_0();
			break;
		case TO:
		case THEN:
		case OR:
		case XOR:
		case DO:
		case ';':
		case '.':
		case METHODS:
		case BEGIN_TOK:
			break;
		default:
			error();
			break;
	}
}

void FatorLogic(){
	switch(tok){
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
			break;
		case NOT:
			eat(NOT); LogicAtom();
			break;	
		default:
			error();
			break;
	}
}

void LogicAtom(){
	switch(tok){
		case BOOLEAN_LITERAL:
			eat(BOOLEAN_LITERAL);
			break;
		case ID:
		case INT_LITERAL:
		case FLOAT_LITERAL:
		case STRING_LITERAL:
		case NULL_TOK:
		case '-':
		case '+':
		case '(':
			RelExp();
			break;
		default:
			error();
			break;
	}
}	

void RelExp(){
	switch(tok){
		case ID:
		case INT_LITERAL:
		case FLOAT_LITERAL:
		case STRING_LITERAL:
		case NULL_TOK:
		case '-':
		case '+':
		case '(':
			ArithExp_0(); Comparactive();
			break;
		default:
			error();
	}
}

void Comparactive(){
	switch(tok){
		case '<':
			eat('<'); ArithExp_0();
			break;
		case '>':
			eat('>'); ArithExp_0();
			break;
		case LESS_EQ_SIGN:
			eat(LESS_EQ_SIGN); ArithExp_0();
			break;
		case MORE_EQ_SIGN:
			eat(MORE_EQ_SIGN); ArithExp_0();
			break;
		case DOUB_EQ_SIGN:
			eat(DOUB_EQ_SIGN); ArithExp_0();
			break;
		case NEG_EQ_SIGN:
			eat(NEG_EQ_SIGN); ArithExp_0();
			break;	
		case TO:
		case THEN:
		case OR:
		case XOR:
		case DO:
		case ';':
		case '.':
		case METHODS:
		case BEGIN_TOK:
			break;
		default:
			error();
			break;		
	}
}

void ArithExp_0(){
	switch(tok){
		case ID:
		case INT_LITERAL:
		case FLOAT_LITERAL:
		case STRING_LITERAL:
		case NULL_TOK:
		case '-':
		case '+':
		case '(':
			Term_0(); ArithExp_1();
			break;
		default:
			error();
			break;
	}
}

void ArithExp_1(){
	switch(tok){
		case '+':
			eat('+'); Term_0(); ArithExp_1();
			break;
		case '-':
			eat('-'); Term_0(); ArithExp_1();
			break;
		case TO:
		case THEN:
		case OR:
		case XOR:
		case DO:
		case ';':
		case '.':
		case METHODS:
		case BEGIN_TOK:
		case '<':
		case '>':
		case LESS_EQ_SIGN:
		case MORE_EQ_SIGN:
		case DOUB_EQ_SIGN:
		case NEG_EQ_SIGN:
			break;
	}
}

void Term_0(){
	switch(tok){
		case ID:
		case INT_LITERAL:
		case FLOAT_LITERAL:
		case STRING_LITERAL:
		case NULL_TOK:
		case '-':
		case '+':
		case '(':
			Fator(); Term_1();
			break;
		default:
			error();
			break;
	}
}

void Term_1(){
	switch(tok){
		case '*':
			eat('*'); Fator(); Term_1();
			break;
		case '/':
			eat('/'); Fator(); Term_1();
			break;
		case MOD:
			eat(MOD); Fator(); Term_1();
			break;
		case TO:
		case THEN:
		case OR:
		case XOR:
		case DO:
		case ';':
		case '.':
		case METHODS:
		case BEGIN_TOK:
		case '<':
		case '>':
		case LESS_EQ_SIGN:
		case MORE_EQ_SIGN:
		case DOUB_EQ_SIGN:
		case NEG_EQ_SIGN:
			break;	
		default:
			error();
	}
}

void Fator(){
	switch(tok){
		case '-':
			eat('-'); Fator();
			break;
		case '+':
			eat('+'); Fator();
			break;
		case STRING_LITERAL:
			eat(STRING_LITERAL);
			break;
		case FLOAT_LITERAL:
			eat(FLOAT_LITERAL);
			break;
		case INT_LITERAL:
			eat(INT_LITERAL);
			break;
		case ID:
			eat(ID);
			break;
		case NULL_TOK:
			eat(NULL_TOK);
			break;
		case '(':
			eat('('); ArithExp_0(); eat(')');
			break;
		default:
			error();
	}

}
