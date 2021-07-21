#include "Application.h"

bool Application::show_demo_window = false;
Application* Application::g_Application = nullptr;


void GLKeyInputCallback(GLFWwindow* wnd, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(wnd, GLFW_TRUE);
	}

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
	{
		Application::get()->toggleImGuiDemo();
	}
}


void GLMouseMoveCallback(GLFWwindow* wnd, double posX, double posY)
{

}


void GLMouseScrollCallback(GLFWwindow* wnd, double deltaX, double deltaY)
{

}


int Application::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		onImGui();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Display it.
		ImGui::EndFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}


void Application::toggleImGuiDemo()
{
	this->show_demo_window = (this->show_demo_window == true) ? false : true;
}

void Application::onImGui()
{
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
}



bool Application::startUp(const std::string& title, int width, int height, bool fullscreen)
{
	this->title = title;
	this->width = width;
	this->height = height;


	if (!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif



	if (!fullscreen)
	{
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	}
	else
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
		this->width = vidMode->width;
		this->height = vidMode->height;

		window = glfwCreateWindow(vidMode->width, vidMode->height, title.c_str(), monitor, NULL);

		glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	}


	if (!window)
	{
		return false;
	}


	glfwSetKeyCallback(window, GLKeyInputCallback);


	glfwMakeContextCurrent(window);
	glfwSetCursorPos(window, width / 2.0, height / 2.0);


	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glViewport(0, 0, width, height);
	glfwSwapInterval(1);


	glewExperimental = GL_TRUE;
	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(result) << std::endl;
		glfwTerminate();
		return false;
	}

	if (!_initImGui())
	{
		return false;
	}


	return true;
}




bool Application::_initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.DisplaySize = ImVec2{ (float)width, (float)height };



	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();



	if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
	{
		return false;
	}

	if (!ImGui_ImplOpenGL3_Init("#version 450 core"))
	{
		return false;
	}


	ImGui::CaptureMouseFromApp(true);
	ImGui::CaptureKeyboardFromApp(true);


}