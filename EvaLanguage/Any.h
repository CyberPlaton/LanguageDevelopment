#ifndef ANY_H
#define ANY_H
#pragma once

#include <string>
#include <iostream>
#include <any>
#include <vector>
#include <array>
#include <regex>


#include "ColorConsole.h"


#define COMPARE_STRINGS(x, y) strcmp(x.c_str(), y) // Utility. Comparing strings.
#define COMPARE_STRINGS_2(x, y) strcmp(x.c_str(), y.c_str()) // Utility. Comparing strings.


struct Exp;
class Any
{
public:
	enum Type
	{
		TYPE_INVALID = -1,
		TYPE_OPCODE,
		TYPE_NUMBER,
		TYPE_STRING,
		TYPE_BOOL,
		TYPE_EXP,
		TYPE_VAR
	};

public:
	Any(std::any value, Type type) : m_Value(value), m_Type(type) {}
	Any() {}

	Any& operator=(const Any& rhs)
	{
		this->m_Type = rhs.m_Type;
		this->m_Value = rhs.m_Value;
		return *this;
	}


	bool operator<(const Any& rhs)
	{
		using namespace std;

		if (m_Type != rhs.m_Type)
		{
			cout << color(colors::RED);
			cout << "Invalid Comparison Operands!" << white << endl;

			throw std::runtime_error("Invalid Operands Supplied!");
		}

		// Comparison fo now only for numbers.
		if (m_Type == Type::TYPE_NUMBER)
		{
			return std::any_cast<double>(m_Value) < std::any_cast<double>(rhs.m_Value);
		}

		return false;
	}

	bool operator>(const Any& rhs)
	{
		using namespace std;

		if (m_Type != rhs.m_Type)
		{
			cout << color(colors::RED);
			cout << "Invalid Comparison Operands!" << white << endl;

			throw std::runtime_error("Invalid Operands Supplied!");
		}

		// Comparison fo now only for numbers.
		if (m_Type == Type::TYPE_NUMBER)
		{
			return std::any_cast<double>(m_Value) > std::any_cast<double>(rhs.m_Value);
		}

		return false;
	}

	bool operator<=(const Any& rhs)
	{
		using namespace std;

		if (m_Type != rhs.m_Type)
		{
			cout << color(colors::RED);
			cout << "Invalid Comparison Operands!" << white << endl;

			throw std::runtime_error("Invalid Operands Supplied!");
		}

		// Comparison fo now only for numbers.
		if (m_Type == Type::TYPE_NUMBER)
		{
			return std::any_cast<double>(m_Value) <= std::any_cast<double>(rhs.m_Value);
		}

		return false;
	}

	bool operator>=(const Any& rhs)
	{
		using namespace std;

		if (m_Type != rhs.m_Type)
		{
			cout << color(colors::RED);
			cout << "Invalid Comparison Operands!" << white << endl;

			throw std::runtime_error("Invalid Operands Supplied!");
		}

		// Comparison fo now only for numbers.
		if (m_Type == Type::TYPE_NUMBER)
		{
			return std::any_cast<double>(m_Value) >= std::any_cast<double>(rhs.m_Value);
		}

		return false;
	}

	bool operator==(const Any& rhs)
	{
		using namespace std;

		if (m_Type != rhs.m_Type)
		{
			cout << color(colors::RED);
			cout << "Invalid Comparison Operands!" << white << endl;

			throw std::runtime_error("Invalid Operands Supplied!");
		}

		if (m_Type == Type::TYPE_NUMBER)
		{
			return std::any_cast<double>(m_Value) == std::any_cast<double>(rhs.m_Value);
		}


		if (m_Type == Type::TYPE_BOOL)
		{
			return std::any_cast<bool>(m_Value) == std::any_cast<bool>(rhs.m_Value);
		}


		return false;
	}


	bool operator!=(const Any& rhs)
	{
		using namespace std;

		if (m_Type != rhs.m_Type)
		{
			cout << color(colors::RED);
			cout << "Invalid Comparison Operands!" << white << endl;

			throw std::runtime_error("Invalid Operands Supplied!");
		}


		// Comparison fo now only for numbers.
		if (m_Type == Type::TYPE_NUMBER)
		{
			return std::any_cast<double>(m_Value) != std::any_cast<double>(rhs.m_Value);
		}

		return false;
	}

	Any& operator+(const Any& rhs)
	{
		if (m_Type != rhs.m_Type)
		{
			throw std::runtime_error("Invalid Addition Operands Supplied!");
		}


		if (m_Type == TYPE_NUMBER) // Standard addition of numbers.
		{
			return *new Any(std::any(this->as<double>() + std::any_cast<double>(rhs.m_Value)), Any::TYPE_NUMBER);
		}
		else if (m_Type == TYPE_STRING)// Addition of strings is just concat.
		{
			std::string concat = std::string(this->as<const char*>()) + std::string(std::any_cast<const char*>(rhs.m_Value)); // Concat as string...
			
			char* other = new char[strlen(concat.c_str()) + 1];
			strcpy(other, concat.c_str());
			
			return *new Any(std::any(std::move(reinterpret_cast<const char*>(other))), Any::TYPE_STRING);
		}
		else
		{
			throw std::runtime_error("Invalid Addition Operator Type Supplied!");
		}

		return *this;
	}

