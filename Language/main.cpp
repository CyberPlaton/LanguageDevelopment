#include "Application.h"

int main()
{

	Application* app = Application::get();
	if (app->startUp("IDE", 920, 720, false))
	{
		return app->run();
	}
}