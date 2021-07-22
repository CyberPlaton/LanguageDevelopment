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


#include "common/include/nlohmann/json.hpp"


#include <string>
#include <iostream>
#include <fstream>


void GLKeyInputCallback(GLFWwindow* wnd, int key, int scancode, int action, int mode);
void GLMouseMoveCallback(GLFWwindow* wnd, double posX, double posY);
void GLMouseScrollCallback(GLFWwindow* wnd, double deltaX, double deltaY);


struct SourceBuffer
{
	SourceBuffer()
	{
		memset(&buffer, 0, sizeof(buffer));
	}


	int size()
	{
		int r = 0;
		for (int i = 0; i < sizeof(buffer); i++)
		{
			if (buffer[i] == 0) return r;

			r += sizeof(buffer[i]);
		}
	}

	char buffer[1024 * 16];

	bool currently_open = false;

	bool saved = false;

	int prev_size = 0;
};



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

	/*
	* Change color scheme of the editor.
	*/
	void toggleColorScheme(int n);

public:
	ImVec4 cyberpunk_color_scheme[53];
	float clear_color[4] = { 0.9f, 0.9f, 0.9f, 1.0f };

private:

	static Application* g_Application;

	std::string title;
	int width = 0;
	int height = 0;
	GLFWwindow* window = nullptr;


	char source_input[1024 * 16];
	char file_creation_buf[1024];
	const char *standard_file_path = "source/";
	std::string recently_used_files_path = "recently_used_files.json";
	std::string currently_worked_file;
	int file_count = 0;

	std::map<std::string, SourceBuffer*> worked_source_files;


private:

	bool _initImGui();
	bool _initStyles();

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


	void _newFileDialog();
	void _showRecentlyUsedFiles();
};