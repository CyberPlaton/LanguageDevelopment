const assert = require('assert');
const evaParser = require('./evaParser');

/**
 * Eva Environment class.
 */
 class Environment{

    /**
     * Create an environment with a storage map of values. 
     */
    constructor(record = {}, parent = null){
        this.record = record;
        this.parent = parent;
    }

    /**
     * Creates a variable.
     */
    define(name, value){
        this.record[name] = value;
        return value;
    }


    /**
     * Return variable value in storage, if it exists.
     */
    lookup(name){
        return this.resolve(name).record[name];
    }

    /**
     * Returns specific environment on which a variable is defined,
     * or throws if its not defined. 
     */
    resolve(name){
        if(this.record.hasOwnProperty(name)){ // Check if variable is in our scope (record)
            return this;
        }

        // Check if parent has the variable else throw.
        if(this.parent == null){
            throw new ReferenceError('Variable \"' + name + '\" is not defined.');
        }
        else{
            return this.parent.resolve(name);
        }
    }


    /**
     * Update the value of an existent variable.
     * Throw if variable does not exist.
     */
    assign(name, value){
        this.resolve(name).record[name] = value;
        return value;
    }

}




/**
 * Eva interpreter.
 */
class Eva{
    /**
     * Creates  an Eva inst. with a global environment.
     */
     constructor(global_env = new Environment()){
        this.global_env = global_env;
    }


    eval(exp, env = this.global_env){

        console.log("Evaluating Expression: ");
        console.log(exp);

        /**
         * Self evaluating expressions.
         */
        if(this._is_number(exp)){
            return exp;
        }
        if(this._is_string(exp)){
            return exp.slice(1, -1); // Strip the string of its quotes.
        }


        /**
         * Math operations. Moving to built in types... I leave them here..
         */
        if(exp[0] === '+'){ // Addition

            // Recursive descent.
            return this.eval(exp[1], env) + this.eval(exp[2], env);
        }

        if(exp[0] === '*'){ // Multiplication

            // Recursive descent.
            return this.eval(exp[1], env) * this.eval(exp[2], env);
        }


        /**
         * Comparison Operations.
         */
         if(exp[0] === '>'){ // Greater

            // Recursive descent.
            return this.eval(exp[1], env) > this.eval(exp[2], env);
        }

        if(exp[0] === '<'){ // Smaller

            // Recursive descent.
            return this.eval(exp[1], env) < this.eval(exp[2], env);
        }

        if(exp[0] === '=='){ // Equal

            // Recursive descent.
            return this.eval(exp[1], env) === this.eval(exp[2], env);
        }

        if(exp[0] === '>='){ // Greater-Equal

            // Recursive descent.
            return this.eval(exp[1], env) >= this.eval(exp[2], env);
        }

        if(exp[0] === '<='){ // Smaller-Equal

            // Recursive descent.
            return this.eval(exp[1], env) <= this.eval(exp[2], env);
        }


        /**
         * Expression blocks.
         */
        if(exp[0] === 'begin'){

            // Create new environment for the block,
            // with the parent environment of the previous block.
            const block_env = new Environment({}, env);

            return this._eval_block(exp, block_env);
        }



        /**
         * Variables.
         */
         if(exp[0] === 'var'){ // Var decl.

            const [_, name, value] = exp; // Extract from exp only exp[1] and exp[2].

            return env.define(name, this.eval(value, env)); // Let the environment recursively handle variable defs.
        }
        

        if(this._is_VariableName(exp)){ // Variable access.
            return env.lookup(exp);
        }


        /**
         * Variable Assignment.
         */
         if(exp[0] === 'set'){

            const [_, name, value] = exp; // Extract from exp only exp[1] and exp[2].

            return env.assign(name, this.eval(value, env)); // Let the environment recursively handle variable assignment.
        
         }



         /**
          * Branching conditions.
          */
          if(exp[0] === 'if'){

            const [_tag, condition, consequent, alternate] = exp;

            if(this.eval(condition, env)){
                return this.eval(consequent, env);
            }
            else{
                return this.eval(alternate, env);
            }

          }



          if(exp[0] === 'while'){

            const [_tag, condition, body] = exp;
            let result;
            while(this.eval(condition, env)){
                result = this.eval(body, env);
            }
            return result;
          }




          /**
           * Function Calls.
           */
          if(Array.isArray(exp)){

            const func = this.eval(exp[0], env); // Extract the function, meaning lookup the variable name in the environment and return the function pointer.

            // Extract parameters for the function call from the expression.
            // Note that the function is native JS.
            const args = exp.slice(1).map(arg => this.eval(arg, env));

            // 1.) Native Functions.
            // Check whether it is a function type.
            if(typeof func === 'function'){
                func(...args); // Calling the function with variable number of parameters.
            }

            // 2.) User-Defined Functions.
            // TODO
          }



        throw 'Unimplemented: ' + JSON.stringify(exp) ;
    }



    _eval_block(block, env){

        // Result is the last evaluation of the block.
        let result;

        const [_tag, ...expressions] = block;


        expressions.forEach(exp => {
            result = this.eval(exp, env);
        });

        return result;
    }


    _is_number(exp){
        return typeof exp === 'number';
    }
    
    // Check whether its string AND
    // first and last sign are quotes "".
    _is_string(exp){
        return typeof exp === 'string' && exp[0] === '"' && exp.slice(-1) === '"';
    }
    
    // Determine whether exp is a name consisting of
    // chars and numbers
    _is_VariableName(exp){
        return typeof exp ==='string' && /^[a-zA-Z][a-zA-Z0-9_]*$/.test(exp);
    }
}






