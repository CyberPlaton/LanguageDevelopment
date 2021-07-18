#include <thread>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <fstream>
#include <functional>


#include "ColorConsole.h"
#include "Any.h"


class Environment
{
public:
	enum ScopeType
	{
		SCOPE_INVALID = -1,
		SCOPE_GLOBAL = 0, // Main Scope for the program.
		SCOPE_FUNCTION,   // Created Scope on entering a function.
		SCOPE_AGGREGATE   // Created Scope for each created class/struct.
	};

public:
	Environment(Environment* parent, ScopeType type = ScopeType::SCOPE_GLOBAL) : parent_env(parent)
	{
		Environment::env_count++;

		if (parent == nullptr)
		{
			scope_name = "Global Environment";
		}
		else
		{
			scope_name = parent->scope_name + "_child_" + std::to_string(Environment::env_count);

			parent_env->children_env.push_back(this);
		}

		scope_type = type;
	}

	bool doesExist(const std::string& name)
	{
		try
		{
			if (_resolve(name).record[name].m_Value.has_value())
			{
				return true;
			}
		}
		catch (...)
		{
			return false;
		}

		return false;
	}

	/*
	* Used in e.g. "set x = 25",
	* meaning giving new value to an existing variable.
	*/
	Any& assign(const std::string& name, Any& value)
	{
		_resolve(name).record[name] = std::move( value );
		return value;
	}


	/*
	* Used in e.g. "var x = 10",
	* meaning introducing a new variable into the record.
	*/
	Any& define(const std::string& name, Any& value)
	{
		record.emplace(name, value);
		return value;
	}


	Any& lookup(const std::string& name)
	{
		return _resolve(name).record[name];
	}


	std::string env_name() { return this->scope_name; }
	ScopeType env_scope_type() { return this->scope_type; }
	
	static Environment* get_global_environment(Environment* kid)
	{
		while (kid->parent_env != nullptr) // Go the up the tree hierarchy.
		{
			kid = kid->parent_env;
		}

		return kid; // The global env. at this point.
	}

	static void print_env_tree(Environment* root)
	{
		root->_print_self_and_children(0);
	}

	static std::string scope_type_string(ScopeType t)
	{
		switch (t)
		{
		case ScopeType::SCOPE_AGGREGATE:
			return "aggregate";
		case ScopeType::SCOPE_FUNCTION:
			return "function";
		case ScopeType::SCOPE_GLOBAL:
			return "global";
		default:
			return "invalid";
		}
	}

private:

	static unsigned int env_count;

	// Variables record of this environment.
	std::map<std::string, Any> record;


	// Parent environment.
	Environment* parent_env = nullptr;
	std::vector<Environment*> children_env;

	std::string scope_name;
	ScopeType scope_type = ScopeType::SCOPE_INVALID;

private:

	void _print_self_and_children(int offset = 0)
	{
		using namespace std;
		cout << color(colors::GREEN);
		for (int i = 0; i < offset; i++) cout << "\t";
		cout << "Environment := { " << endl;


		cout << color(colors::YELLOW);
		for (int i = 0; i < offset; i++) cout << "\t";
		cout << "Scope Name: ";
		cout << color(colors::MAGENTA);
		for (int i = 0; i < offset; i++) cout << "\t";
		cout << scope_name << white << endl;

		cout << color(colors::YELLOW);
		for (int i = 0; i < offset; i++) cout << "\t";
		cout << "Scope Type: ";
		cout << color(colors::MAGENTA);
		for (int i = 0; i < offset; i++) cout << "\t";
		cout << Environment::scope_type_string(scope_type) << white << endl;

		
		_print_scope_members(offset + 1);

		cout << color(colors::GREEN);
		cout << "} " << white << endl << endl << endl;

		for (auto& kid : children_env)
		{
			kid->_print_self_and_children(offset + 1);
		}
	}


	void _print_scope_members(int offset = 0)
	{
		using namespace std;
		cout << color(colors::DARKGREEN);
		for (int i = 0; i < offset; i++) cout << "\t";
		cout << "Environment Record := { " << endl;

		for (auto& entry : record)
		{
			cout << color(colors::DARKGREEN);
			for (int i = 0; i < offset; i++) cout << "\t";
			cout << "\"" << entry.first << "\" := { " << endl;

			entry.second.reprSelf(offset + 1);

			cout << color(colors::DARKGREEN);
			for (int i = 0; i < offset; i++) cout << "\t";
			cout << "}," << white << endl;
		}

		cout << color(colors::DARKGREEN);
		for (int i = 0; i < offset - 1; i++) cout << "\t";
		cout << "};" << white << endl << endl << endl;
	}


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
			cout << "Variable not Defined \"" << name << "\"" << endl;
			cout << "Environment: \""<< this->scope_name << "\"" << white << endl;

