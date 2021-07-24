
#include "Application.h"

#include <vector>
#include <any>
#include <iostream>

#pragma comment(lib, "antlr4-runtime.lib")
#include "ANTLR/antlr4-runtime/antlr4-runtime.h"
#include "ANTLR/generated/Python3Lexer.h"
#include "ANTLR/generated/Python3Parser.h"




int main()
{
	// TESTING
	// Check why Release build is not working
	//
	//
	
	using namespace std;
	string line;
	ifstream source("source/python.py");
	if (source.is_open())
	{
		antlr4::ANTLRInputStream input(source);
		Python3Lexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);


		tokens.fill();
		for (auto token : tokens.getTokens())
		{
			size_t type = token->getType();
			std::string type_name = lexer.getVocabulary().getSymbolicName(type);


			//cout << token->getText() << "";
			cout << token->toString();
			cout << "	Type: " << type_name;
			cout << "	Value: " << token->getText() << endl;

			if (type_name.compare("NEWLINE") == 0)
			{
				cout << endl;
			}
		}


		Python3Parser parser(&tokens);

		antlr4::tree::ParseTree* tree = parser.file_input();

		cout << "Concrete Syntax Tree: " << endl;
		cout << tree->toStringTree(&parser) << endl;
		source.close();
	}

	return 0;
	



	Application* app = Application::get();
	if (app->startUp("IDE", 920, 720, false))
	{
		return app->run();
	}
}



class ASTNode;


class Token
{	
	friend class ASTNode;
public:
	enum Type
	{
		INVALID = -1,
		BLOCK,
		ASSIGN,
		RETURN,
		PRINT,
		IF,
		CALL,
		NEW,
		ADD,
		INT,
		SEMI_COLON,
		ID,
	};


public:




private:

	Type type = Type::INVALID;
};




class Scope
{

};





class ASTNode
{
public:
	ASTNode(Token& token, Scope* parent = nullptr){}


	Token::Type type()
	{
		return token->type;
	}



private:
	ASTNode* parent = nullptr;
	std::vector< ASTNode* > children;


	Scope* scope = nullptr;


	Token* token = nullptr;
};



class Interpreter
{
public:

	Token& exec(ASTNode& root)
	{
		switch (root.type())
		{
		case Token::Type::INT:
			break;
		case Token::Type::BLOCK:
			break;
		case Token::Type::RETURN:
			break;
		case Token::Type::SEMI_COLON:
			break;
		case Token::Type::ASSIGN:
			break;
		case Token::Type::ID:
			break;
		case Token::Type::CALL:
			break;
		case Token::Type::IF:
			break;
		case Token::Type::PRINT:
			break;

		default:
			break;
		}
	}
};