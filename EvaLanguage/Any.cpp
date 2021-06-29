#include"Any.h"

void Any::reprSelf(unsigned offset)
{
	using namespace std;

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

		cout << color(colors::MAGENTA);
		cout << "\" " << std::any_cast<const char*>(m_Value) << " \" ";

		cout << color(colors::YELLOW);
		cout << "Type: ";

		cout << color(colors::MAGENTA);
		cout << "\"VAR\"" << white << endl;
		break;

	default:
		break;
	}
}
