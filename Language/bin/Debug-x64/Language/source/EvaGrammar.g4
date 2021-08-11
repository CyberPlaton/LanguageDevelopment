grammar EvaGrammar;

/*Starting Rules*/
program: (NEWLINE | expr)* EOF;


single_input: NEWLINE
	| expr
	| expr NEWLINE
	;



/*Parser Rules*/
expr: expr (PLUS | MINUS) term
	| term
	;


term: term (MUL | DIVIDE) literal
	| literal
	;


literal: INT
	;


INT: [0-9]+;


NEWLINE: [\r\n] -> skip;
WS: [' ' | \t] -> skip;


/*Lexer Definitions*/ 
MUL: '*';
PLUS: '+';
MINUS: '-';
DIVIDE: '/';