			throw std::runtime_error("Variable not Defined!");
		}
	}
};

unsigned int Environment::env_count = 0;




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



	Any& eval(Exp& exp, Environment* env = nullptr, bool debug_out = false)
	{
		using namespace std;

		if (!env) env = global_environment;

		if (debug_out)
		{
			cout << color(colors::DARKCYAN);
			cout << "EVAL EXP: " << endl;
			exp.representSelf();
		}

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
				Environment* block_env = new Environment(env, Environment::SCOPE_FUNCTION);
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


			/*
			* User function declarations.
			* 
			*/
			if (COMPARE_STRINGS(op_code, "def") == 0)
			{
				// Function name.
				std::string name = exp.expression[1].as<const char*>();


				Exp body;
				
				for (int i = 0; i < exp.expression.size(); i++)
				{
					// Skip "def" keyword and function name.
					if (i == 0 || i == 1) continue;

					body.expression.push_back(exp.expression[i]);
				}


				// Store function in environment as an expression,
				// which can be looked up by name and evaluated dynamically.
				return env->define(name, *new Any(body, Any::TYPE_EXP));
			}

		}

		/*
		* Variable access.
		*/
		if (_isVariable(exp))
		{
			// Get what is stored under name.
			Any& var = env->lookup(std::string(exp.expression[0].as< const char*>()));


			// If we stored an expression under the name,
			// then evaluate it first and then return the result, so take it as a "function call".
			if (var.m_Type == Any::Type::TYPE_EXP)
			{

				// First, the count of parameters and defined parameters in function should match,
				// else display an error indicating problem.
				if (exp.expression.size() != var.as<Exp>().expression.size())
				{
					cout << color(colors::RED);
					cout << "Mismatch of Parameter Count in Function Body: {" << white << endl;

					var.reprSelf(1);

					cout << color(colors::RED);
					cout << "}" << white << endl;


					// Show expected number and actually supplied.
					cout << color(colors::RED);
					cout << "Supplied: " << exp.expression.size() - 1 << endl; // Do not count the function name as param.
					cout << "Expected: " << var.as<Exp>().expression.size() - 1 << white << endl; // Do not count the function body as param.

					throw std::runtime_error("Parameter Mismatch in Function!");
				}


				Exp body;
				Environment* activation_env = new Environment(env, Environment::SCOPE_FUNCTION); // This is DYNAMIC!


				Exp e = var.as<Exp>();
				for (int index = 0; index <= exp.expression.size(); index++)
				{
					/*
					* NOTE!
					* 
					* The index goes from 0 to exp.expression.size(),
					* because the 0-th index in "exp.expression[index]" is the function name, which we can skip,
					* after it we have a variable amount of variable names: "exp.expression[n]".
					* 
					* And as "exp.expression" and "e.expression" are ensured to have the same size,
					* (meaning there are same amount of given parameters and needed parameters),
					* we would not catch the actual function body defined in the last entry of "e.expression"
					* if we would only iterate through 0 to "exp.expression.size() - 1".
					* 
					*/


					// Skip the function-name
					if (index == 0) continue;


					// Get the function body if we reached it.
					if (e.expression[index - 1].m_Type == Any::TYPE_EXP)
					{
						body = Exp(e.expression[index - 1]);
						break;
					}
					else
					{
						// Get the parameter name.
						std::string param_name = e.expression[index - 1].as<const char*>();

						// Get the parameter self.
						Any param_value = exp.expression[index];


						if (debug_out)
						{
							cout << color(colors::RED);
							cout << "param_name := \"" << param_name << "\" ";
							param_value.reprSelf(1);
						}


						// Try define param in environment
						if (!env->doesExist(param_name))
						{
							if (debug_out)
							{
								cout << color(colors::RED);
								cout << "define := \"" << param_name << "\" in env" << white << endl;

							}
							
							activation_env->define(param_name, param_value);
						}
						else
						{
							if (debug_out)
							{
								cout << color(colors::RED);
								cout << "skip definition of existing param := \"" << param_name << "\" in env " << white << endl;
							}
						}

					}
				}

				/*
				* TODO Current Problem: 16.07.21.
				* 
				* Value of parameter changes in environment.record as we proceed with execution.
				* e.g. in the expression
				* 
				*	Exp("+", Exp("+", "func_param", "func_param"), "func_param")),
				*		Exp("square", 2.0)
				* 
				* we first add "func_param" + "func_param", which results in 4.0,
				* after that as we access to add again "func_param" + "func_param"
				* it results in 4.0 + 4.0 = 8.0,
				* which is not the desired behaviour.
				*/

				return this->eval(body, activation_env);
			}
			else // Else just return the value.
			{
				if (debug_out)
				{
					cout << color(colors::RED);
					cout << "VARIABLE ACCESS := "; var.reprSelf(1); cout << endl;
				}
				
				return var;
			}
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
	cout << "[EVA] eva_built_in_print(...)\t";
	
	cout << color(colors::CYAN);
	cout << text;

	cout << color(colors::DARKCYAN);
	cout << white << endl;

	// Basically Return "void" = "null".
	return *new Any(nullptr, Any::Type::TYPE_VAR);
}


