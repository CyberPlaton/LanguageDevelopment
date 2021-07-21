#pragma once

#include"common/include/GL/glew.h"
#pragma comment(lib, "glew32.lib")

#include"common/include/GLFW/glfw3.h"
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "common/include/imgui-master/imgui.h"
#include "common/include/imgui-master/examples/imgui_impl_glfw.h"
#include "common/include/imgui-master/examples/imgui_impl_opengl3.h"


#include <string>
#include <iostream>


void GLKeyInputCallback(GLFWwindow* wnd, int key, int scancode, int action, int mode);
void GLMouseMoveCallback(GLFWwindow* wnd, double posX, double posY);
void GLMouseScrollCallback(GLFWwindow* wnd, double deltaX, double deltaY);



class Application
{
public:

	/*
	* Singleton class access.
	*/
	static Application* get()
	{
		if (!Application::g_Application)
		{
			g_Application = new Application();
		}

		return g_Application;
	}

	/*
	* Singleton class destructor.
	*/
	static void del()
	{
		if (Application::g_Application)
		{
			delete g_Application;
		}
	}

	/*
	* Run the program main loop.
	*/
	int run();


	/*
	* Render imgui to screen.
	*/
	void onImGui();

	/*
	* Initialize the program with glew, glfw and imgui.
	*/
	bool startUp(const std::string& title, int width, int height, bool fullscreen = false);

	/*
	* Turn on or off the imgui demo window.
	*/
	void toggleImGuiDemo();


private:

	static Application* g_Application;
	static bool show_demo_window;


	std::string title;
	int width = 0;
	int height = 0;
	GLFWwindow* window = nullptr;

private:

	bool _initImGui();


	Application()
	{
	}

	~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
	}
};