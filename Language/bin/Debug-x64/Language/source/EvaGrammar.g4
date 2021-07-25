grammar EvaGrammar;

/*Starting Rules*/
file_input: (NEWLINE | e)* EOF;

single_input: NEWLINE
			| e
			| e NEWLINE
			;


/*Parser Rules*/
e: e '+' t
	| t
	;


t: t '*' m
	| m
	;


m: m '%' f
	| f
	;



f: INT
	| '(' e ')'
	;


INT: [0-9]+;

NEWLINE: [\r\n] -> skip;
