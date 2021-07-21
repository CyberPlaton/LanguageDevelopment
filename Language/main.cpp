
#include "Application.h"

#include <vector>
#include <any>
#include <iostream>



int main()
{
	Application* app = Application::get();
	if (app->startUp("IDE", 1920, 1080))
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