#include "Application.h"


static bool show_demo_window = false;
static bool source_code_open = false;
static bool console_window = false;
static bool new_file_name_specified = false;
static bool file_creation = false;


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
	show_demo_window = (show_demo_window == true) ? false : true;
	source_code_open = (source_code_open == true) ? false : true;
	console_window = (console_window == true) ? false : true;
}

void Application::onImGui()
{
	using namespace std;

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);


	


	// Console
	if (console_window)
	{
		
	}


	//
	if (file_creation)
	{
		_newFileDialog();
	}


	// Main Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
				file_creation = true;
			}

			if (ImGui::MenuItem("Open", "Ctrl+O")) {}
			if (ImGui::BeginMenu("Open Recent"))
			{
				_showRecentlyUsedFiles();
				if (ImGui::BeginMenu("More.."))
				{
					ImGui::MenuItem("Hello");
					ImGui::MenuItem("Sailor");
					if (ImGui::BeginMenu("Recurse.."))
					{
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}


	// Menu Bar End




	if (source_code_open)
	{		
		if (!currently_worked_file.empty())
		{

			if (ImGui::Begin(currently_worked_file.c_str(), &source_code_open))
			{
				ImGui::InputTextMultiline("source", this->source_input, IM_ARRAYSIZE(this->source_input), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput);

				if (ImGui::Button("Save", ImVec2(100.0f, 20.0f)))
				{
					// Export source to file.
					std::ofstream outfile(currently_worked_file, std::ios::binary);
					outfile << this->source_input;
					outfile.close();


					cout << this->source_input << endl;
				}

				if (ImGui::Button("Eval", ImVec2(100.0f, 20.0f)))
				{
					cout << "Not Implemented" << endl;
				}
			}

			ImGui::End();
		}
		
	}
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


	using namespace nlohmann;
	
	// Try import recently used files.
	std::ifstream file(recently_used_files_path, std::ios::in);
	if (!file.is_open())
	{
		// None exist, create one.
		json out;
		std::ofstream jsonout(recently_used_files_path);
		jsonout << out;
		jsonout.close();
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



void Application::_newFileDialog()
{
	using namespace std;
	using namespace nlohmann;

	ImGui::SetNextWindowSize(ImVec2(350.0f, 80.0f));
	ImGui::SetNextWindowPos(ImVec2(1.0f, 1.0f));

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize;
	flags |= ImGuiWindowFlags_NoMove;
	flags |= ImGuiWindowFlags_AlwaysAutoResize;

	if(ImGui::Begin("File Creation", &file_creation, flags))
	{
		ImGui::InputText("Enter file name...", file_creation_buf, IM_ARRAYSIZE(file_creation_buf));
		if (ImGui::Button("Ok", ImVec2(20.0f, 20.0f)))
		{
			file_creation = false;

			std::string path = std::string(standard_file_path);
			std::string name = std::string(file_creation_buf);
			
			std::ofstream outfile(path + name, std::ios::binary);
			
			outfile.close();

			memset(&file_creation_buf, 0, sizeof(file_creation_buf));
			file_count++;


			cout << "File created: " << path + name << endl;


			// Store file in recently used.
			std::ifstream i(recently_used_files_path);
			json in;
			i >> in;			
			in.emplace(std::to_string(file_count), path + name);

			cout << in.dump(4) << endl;
			std::ofstream jsonout(recently_used_files_path);
			jsonout << in;
			jsonout.close();
		}
		ImGui::End();
	}
}



void Application::_showRecentlyUsedFiles()
{
	using namespace std;
	using namespace nlohmann;

	std::ifstream i(recently_used_files_path);
	json in;
	i >> in;


	for (auto& item : in)
	{
		if (ImGui::MenuItem(item.get<std::string>().c_str()))
		{
			cout << item.get<std::string>() << "  selected " << endl;

			std::string path = item.get<std::string>();

			std::ifstream code(path, std::ios::in);
			std::string text;
			std::string line;

			if (!code.is_open())
			{
				cout << "Could not open file: " << path << endl;
			}

			while (std::getline(code, line))
			{
				text += line + "\n";
			}

			// Clear current source buffer
			memset(&source_input, 0, sizeof(source_input));

			for (int i = 0; i < text.size(); i++)
			{
				source_input[i] = text[i];
			}


			currently_worked_file = path;


			code.close();
		}
	}
}