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


/*Example of how we can hook in functionality from the target language*/
f: INT
	| '(' e ')'	 { std::cout<< e.text() << std::endl; }
	;


INT: [0-9]+;

