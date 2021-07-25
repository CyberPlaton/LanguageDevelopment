grammar EvaGrammar;

/*Starting Rules*/
file_input: (NEWLINE | e)* EOF;

single_input: NEWLINE
			| e
			| e NEWLINE
			;


/*Parser Rules*/
e: e (PLUS | MINUS) t
	| t
	;


t: t (MUL | DIVIDE) m
	| m
	;


m: m MOD f
	| f
	;



f: INT
	| '(' e ')'
	;


INT: [0-9]+;

NEWLINE: [\r\n] -> skip;
WS: [' ' | \t] -> skip;


/*Lexer Definitions*/ 
MUL: '*';
PLUS: '+';
MINUS: '-';
DIVIDE: '/';
MOD: '%';