	Any& operator-(const Any& rhs)
	{
		if (!m_Type == TYPE_NUMBER ||
			m_Type != rhs.m_Type)
		{
			throw std::runtime_error("Invalid Subtraction Operator Type Supplied!");
		}


		if (m_Type == TYPE_NUMBER) // Standard subtraction of numbers.
		{
			return *new Any(std::any(this->as<double>() - std::any_cast<double>(rhs.m_Value)), Any::TYPE_NUMBER);
		}
		else // TODO
		{
			throw std::runtime_error("Subtraction of String not implemented!");
			//this->m_Value = std::any(std::string(this->as<const char*>()) + std::string(std::any_cast<const char*>(rhs.m_Value)));
		}

		return *this;
	}

	Any& operator*(const Any& rhs)
	{
		if (!m_Type == TYPE_NUMBER ||
			m_Type != rhs.m_Type)
		{
			throw std::runtime_error("Invalid Multiplication Operator Type Supplied!");
		}

		return *new Any(std::any(this->as<double>() * std::any_cast<double>(rhs.m_Value)), Any::TYPE_NUMBER);
	}

	Any& operator/(const Any& rhs)
	{
		if (!m_Type == TYPE_NUMBER ||
			m_Type != rhs.m_Type)
		{
			throw std::runtime_error("Invalid Division Operator Type Supplied!");
		}


		if (std::any_cast<double>(rhs.m_Value) == 0.0)
		{
			throw std::runtime_error("Fatal Error: Zero-Division!");
		}

		return *new Any(std::any(this->as<double>() / std::any_cast<double>(rhs.m_Value)), Any::TYPE_NUMBER);
	}

	// Returns whether this is a null variable of type std::nullptr_t.
	bool isNull()
	{
		return _isNull(m_Value);
	}

	// Return the type as unsigned int.
	Type type() const { return m_Type; }


	// Returns the data as std::any.
	std::any data() const { return m_Value; }


	// Use to access the value.
	// You have to know the type in order to convert and access it.
	//
	// So a naive solution would be a switch on "type()" of value,
	// if it is changing during runtime.
	// 
	// Converting to string is somewhat special:
	// std::string s = other.as< const char* >();
	template < typename T >
	T as() {

		try {

			// Return the memory address, 
			// where the object is stored.
			return std::any_cast<T>(m_Value);
		}
		catch (const std::bad_any_cast& e) {

			using namespace std;
			cout << color(colors::RED);
			cout << "Any: Bad Cast! From \"" << m_Value.type().name() << "\" to \"" << typeid(T).name() << "\"" << white << endl;

			throw runtime_error("Fatal bad cast!");
		}

	}


	void setType(Type t)
	{
		m_Type = t;
	}

	void setData(std::any d)
	{
		m_Value = std::move(d);
	}



	void reprSelf(unsigned offset = 0);

public:

	std::any m_Value;
	Type m_Type;

private:


	bool _isNull(std::any& a)
	{
		using namespace std;

		std::any dummy(nullptr);
		if (dummy.type().hash_code() == a.type().hash_code())
		{
			cout << color(colors::RED);
			cout << "WARNING! Fatal \"null\" Variable Access!" << white << endl;
			return true;
		}

		return false;
	}
};



struct Exp
{
	template < class ...Args>
	Exp(Args... args)
	{
		using namespace std;

		std::vector<std::any> pre_exp = { args... };

		for (auto& e : pre_exp)
		{
			// Create Any class expressions from the std::any values we got...
			// Allowed Datatypes are BOOL, STRING, NUMBER and EXP

			if (_isNumber(e))
			{
				cout << "Number" << endl;

				// Then just store not the raw args but the created Any from before...
				expression.push_back(Any(e, Any::Type::TYPE_NUMBER));
			}
			else if (_isBoolean(e))
			{
				cout << "Bool" << endl;
				expression.push_back(Any(e, Any::Type::TYPE_BOOL));
			}
			else if (_isString(e))
			{
				cout << "String" << endl;

				// Before storing the string, strip the quotes.
				std::string s = std::string(std::any_cast<const char*>(e));
				std::string sliced_string = s.substr(1, s.length() - 2);

				char* other = new char[strlen(sliced_string.c_str()) + 1];
				strcpy(other, sliced_string.c_str());

				expression.push_back(Any(std::move(reinterpret_cast<const char*>(other)), Any::Type::TYPE_STRING));
			}
			else if (_isExpression(e))
			{
				cout << "Expression" << endl;
				expression.push_back(Any(e, Any::Type::TYPE_EXP));
			}
			else if (_isOpCode(e))
			{
				cout << "OpCode" << endl;
				expression.push_back(Any(e, Any::Type::TYPE_OPCODE));
			}
			else if (_isVariable(e))
			{
				cout << "Variable" << endl;
				expression.push_back(Any(e, Any::Type::TYPE_VAR));
			}
			else if (_isAny(e))
			{
				cout << "Any" << endl;
				expression.push_back(std::any_cast<Any&>(e));
			}
			else
			{
				cout << color(colors::RED);
				cout << "Unsupported Variable Type!" << white << endl;
				throw std::runtime_error("Unsupported Variable Type!");
			}
		}

	}




