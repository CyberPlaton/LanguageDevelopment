#include"Any.h"

void Any::reprSelf(unsigned offset)
{
	using namespace std;

	std::any dummy_null(nullptr);

	for (int i = 0; i < offset; i++) cout << "\t";

	switch (m_Type)
	{
	case Type::TYPE_BOOL:

		cout << color(colors::YELLOW);
		cout << "Value: ";

		if (std::any_cast<bool>(m_Value) == true)
		{
			cout << color(colors::MAGENTA);
			cout << "\"true\" ";
		}
		else
		{
			cout << color(colors::MAGENTA);
			cout << "\"false\" ";
		}

		cout << color(colors::YELLOW);
		cout << "Type: ";

		cout << color(colors::MAGENTA);
		cout << "\"BOOL\"" << white << endl;

		break;
	case Type::TYPE_NUMBER:

		cout << color(colors::YELLOW);
		cout << "Value: ";

		cout << color(colors::MAGENTA);
		cout << "\" " << std::any_cast<double>(m_Value) << " \" ";

		cout << color(colors::YELLOW);
		cout << "Type: ";

		cout << color(colors::MAGENTA);
		cout << "\"NUMBER\"" << white << endl;

		break;
	case Type::TYPE_STRING:

		cout << color(colors::YELLOW);
		cout << "Value: ";

		cout << color(colors::MAGENTA);
		cout << "\" " << std::any_cast<const char*>(m_Value) << " \" ";

		cout << color(colors::YELLOW);
		cout << "Type: ";

		cout << color(colors::MAGENTA);
		cout << "\"STRING\"" << white << endl;

		break;
	case Type::TYPE_EXP:
		std::any_cast<Exp>(m_Value).representSelf(offset + 1);
		break;


	case Type::TYPE_OPCODE:

		cout << color(colors::YELLOW);
		cout << "Value: ";

		cout << color(colors::MAGENTA);
		cout << "\" " << std::any_cast<const char*>(m_Value) << " \" ";

		cout << color(colors::YELLOW);
		cout << "Type: ";

		cout << color(colors::MAGENTA);
		cout << "\"OPCODE\"" << white << endl;

		break;


	case Type::TYPE_VAR:

		cout << color(colors::YELLOW);
		cout << "Value: ";

		try
		{
			// Check whether variable is "null".
			if (dummy_null.type().hash_code() == m_Value.type().hash_code())
			{
				cout << color(colors::MAGENTA);
				cout << "\" " << "null" << " \" ";
			}
			// Check whether the datatype is a function declaration.
			else if (std::string(m_Value.type().name()).find("(__cdecl*)") != std::string::npos)
			{
				cout << color(colors::MAGENTA);
				cout << "\" " << "Function Declaration " << "\" ";
				cout << color(colors::DARKMAGENTA);
				cout << "	Function Type: " << m_Value.type().name() << white << endl;
			}
			// Else it should be a standard variable name.
			else
			{
				cout << color(colors::MAGENTA);
				cout << "\" " << std::any_cast<const char*>(m_Value) << " \" ";
			}
		}
		catch (...) // In any case, catch something unexpected and show what we did not consider.
		{
			cout << endl;
			cout << color(colors::RED);
			cout << "Unable to Represent Self! Datatype: "<< m_Value.type().name() << white << endl;
		}


		cout << color(colors::YELLOW);
		cout << "Type: ";

		cout << color(colors::MAGENTA);
		cout << "\"VAR\"" << white << endl;
		break;


	default:
		break;
	}
}
