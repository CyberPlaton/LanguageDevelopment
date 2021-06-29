#include <thread>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <fstream>


#include "ColorConsole.h"
#include "Any.h"


class Environment
{
public:
	Environment(Environment* parent) : parent_env(parent)
	{
	}


	Any& assign(const std::string& name, Any& value)
	{
		_resolve(name).record[name] = std::move( value );
		return value;
	}


	Any& define(const std::string& name, Any& value)
	{
		record.emplace(name, value);
		return value;
	}


	Any& lookup(const std::string& name)
	{
		return _resolve(name).record[name];
	}


private:

	// Variables record of this environment.
	std::map<std::string, Any> record;


	// Parent environment.
	Environment* parent_env = nullptr;

private:


	Environment& _resolve(const std::string& name)
	{
		using namespace std;

		// Try find variable in own record.
		for (auto& entry : record)
		{
			if (COMPARE_STRINGS_2(entry.first, name) == 0) return *this;
		}

		// Else check parent or throw.
		if (parent_env)
		{
			return parent_env->_resolve(name);
		}
		else
		{
			cout << color(colors::RED);
			cout << "Variable not Defined \"" << name << "\"" << white << endl;

			throw std::runtime_error("Variable not Defined!");
		}
	}
};






class Eva
{
public:
	Eva(Environment* env)
	{
		if (env == nullptr)
		{
			global_environment = new Environment(0);
		}
		else
		{
			global_environment = env;
		}
	}



	Any& eval(Exp& exp, Environment* env = nullptr)
	{
		using namespace std;

		if (!env) env = global_environment;


		/*
		* Self evaluating.
		*/
		if (_isNumber(exp))
		{
			return exp.expression[0];
		}
		if (_isString(exp))
		{
			return exp.expression[0];
		}
		if (_isBoolean(exp))
		{
			return exp.expression[0];
		}


		/*
		* OpCodes.
		*/
		if (_isOpCode(exp))
		{
			std::string op_code = std::string(exp.expression[0].as<const char*>());


			/*
			* Comparison Ops.
			*/
			if (COMPARE_STRINGS(op_code, "<") == 0)
			{
				Any& result = *new Any(false, Any::Type::TYPE_BOOL);
				result.m_Value = this->eval(*new Exp(exp.expression[1]), env) < this->eval(*new Exp(exp.expression[2]), env);
				return result;
			}
			else if (COMPARE_STRINGS(op_code, ">") == 0)
			{
				Any& result = *new Any(false, Any::Type::TYPE_BOOL);
				result.m_Value = this->eval(*new Exp(exp.expression[1]), env) > this->eval(*new Exp(exp.expression[2]), env);
				return result;
			}
			else if (COMPARE_STRINGS(op_code, "<=") == 0)
			{
				Any& result = *new Any(false, Any::Type::TYPE_BOOL);
				result.m_Value = this->eval(*new Exp(exp.expression[1]), env) <= this->eval(*new Exp(exp.expression[2]), env);
				return result;
			}
			else if (COMPARE_STRINGS(op_code, ">=") == 0)
			{
				Any& result = *new Any(false, Any::Type::TYPE_BOOL);
				result.m_Value = this->eval(*new Exp(exp.expression[1]), env) >= this->eval(*new Exp(exp.expression[2]), env);
				return result;
			}
			else if (COMPARE_STRINGS(op_code, "==") == 0)
			{
				Any& result = *new Any(false, Any::Type::TYPE_BOOL);
				result.m_Value = this->eval(*new Exp(exp.expression[1]), env) == this->eval(*new Exp(exp.expression[2]), env);
				return result;
			}
			else if (COMPARE_STRINGS(op_code, "!=") == 0)
			{
				Any& result = *new Any(false, Any::Type::TYPE_BOOL);
				result.m_Value = this->eval(*new Exp(exp.expression[1]), env) != this->eval(*new Exp(exp.expression[2]), env);
				return result;
			}


			/*
			* Math.
			*/
			if (COMPARE_STRINGS(op_code, "+") == 0)
			{
				return this->eval(*new Exp(exp.expression[1]), env) + this->eval(*new Exp(exp.expression[2]), env);
			}
			if (COMPARE_STRINGS(op_code, "*") == 0)
			{
				return this->eval(*new Exp(exp.expression[1]), env) * this->eval(*new Exp(exp.expression[2]), env);
			}
			if (COMPARE_STRINGS(op_code, "/") == 0)
			{
				return this->eval(*new Exp(exp.expression[1]), env) / this->eval(*new Exp(exp.expression[2]), env);
			}



			/*
			* Variables definition and assignment.
			*/
			if (COMPARE_STRINGS(op_code, "var") == 0)
			{
				return env->define(std::string(exp.expression[1].as<const char*>()), this->eval(* new Exp(exp.expression[2]), env));
			}

			if (COMPARE_STRINGS(op_code, "set") == 0)
			{
				return env->assign(std::string(exp.expression[1].as<const char*>()), this->eval(*new Exp(exp.expression[2]), env));
			}


			/*
			* Flow control.
			*/
			if (COMPARE_STRINGS(op_code, "begin") == 0)
			{
				Environment* block_env = new Environment(env);
				return _evalBlock(exp, block_env);
			}


			/*
			* Branching.
			*/
			if (COMPARE_STRINGS(op_code, "if") == 0)
			{
				if (eval(*new Exp(exp.expression[1]), env).as< bool >()) // Condition
				{
					return eval(*new Exp(exp.expression[2]), env); // Consequent
				}
				else
				{
					return eval(*new Exp(exp.expression[3]), env); // Alternate
				}

			}


			if (COMPARE_STRINGS(op_code, "while") == 0) // [1] = condition, [2] = body.
			{
				Any& result = *new Any();

				// Possible implicit conversion from number to boolean.
				while (this->eval(*new Exp(exp.expression[1]), env) == Any(true, Any::TYPE_BOOL))
				{
					result = this->eval(*new Exp(exp.expression[2]), env);
				}

				return result;
			}


		}

		/*
		* Variable access.
		*/
		if (_isVariable(exp))
		{
			return env->lookup(std::string(exp.expression[0].as< const char*>()));
		}



		if (_isExpression(exp))
		{
			return eval(*new Exp( exp.expression[0].as<Exp>()), env);
		}


		cout << color(colors::RED);
		cout << "Expression not implemented: { " << endl;
		exp.representSelf(1);
		cout << color(colors::RED);
		cout << "} " << endl;
		throw std::runtime_error("Expression not implemented!");
	}




private:

	Environment* global_environment = nullptr;


private:


	bool _isNumber(Exp& exp)
	{
		return exp.expression[0].m_Type == Any::Type::TYPE_NUMBER;
	}

	bool _isString(Exp& exp)
	{
		if (exp.expression[0].m_Type == Any::Type::TYPE_STRING)
		{
			// We do not need to strip the quotes of the string,
			// as it is already done.
			return true;
		}

		return false;
	}


	bool _isVariable(Exp& exp)
	{
		// We dont need to check for validity of the name, as it was already done.
		return exp.expression[0].m_Type == Any::Type::TYPE_VAR;
	}

	bool _isOpCode(Exp& exp)
	{
		return exp.expression[0].m_Type == Any::Type::TYPE_OPCODE;
	}

	bool _isBoolean(Exp& exp)
	{
		return exp.expression[0].m_Type == Any::Type::TYPE_BOOL;
	}

	bool _isExpression(Exp& exp)
	{
		return exp.expression[0].m_Type == Any::Type::TYPE_EXP;
	}

	Any& _evalBlock(Exp& exp, Environment* env)
	{
		Any& result = *new Any();

		bool skip_op_code = false;

		for (auto& e : exp.expression)
		{
			if (!skip_op_code)
			{
				skip_op_code = true;
				continue;
			}

			result = eval(*new Exp(e), env);
		};

		return result;
	}
};




/*
* EVA BUILT-IN FUNCTIONS
*/
Any& eva_built_in_print(const std::string& text)
{
	using namespace std;
	cout << color(colors::DARKCYAN);
	cout << "[EVA] eva_built_in_print(...) \"";
	
	cout << color(colors::CYAN);
	cout << text;

	cout << color(colors::DARKCYAN);
	cout << "\"" << white << endl;

	// Basically Return "void" = "null".
	return *new Any(nullptr, Any::Type::TYPE_VAR);
}


using EVA_MATH_FUNC = Any & (*)(Any&, Any&);
Any& eva_built_in_add(Any& lhs, Any& rhs)
{
	using namespace std;
	cout << color(colors::DARKCYAN);
	cout << "[EVA] built_in_add(...)" << white << endl;

	
	Any& r = lhs + rhs;
	return r;
}

Any& eva_built_in_minus(Any& lhs, Any& rhs)
{
	using namespace std;
	cout << color(colors::DARKCYAN);
	cout << "[EVA] eva_built_in_minus(...)" << white << endl;


	Any& r = lhs - rhs;
	return r;
}


Any& eva_built_in_mul(Any& lhs, Any& rhs)
{
	using namespace std;
	cout << color(colors::DARKCYAN);
	cout << "[EVA] eva_built_in_mul(...)" << white << endl;


	Any& r = lhs * rhs;
	return r;
}



Any& eva_built_in_div(Any& lhs, Any& rhs)
{
	using namespace std;
	cout << color(colors::DARKCYAN);
	cout << "[EVA] eva_built_in_div(...)" << white << endl;


	Any& r = lhs / rhs;
	return r;
}