	void representSelf(int offset = 0)
	{
		using namespace std;

		cout << color(colors::CYAN);
		cout << "Expression : { " << white << endl;


		for (auto& e : expression) e.reprSelf(offset + 1);


		cout << color(colors::CYAN);
		for (int i = 0; i < offset - 1; i++) cout << "\t";
		cout << "};" << white << endl << endl;
	}




	/*
	* If "type" of expression is BOOL, STRING or NUMBER
	* expression.size() is 1 and holds the value.
	*
	* if "type" of expression is EXP then
	* expression.size() can be variable and can hold either another
	* EXP as value (or values) etc.
	*
	* The Exp class is stored with the help of the Any class,
	* so we eventually find the end of recursion and
	* can get the basic variable type.
	*/
	std::vector<Any> expression;



private:

	bool _isAny(std::any& a)
	{
		Any d;
		std::any any_dummy(d);
		return a.type().hash_code() == any_dummy.type().hash_code();
	}

	bool _isNumber(std::any& a)
	{
		std::any dummy_num(0.0);
		return a.type().hash_code() == dummy_num.type().hash_code();
	}

	bool _isBoolean(std::any& a)
	{
		std::any dummy_bool(false);
		return a.type().hash_code() == dummy_bool.type().hash_code();
	}

	bool _isString(std::any& a)
	{
		std::any dummy_str("Im a dummy");
		if (a.type().hash_code() == dummy_str.type().hash_code())
		{
			std::string name = std::string(std::any_cast<const char*>(a));

			if (name.at(0) == '"' && name.at(name.length() - 1) == '"')
			{
				return true;
			}
		}

		return false;
	}


	bool _isOpCode(std::any& a)
	{
		std::any dummy_str("Im a dummy");
		if (a.type().hash_code() == dummy_str.type().hash_code())
		{
			if (_isString(a) == false)
			{
				std::string potential_opcode = std::string(  std::any_cast<const char*>(a)  );
				bool is_opcode = false;

				// Define set of opcodes we have, everything else is NOT a opcode.
				/*
				* Comparison op.
				*/
				if (COMPARE_STRINGS(potential_opcode, "<") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, ">") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "==") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, ">=") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "<=") == 0)
				{
					is_opcode = true;
				}
				/*
				* Math op.
				*/
				else if (COMPARE_STRINGS(potential_opcode, "+") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "-") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "*") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "/") == 0)
				{
					is_opcode = true;
				}
				/*
				* Variables op.
				*/
				else if (COMPARE_STRINGS(potential_opcode, "set") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "var") == 0)
				{
					is_opcode = true;
				}
				/*
				* Flow control
				*/
				else if (COMPARE_STRINGS(potential_opcode, "begin") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "while") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "if") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "else") == 0)
				{
					is_opcode = true;
				}
				else if (COMPARE_STRINGS(potential_opcode, "def") == 0)
				{
					is_opcode = true;
				}


				// ...

				return is_opcode;
			}
		}

		return false;
	}

	bool _isVariable(std::any& a)
	{
		using namespace std;

		std::any dummy_str("Im a dummy");
		if (a.type().hash_code() == dummy_str.type().hash_code())
		{
			if (!_isString(a) && !_isOpCode(a))
			{
				// Check whether it is a valid variable name.
				if (!_isValidVariableName(a))
				{
					cout << color(colors::RED);
					cout << "Invalid Variable Name: \""<< std::string(std::any_cast<const char*>(a)) << "\"" << white << endl;
					throw std::runtime_error("Invalid Variable Name!");
				}

				return true;
			}
		}

		return false;
	}

	bool _isValidVariableName(std::any& a)
	{
		std::string name = std::string(std::any_cast<const char*>(a));

		if (std::regex_match(name, std::regex("[a-zA-Z_]+[0-9_]*[a-zA-Z_]+")) ||
			std::regex_match(name, std::regex("[a-zA-Z_]+")))
		{
			return true;
		}

		return false;
	}

	bool _isExpression(std::any& a)
	{
		/*
		* We evaluate whether "a" is an expression like this in order to
		* reach the end of recursion.
		*/
		Exp e;
		std::any dummy_exp(e);
		return a.type().hash_code() == dummy_exp.type().hash_code();
	}
};


#endif