template < class ... Args >
Any& eva_built_in_printf(Args... args)
{
	using namespace std;
	cout << color(colors::DARKCYAN);
	cout << "[EVA] eva_built_in_printf(...)\t";

	std::vector<Any> vec = { args... };

	std::streamsize p = std::cout.precision();

	for (auto& e : vec)
	{
		switch (e.type())
		{
		case Any::Type::TYPE_BOOL:

			cout << color(colors::CYAN);
			cout << e.as<bool>() << " ";
			break;

		case Any::Type::TYPE_NUMBER:

			cout << color(colors::CYAN);
			cout.precision(32);
			cout <<  e.as<double>() << " ";
			cout.precision(p);
			break;

		case Any::Type::TYPE_STRING:

			cout << color(colors::CYAN);
			cout << e.as<const char*>();
			break;

		default:
			break;
		}

	}

	cout << color(colors::DARKCYAN);
	cout << white << endl;
	
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

	/*
	* This function is a test on how we could achieve variable parameter count in eva.
	* 
	* Here we define a function that takes 4 "Any" values as param and prints them,
	* do define the same with more or less params, do:
	* 
	* e.g.
	* 
	* *new Any(&eva_built_in_printf<Any&, Any&, Any&, Any&, Any&, Any&, Any&, Any&>, Any::Type::TYPE_VAR)	// For 8 parameters...
	* 
	* and call later to eval with:
	* 
	* eva.eval(*new Exp("printf")).as<Any& (*)(Any&, Any&, Any&, Any&, Any&, Any&, Any&, Any&)>()(first, second, third, fourth, fifth, sixth, seventh, eight);
	*/
	Any& func6 = *new Any(&eva_built_in_printf<Any&, Any&, Any&, Any&>, Any::Type::TYPE_VAR);
	global_env->define("printf", func6);



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
	*		e.g. "<", "begin", "while", "set" etc. are clearly an OPCODE.
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


	Any& name = *new Any("Bogdan ", Any::Type::TYPE_STRING);
	Any& name2 = *new Any(true, Any::Type::TYPE_BOOL);
	Any& name3 = *new Any(99182.019282978111111111112151241231215142367847694568, Any::Type::TYPE_NUMBER);
	Any& name4 = *new Any("Nice! \n", Any::Type::TYPE_STRING);


	eva.eval(*new Exp("printf")).as<Any& (*)(Any&, Any&, Any&, Any&)>()(name, name2, name3, name4);




	/*
	* USER DEFINED FUNCTIONS.
	* 
	* { // begin
	* 
	* 
	*	def square(func_param) 
	*		(func_param + func_param) + func_param			// return
	* 
	* }
	* 
	* e.g. func_param = 2.0
	*		should result in (2.0 + 2.0) + 2.0 = 6.0.
	* 
	*/
	test_e = Exp("begin",
				Exp("def", "square", "func_param",
						Exp("+", Exp("+", "func_param", "func_param"), "func_param")
				), 
		Exp("square", 2.0)
	);

	double result = eva.eval(test_e).as<double>();
	double expect = 6.0;
	if (result == expect)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	else
	{
		cout << color(colors::RED);
		cout << "Expected:" << expect << endl;
		cout << "Result:" << result << white << endl;
	}

	test_e = Exp("begin",
		Exp("def", "square", "func_param",
			Exp("*", Exp("+", "func_param", "func_param"), "func_param")
		),
		Exp("square", 4.0)
	);

	/*
	* (4 + 4) * 4 = 8 * 4 = 32.
	*/
	result = eva.eval(test_e).as<double>();
	expect = 32.0;
	if (result == expect)
	{
		cout << color(colors::GREEN);
		cout << "Passed!" << white << endl;
	}
	else
	{
		cout << color(colors::RED);
		cout << "Expected:" << expect << endl;
		cout << "Result:" << result << white << endl;
	}



	// Print Environments.
	//Environment::print_env_tree(global_env);

	return 0;
}