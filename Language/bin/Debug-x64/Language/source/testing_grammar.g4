grammar testing_grammar;


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