int main()
{
	using namespace std;

	// Create some expressions for evaluation.
	Exp e("\"Hello\"", "\"World\"");
	e.representSelf();


	Exp e_num(2019.0);
	e_num.representSelf();


	Exp e_bool(false);
	e_bool.representSelf();


	Exp e6(e, e_num, e_bool, e);
	e6.representSelf();

	

	Exp e_scope_1("var", "x", 10.0);
	e_scope_1.representSelf();

	Exp e_scope_2("var", "y", 20.0);
	e_scope_2.representSelf();

	Exp e_scope_3_0("*", "x", "y");
	e_scope_3_0.representSelf();

	Exp e_scope_3("+", e_scope_3_0, 30.0);
	e_scope_3.representSelf();


	Exp e_scope("begin",
				e_scope_1,
				e_scope_2,
				e_scope_3);
	e_scope.representSelf();



	Exp e_scoped_scope("begin",
					   e_scope,
					   e_scope);
	e_scoped_scope.representSelf();




	/*
	* Setup the eva interpreter and global environment.
	*/
	Environment* global_env = new Environment(nullptr);

	/*
	* Define pre-defined functions, variables etc. for environment.
	*/
	global_env->define("true", *new Any(true, Any::Type::TYPE_BOOL));
	global_env->define("false", *new Any(false, Any::Type::TYPE_BOOL));
	global_env->define("null", *new Any(nullptr, Any::Type::TYPE_VAR));



	Any& func = *new Any(&eva_built_in_print, Any::Type::TYPE_VAR);
	Any& func2 = *new Any(&eva_built_in_add, Any::Type::TYPE_VAR);
	Any& func3 = *new Any(&eva_built_in_minus, Any::Type::TYPE_VAR);
	Any& func4 = *new Any(&eva_built_in_mul, Any::Type::TYPE_VAR);
	Any& func5 = *new Any(&eva_built_in_div, Any::Type::TYPE_VAR);


	global_env->define("print", func);
	global_env->define("add", func2);
	global_env->define("sub", func3);
	global_env->define("mul", func4);
	global_env->define("div", func5);


	Eva eva(global_env);




	/*
	* As we execute the code, we get that e.g. "result" is OPCODE,
	* so how is this correct?
	* 
	* =>	Well actually, EVERYTHING, that is not a STRING is an OPCODE,
	*		e.g. "result" is here a variable name and will be looked up in the Environment::Record map.
	*		e.g. "<", "begin", "while", "set" etc. a are clearly an OPCODE.
	*/
	Exp while_loop("begin",

		Exp("var", "counter", 0.0),
		Exp("var", "result", 0.0),

		Exp("while", Exp("<", "counter", 10.0),
			Exp("begin",
				
				Exp("set", "result", Exp("+", "result", 1.0)),
				Exp("set", "counter", Exp("+", "counter", 1.0))

				)),
		"result"
	);
	while_loop.representSelf();


	
	/*
	* Self-Evaluating
	*/
	Exp test_e = Exp(20.0);
	if (eva.eval(test_e).as<double>() == 20.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	test_e = Exp("\"Hello\"");
	if (std::string(eva.eval(test_e).as<const char*>()).compare("Hello") == 0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	test_e = Exp(false);
	if (eva.eval(test_e).as<bool>() == false)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	/*
	* Math
	*/
	test_e = Exp("+", 25.0, 25.0);
	if (eva.eval(test_e).as< double >() == 50.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	test_e = Exp("*", 10.0, 25.0);
	if (eva.eval(test_e).as< double >() == 250.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	test_e = Exp("/", 50.0, 2.0);
	if (eva.eval(test_e).as< double >() == 25.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	/*
	* Var decl and access
	*/
	test_e = Exp("var", "my_variable_09182___nice", 25.0);
	if (eva.eval(test_e).as< double >() == 25.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	test_e = Exp("set", "my_variable_09182___nice", 50.0);
	if (eva.eval(test_e).as< double >() == 50.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	test_e = Exp("my_variable_09182___nice");
	if (eva.eval(test_e).as< double >() == 50.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	/*
	* Flow control.
	*/

	/*
	* { // begin
	*	var x = "hello"
	*	var y = false
	*   y
	* }
	*/
	test_e = Exp("begin", Exp("var", "x", "\"Hello\""), Exp("var", "y", false), "y");
	if (eva.eval(test_e).as< bool >() == false)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}


	/*
	* { // begin
	*	{ // begin
	* 
	*		var  = "Hello"
	*		var y = false
	*		y
	*	}
	* }
	*/
	test_e = Exp("begin",
			 Exp("begin",
				Exp("var", "x", "\"Hello\""), Exp("var", "y", false), "y")
	);
	if (eva.eval(test_e).as< bool >() == false)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}


	/*
	* { // begin
	* 
	*  var outer_variable = 1.0
	* 
	*	{ // begin
	*
	*		var  = "Hello"
	*		var y = false
	*		outer_variable = 20.0
	*	}
	* 
	*  outer_variable
	* }
	*/
	test_e = Exp("begin",
		Exp("var", "outer_variable", 1.0),
		Exp("begin",
			Exp("var", "x", "\"Hello\""), Exp("var", "y", false), Exp("set", "outer_variable", 20.0)),
		Exp("outer_variable")
	);
	if (eva.eval(test_e).as< double >() == 1.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	/*
	* Branching Test.
	*/

	/*
	* { // begin
	*	var x = 10.0
	* 	var y = 10.0
	*	
	*	if x > 10.0 // Evaluates to false
	*		y = 20.0
	*	else
	*		y = 30.0 // So we set y to 30.0
	*
	*	y // Returns value of y.
	* }
	* 
	* Expected result is "y == 30.0".
	*/
	test_e = Exp("begin",
		Exp("var", "x", 10.0),
		Exp("var", "y", 0.0),

		Exp("if", Exp(">", "x", 10.0),
			Exp("set", "y", 20.0),
			Exp("set", "y", 30.0)),
		Exp("y")
	);

	if (eva.eval(test_e).as< double >() == 30.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}



	test_e = Exp("begin",
		Exp("var", "x", 20.0),
		Exp("var", "y", 0.0),

		Exp("if", Exp("<", "x", 100.0),
			Exp("set", "y", 0.5),
			Exp("set", "y", 30.0)),
		Exp("y")
	);

	if (eva.eval(test_e).as< double >() == 0.5)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}


	/*
	* { // begin
	* 
	*	var	counter = 0.0
	* 	var	result = 0.0
	* 
	*	while counter < 10.0
	*		{
	*			result = result + 1.0
	*			counter = counter + 1.0
	*		}
	* 
	*	result
	* }
	* 
	* Expected is "result == 10.0".
	*/
	test_e = Exp("begin",
		Exp("var", "counter", 0.0),
		Exp("var", "result", 0.0),

		Exp("while", Exp("<", "counter", 10.0),
			
			Exp("begin",
				Exp("set", "result", Exp("+", "result", 1.0)),
				Exp("set", "counter", Exp("+", "counter", 1.0)))
		   ),
		Exp("result")
	);

	if (eva.eval(test_e).as< double >() == 10.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}



	/*
	* Testing built-in variables.
	*
	* Here we introduce "null", which is implemented as a nullptr of C++.
	*/
	if (eva.eval(*new Exp("true")).as<bool>() == true)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	if (eva.eval(*new Exp("false")).as<bool>() == false)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	if (eva.eval(*new Exp("null")).as<std::nullptr_t>() == nullptr)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	// For convinience we could do:
	using null = std::nullptr_t;
	if (eva.eval(*new Exp("null")).as<null>() == nullptr)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	if (eva.eval(*new Exp("print")).as<Any&(*)(const std::string&)>()("Printing Some Stuff Here...").as<null>() == nullptr)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}


	Any& a = *new Any(25.0, Any::Type::TYPE_NUMBER);
	Any& b = *new Any(25.0, Any::Type::TYPE_NUMBER);

	if (eva.eval(*new Exp("add")).as<Any & (*)(Any&, Any&)>()(a, b).as<double>() == 50.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	a = *new Any(25.0, Any::Type::TYPE_NUMBER);
	b = *new Any(25.0, Any::Type::TYPE_NUMBER);
	if (eva.eval(*new Exp("add")).as<EVA_MATH_FUNC>()(a, b).as<double>() == 50.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	a = *new Any(25.0, Any::Type::TYPE_NUMBER);
	b = *new Any(25.0, Any::Type::TYPE_NUMBER);
	if (eva.eval(*new Exp("sub")).as<EVA_MATH_FUNC>()(a, b).as<double>() == 0.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	a = *new Any(25.0, Any::Type::TYPE_NUMBER);
	b = *new Any(25.0, Any::Type::TYPE_NUMBER);
	if (eva.eval(*new Exp("mul")).as<EVA_MATH_FUNC>()(a, b).as<double>() == 625.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	a = *new Any(25.0, Any::Type::TYPE_NUMBER);
	b = *new Any(25.0, Any::Type::TYPE_NUMBER);
	if (eva.eval(*new Exp("div")).as<EVA_MATH_FUNC>()(a, b).as<double>() == 1.0)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}

	//assert(test_math_and_recursive_math());
	//assert(test_var_decl());
	//assert(test_scope_declaration());

	return 0;
}