/**
 * Testing.
 */
const global_environment = new Environment({
    null:null,
    true:true,
    false:false,
    VERSION:'0.0.1',


    /**
     * Define built-in functions for the environment.
     */
    '+'(op1, op2){
        return op1 + op2;
    },
    '*'(op1, op2){
        return op1 * op2;
    },
    '-'(op1, op2 = null){
        if(op2 == null){
            return -op1;
        }
        else{
            return op1 - op2;
        }
    },
    '/'(op1, op2){
        return op1 / op2;
    },
    /**
     * Same can be done for the comparison operators.
     */
    

}, null);
const eva = new Eva(global_environment);


function test(eva, source, expected){
    const exp = evaParser.parse(source);

    assert.strictEqual(eva.eval(exp), expected);
}



/**
 * Self-eval.
 */
assert.strictEqual(eva.eval(1), 1);
assert.strictEqual(eva.eval('"hello"'), 'hello');

/**
 * Math.
 */
assert.strictEqual(eva.eval(['+', 1, 5]), 6); // 1 + 5
assert.strictEqual(eva.eval(['+', ['+', 3, 2], 5]), 10); // (3 + 2) + 5
assert.strictEqual(eva.eval(['+', ['+', ['+', 1, 1], 2], 5]), 9); // ((1 + 1) + 2) + 5
assert.strictEqual(eva.eval(['+', ['+', 2,  ['+', 1, 1]],  ['+', 1, 8]]), 13); // (2 + (1 + 1)) + (1 + 8)
assert.strictEqual(eva.eval(['*', 3, 5]), 15);
assert.strictEqual(eva.eval(['*', ['*', 1, 1], ['*', 3, 5]]), 15);
assert.strictEqual(eva.eval(['*', ['+', 5, 0], ['*', 15, 1]]), 75); // (5 + 0) * ( 15 * 1)
assert.strictEqual(eva.eval(['+', ['*', 1, 1], 5]), 6);


/**
 * Variables.
 */
 assert.strictEqual(eva.eval(['var', 'foo', 10]), 10); // Create a variable...
 assert.strictEqual(eva.eval('foo'), 10); // Access a variables value...
 assert.strictEqual(eva.eval('VERSION'), '0.0.1'); // Access global variables
 assert.strictEqual(eva.eval(['var', 'user', 'true']), true); // var user = true.
 assert.strictEqual(eva.eval(['var', 'z', ['*', 2, 2]]), 4); // var z = 2 * 2.
 assert.strictEqual(eva.eval('z'), 4);
 assert.strictEqual(eva.eval(['var', 'foo', ['*', 'foo', 'z']]), 40); // foo = foo * z;

/**
 * Block scope, e.g. C++
 * A block has own scope -> environment.
 * 
 * { // Block start
 * 
 *  int x = 10;
 *  cout << x;
 * 
 * } // Block end.
 * 
 * 
 * {
 * var x = 3
 * var y = 2
 * 4 + (x * y)
 * }
 */
 assert.strictEqual(eva.eval(
     ['begin',
     
     ['var', 'x', 10],
     ['var', 'y', 20],
     
     ['+', ['*', 'x', 'y'], 30],
     
    ]), 230);


assert.strictEqual(eva.eval(
    ['begin',
    ['var', 'x', 10],    


    ['begin',
         ['var', 'x', 20],
         'x'
    ],

    'x'
        
]), 10);  


assert.strictEqual(eva.eval(
    ['begin',
        ['var', 'value', 10],
        ['var', 'result', ['begin',
                                ['var', 'x', ['+', 'value', 10]],
                            'x'
                          ]],

    'result'
        
]), 20); 



assert.strictEqual(eva.eval(
    ['begin',
    ['var', 'data', 10],    


    ['begin',
         ['set', 'data', 100],
    ],

    'data'
        
]), 100); 


/**
 * Branching Tests.
 * x = 10
 * y = 0
 * 
 * if(x > 10){
 *  y = 20
 * }
 * else{
 * y = 30
 * }
 */
 assert.strictEqual(eva.eval(
    ['begin',
    ['var', 'x', 10],    
    ['var', 'y', 0], 
    ['if', ['>', 'x', 10],
            ['set', 'y', 20],
            ['set', 'y', 30],        
    ],
    'y'
]), 30);



/**
 * While Loop Test.
 * 
 * {
 *  counter = 0
 *  result = 0
 *  while(counter < 10){
 *      result = result + 1
 *      counter = counter + 1
 *      }
 * }
 */
 assert.strictEqual(eva.eval(
    ['begin',
    
    ['var', 'counter', 0],    
    ['var', 'result', 0], 
    
    ['while', ['<', 'counter', 10],
        ['begin',
            ['set', 'result', ['+', 'result', 1]],
            ['set', 'counter', ['+', 'counter', 1]]
        ]
     ],
    'result'
]), 10);



/**
 * New Testing Format.
 * 
 * We Generated a Parser that Parses the String as below and generates the expression,
 * which in turn is supplied to the eva.eval(..) function.
 * 
 * Note that Strings must be denoted as \"Some String\".
 * 
 * Note that the parser is only for convenience and generates exactly the same source code as above...
 */
test(eva, '(begin (var x 10) (var y 20) (+ (* x 10) y))', 120);


/**
 * Built-In Functions.
 */
 assert.strictEqual(eva.eval(['print', '"Hello"', '"Bogdan :)"']), 10);


 console.log("All assertions passed!");