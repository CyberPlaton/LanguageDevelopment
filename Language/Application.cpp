#include "Application.h"

std::string exec_command(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();

		std::cout << buffer.data() << std::endl;
	}
	return result;
}


static bool show_demo_window = false;
static bool source_code_open = false;
static bool console_window = false;
static bool new_file_name_specified = false;
static bool file_creation = false;
static int editor_color_scheme = 0;
static const int editor_color_scheme_count = 4;
static bool custom_font_selected = false;


Application* Application::g_Application = nullptr;
AppConsole* Application::g_Console = nullptr;




void GLKeyInputCallback(GLFWwindow* wnd, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(wnd, GLFW_TRUE);
	}

	
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS && source_code_open == false)
	{
		Application::get()->toggleImGuiDemo();
		Application::get()->toggleColorScheme(++editor_color_scheme % editor_color_scheme_count);
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
}

void Application::onImGui()
{
	using namespace std;

	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}




	// Console
	if (console_window)
	{
		Application::get()->g_Console->Draw("Console", &console_window);
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


			if (ImGui::BeginMenu("Open Recent"))
			{
				_showRecentlyUsedFiles();

				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Settings"))
		{
			if (ImGui::BeginMenu("FontScale"))
			{
				ImGui::SliderFloat("FontScale", &source_font_scale, 1.0f, 2.0f, "%.1f", 1.0f);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Fonts"))
			{
				for (auto& font : fonts)
				{
					if (ImGui::MenuItem(font.first.c_str()))
					{
						current_font_selected = font.first;
						custom_font_selected = true;
					}
				}

				ImGui::EndMenu();
			}


			ImGui::EndMenu();
		}



		if (ImGui::BeginMenu("Debug"))
		{
			if (ImGui::MenuItem("Toggle Console"))
			{
				console_window = (console_window == true) ? false : true;
			}

			ImGui::EndMenu();
		}


		ImGui::EndMainMenuBar();
	}


	// Menu Bar End



	// Worked files
	bool any_source_open = false;
	for (auto& file : worked_source_files)
	{
		if (file.second->currently_open)
		{
			any_source_open = true;

			//ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
			//ImGui::SetNextWindowSize(ImVec2(500.0f, 500.0f));
			if (ImGui::Begin(file.first.c_str(), &file.second->currently_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
			{
				// Set Custom Font for source input.
				if (custom_font_selected)
				{
					ImGui::PushFont(fonts.at(current_font_selected));
				}


				// Set custom scale only for textinput line.
				ImGui::SetWindowFontScale(source_font_scale);
				ImGui::InputTextMultiline("source", file.second->buffer, IM_ARRAYSIZE(file.second->buffer), ImVec2(source_font_scale * width / 2.0f, height / 2.0f), ImGuiInputTextFlags_AllowTabInput);
				ImGui::SetWindowFontScale(1.0f);



				if (custom_font_selected)
				{
					ImGui::PopFont();
				}


				if (ImGui::Button("Save", ImVec2(100.0f, 20.0f)))
				{
					// Export source to file.
					std::ofstream outfile(file.first, std::ios::binary);
					outfile << file.second->buffer;
					outfile.close();


					cout << file.second->buffer << endl;
					file.second->saved = true;
					file.second->prev_size = file.second->size();
				}

				ImGui::SameLine();
				if (ImGui::Button("Eval", ImVec2(100.0f, 20.0f)))
				{
					// Send file to evaluation.


					// Check whether the file is a source file or a grammar.
					if (file.first.find(".g4") != std::string::npos)
					{
						// Grammar.
						cout << "Checking Grammar File (if no error message, then everything OK!)" << endl;
						std::string cmd = "java -jar source/antlr-4.7-complete.jar -Dlanguage=Cpp -o source/generated/ " + file.first;
						std::string result = exec_command(cmd.c_str());
					}
					else
					{
						// Source.
						cout << "Not Implemented" << endl;
					}
				}


				// Display Parsing option only for NON-GRAMMAR files.
				if(file.first.find(".g4") == std::string::npos)
				{
					ImGui::SameLine();
					if (ImGui::Button("Parse", ImVec2(100.0f, 20.0f)))
					{
						// Send current open file to check in parser and lexer,
						// and whether to give output to app console window.
						_sendFileToCheck(file.first, console_window);
					}
				}

				ImGui::End();
			}
		}

	}
	source_code_open = any_source_open;

	
}



void Application::_sendFileToCheck(const std::string file, bool app_console_output)
{
	using namespace std;

	string line;
	ifstream source(file.c_str());
	g_Console->AddLog(("#B# Parsing result for \"" + file + "\"").c_str());
	if (source.is_open())
	{
		antlr4::ANTLRInputStream input(source);
		EvaGrammarLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);

		std::string token_text_line;


		tokens.fill();
		for (auto token : tokens.getTokens())
		{
			size_t type = token->getType();
			std::string type_name = lexer.getVocabulary().getSymbolicName(type);


			token_text_line = "Type: " + type_name + " Value: " + token->getText();

			if (type_name.compare("NEWLINE") == 0)
			{

			}

			g_Console->AddLog(token_text_line.c_str());
		}


		EvaGrammarParser parser(&tokens);

		
		antlr4::tree::ParseTree* tree = parser.file_input();

		//cout << "Concrete Syntax Tree: " << endl;
		//cout << tree->toStringTree(&parser) << endl;

		token_text_line = tree->toStringTree(&parser, true);

		g_Console->AddLog("#M# Concrete Syntax Tree: ");
		g_Console->AddLog(token_text_line.c_str());

		source.close();
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


	glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
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
	using namespace std;
	
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
	else
	{
		// There exist one, so store count of files.
		json in;
		file >> in;
		file_count = in.size();

		// Then read the files and load into our source file buffers.
		for (auto& entry : in)
		{
			std::ifstream code(entry.get<std::string>(), std::ios::in);
			std::string text;
			std::string line;

			if (!code.is_open())
			{
				cout << "Could not open file: " << entry.get<std::string>() << endl;
			}

			SourceBuffer* buf = new SourceBuffer();
			buf->currently_open = false;

			while (std::getline(code, line))
			{
				text += line + "\n";
			}

			for (int i = 0; i < text.size(); i++)
			{
				buf->buffer[i] = text[i];
			}

			worked_source_files.emplace(std::make_pair(entry.get<std::string>(), buf));
		}
	}

	return true;
}




bool Application::_initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.DisplaySize = ImVec2{ (float)width, (float)height };


	ImGui::StyleColorsLight();



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

	g_Console = new AppConsole();

	return (_initStyles() && _initFonts());
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


			cout << file_count << ".) File created: " << path + name << endl;


			// Store file in recently used.
			std::ifstream i(recently_used_files_path);
			json in;
			i >> in;			
			in.emplace(std::to_string(file_count), path + name);

			cout << in.dump(4) << endl;
			std::ofstream jsonout(recently_used_files_path);
			jsonout << in;
			jsonout.close();


			// Update Worked Source Files.
			worked_source_files.emplace(std::make_pair(path + name, new SourceBuffer()));
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


			// Set current worked file and open it
			worked_source_files.at(path)->currently_open = true;

			//currently_worked_file = path;
			//source_code_open = true;


			code.close();
		}
	}
}


bool Application::_initStyles()
{
	cyberpunk_color_scheme[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.00f, 0.22f, 0.94f);
	cyberpunk_color_scheme[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.00f, 0.17f, 0.00f);
	cyberpunk_color_scheme[ImGuiCol_PopupBg] = ImVec4(0.02f, 0.00f, 0.17f, 0.94f);
	cyberpunk_color_scheme[ImGuiCol_Border] = ImVec4(0.16f, 0.00f, 0.32f, 0.50f);
	cyberpunk_color_scheme[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	cyberpunk_color_scheme[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.36f, 0.40f, 0.54f);
	cyberpunk_color_scheme[ImGuiCol_FrameBgHovered] = ImVec4(0.82f, 0.26f, 0.98f, 0.40f);
	cyberpunk_color_scheme[ImGuiCol_FrameBgActive] = ImVec4(0.89f, 0.26f, 0.98f, 0.67f);
	cyberpunk_color_scheme[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.00f, 0.26f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	cyberpunk_color_scheme[ImGuiCol_MenuBarBg] = ImVec4(0.07f, 0.00f, 0.25f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	cyberpunk_color_scheme[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_CheckMark] = ImVec4(0.38f, 0.78f, 1.00f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.70f, 0.88f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.82f, 0.98f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_Button] = ImVec4(0.29f, 0.26f, 0.98f, 0.40f);
	cyberpunk_color_scheme[ImGuiCol_ButtonHovered] = ImVec4(0.82f, 0.26f, 0.98f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.06f, 0.98f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	cyberpunk_color_scheme[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	cyberpunk_color_scheme[ImGuiCol_HeaderActive] = ImVec4(0.79f, 0.26f, 0.98f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	cyberpunk_color_scheme[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	cyberpunk_color_scheme[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	cyberpunk_color_scheme[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	cyberpunk_color_scheme[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	cyberpunk_color_scheme[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
	cyberpunk_color_scheme[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.30f, 0.98f, 0.80f);
	cyberpunk_color_scheme[ImGuiCol_TabActive] = ImVec4(0.67f, 0.20f, 0.68f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	cyberpunk_color_scheme[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	cyberpunk_color_scheme[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	cyberpunk_color_scheme[ImGuiCol_TextSelectedBg] = ImVec4(0.77f, 0.26f, 0.98f, 0.35f);
	cyberpunk_color_scheme[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	cyberpunk_color_scheme[ImGuiCol_NavHighlight] = ImVec4(0.77f, 0.26f, 0.98f, 1.00f);
	cyberpunk_color_scheme[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	cyberpunk_color_scheme[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	cyberpunk_color_scheme[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);


	return true;
}


void Application::toggleColorScheme(int n)
{
	ImGuiStyle& style = ImGui::GetStyle();

	switch (n)
	{
	case 0:

		// Change Background color.
		glClearColor(43.0f / 255.0f, 42.0f / 255.0f, 92.0f / 255.0f, clear_color[3]);

		style.Colors[ImGuiCol_Text] = cyberpunk_color_scheme[ImGuiCol_Text];
		style.Colors[ImGuiCol_TextDisabled] = cyberpunk_color_scheme[ImGuiCol_TextDisabled];
		style.Colors[ImGuiCol_WindowBg] = cyberpunk_color_scheme[ImGuiCol_WindowBg];
		style.Colors[ImGuiCol_ChildBg] = cyberpunk_color_scheme[ImGuiCol_ChildBg];
		style.Colors[ImGuiCol_PopupBg] = cyberpunk_color_scheme[ImGuiCol_PopupBg];
		style.Colors[ImGuiCol_Border] = cyberpunk_color_scheme[ImGuiCol_Border];
		style.Colors[ImGuiCol_BorderShadow] = cyberpunk_color_scheme[ImGuiCol_BorderShadow];
		style.Colors[ImGuiCol_FrameBg] = cyberpunk_color_scheme[ImGuiCol_FrameBg];
		style.Colors[ImGuiCol_FrameBgHovered] = cyberpunk_color_scheme[ImGuiCol_FrameBgHovered];
		style.Colors[ImGuiCol_FrameBgActive] = cyberpunk_color_scheme[ImGuiCol_FrameBgActive];
		style.Colors[ImGuiCol_TitleBg] = cyberpunk_color_scheme[ImGuiCol_TitleBg];
		style.Colors[ImGuiCol_TitleBgActive] = cyberpunk_color_scheme[ImGuiCol_TitleBgActive];
		style.Colors[ImGuiCol_TitleBgCollapsed] = cyberpunk_color_scheme[ImGuiCol_TitleBgCollapsed];
		style.Colors[ImGuiCol_MenuBarBg] = cyberpunk_color_scheme[ImGuiCol_MenuBarBg];
		style.Colors[ImGuiCol_ScrollbarBg] = cyberpunk_color_scheme[ImGuiCol_ScrollbarBg];
		style.Colors[ImGuiCol_ScrollbarGrab] = cyberpunk_color_scheme[ImGuiCol_ScrollbarGrab];
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = cyberpunk_color_scheme[ImGuiCol_ScrollbarGrabHovered];
		style.Colors[ImGuiCol_ScrollbarGrabActive] = cyberpunk_color_scheme[ImGuiCol_ScrollbarGrabActive];
		style.Colors[ImGuiCol_CheckMark] = cyberpunk_color_scheme[ImGuiCol_CheckMark];
		style.Colors[ImGuiCol_SliderGrab] = cyberpunk_color_scheme[ImGuiCol_SliderGrab];
		style.Colors[ImGuiCol_SliderGrabActive] = cyberpunk_color_scheme[ImGuiCol_SliderGrabActive];
		style.Colors[ImGuiCol_Button] = cyberpunk_color_scheme[ImGuiCol_Button];
		style.Colors[ImGuiCol_ButtonHovered] = cyberpunk_color_scheme[ImGuiCol_ButtonHovered];
		style.Colors[ImGuiCol_ButtonActive] = cyberpunk_color_scheme[ImGuiCol_ButtonActive];
		style.Colors[ImGuiCol_Header] = cyberpunk_color_scheme[ImGuiCol_Header];
		style.Colors[ImGuiCol_HeaderHovered] = cyberpunk_color_scheme[ImGuiCol_HeaderHovered];
		style.Colors[ImGuiCol_HeaderActive] = cyberpunk_color_scheme[ImGuiCol_HeaderActive];
		style.Colors[ImGuiCol_Separator] = cyberpunk_color_scheme[ImGuiCol_Separator];
		style.Colors[ImGuiCol_SeparatorHovered] = cyberpunk_color_scheme[ImGuiCol_SeparatorHovered];
		style.Colors[ImGuiCol_SeparatorActive] = cyberpunk_color_scheme[ImGuiCol_SeparatorActive];
		style.Colors[ImGuiCol_ResizeGrip] = cyberpunk_color_scheme[ImGuiCol_ResizeGrip];
		style.Colors[ImGuiCol_ResizeGripHovered] = cyberpunk_color_scheme[ImGuiCol_ResizeGripHovered];
		style.Colors[ImGuiCol_ResizeGripActive] = cyberpunk_color_scheme[ImGuiCol_ResizeGripActive];
		style.Colors[ImGuiCol_Tab] = cyberpunk_color_scheme[ImGuiCol_Tab];
		style.Colors[ImGuiCol_TabHovered] = cyberpunk_color_scheme[ImGuiCol_TabHovered];
		style.Colors[ImGuiCol_TabActive] = cyberpunk_color_scheme[ImGuiCol_TabActive];
		style.Colors[ImGuiCol_TabUnfocused] = cyberpunk_color_scheme[ImGuiCol_TabUnfocused];
		style.Colors[ImGuiCol_TabUnfocusedActive] = cyberpunk_color_scheme[ImGuiCol_TabUnfocusedActive];
		style.Colors[ImGuiCol_PlotLines] = cyberpunk_color_scheme[ImGuiCol_PlotLines];
		style.Colors[ImGuiCol_PlotLinesHovered] = cyberpunk_color_scheme[ImGuiCol_PlotLinesHovered];
		style.Colors[ImGuiCol_PlotHistogram] = cyberpunk_color_scheme[ImGuiCol_PlotHistogram];
		style.Colors[ImGuiCol_PlotHistogramHovered] = cyberpunk_color_scheme[ImGuiCol_PlotHistogramHovered];
		style.Colors[ImGuiCol_TableHeaderBg] = cyberpunk_color_scheme[ImGuiCol_TableHeaderBg];
		style.Colors[ImGuiCol_TableBorderStrong] = cyberpunk_color_scheme[ImGuiCol_TableBorderStrong];
		style.Colors[ImGuiCol_TableBorderLight] = cyberpunk_color_scheme[ImGuiCol_TableBorderLight];
		style.Colors[ImGuiCol_TableRowBg] = cyberpunk_color_scheme[ImGuiCol_TableRowBg];
		style.Colors[ImGuiCol_TableRowBgAlt] = cyberpunk_color_scheme[ImGuiCol_TableRowBgAlt];
		style.Colors[ImGuiCol_TextSelectedBg] = cyberpunk_color_scheme[ImGuiCol_TextSelectedBg];
		style.Colors[ImGuiCol_DragDropTarget] = cyberpunk_color_scheme[ImGuiCol_DragDropTarget];
		style.Colors[ImGuiCol_NavHighlight] = cyberpunk_color_scheme[ImGuiCol_NavHighlight];
		style.Colors[ImGuiCol_NavWindowingHighlight] = cyberpunk_color_scheme[ImGuiCol_NavWindowingHighlight];
		style.Colors[ImGuiCol_NavWindowingDimBg] = cyberpunk_color_scheme[ImGuiCol_NavWindowingDimBg];
		style.Colors[ImGuiCol_ModalWindowDimBg] = cyberpunk_color_scheme[ImGuiCol_ModalWindowDimBg];
		break;



	case 1:
		// Change Background color.
		glClearColor(0.2f, 0.2f, 0.2f, clear_color[3]);
		ImGui::StyleColorsDark();

		break;


	case 2:
		// Change Background color.
		glClearColor(250.0f / 255.0f, 250.0f / 255.0f, 250.0f / 255.0f, clear_color[3]);
		ImGui::StyleColorsLight();

		break;


	case 3:
		// Change Background color.
		glClearColor(0.2f, 0.2f, 0.2f, clear_color[3]);
		ImGui::StyleColorsClassic();

		break;

	}

}



bool Application::_initFonts()
{
	ImGuiIO& io = ImGui::GetIO();

	ImFont* f = io.Fonts->AddFontFromFileTTF("fonts/ProggyClean.ttf", 15.0f);
	fonts.emplace(std::make_pair("ProggyClean", f));

	f = io.Fonts->AddFontFromFileTTF("fonts/Roboto-Medium.ttf", 15.0f);
	fonts.emplace(std::make_pair("Roboto-Medium", f));

	f = io.Fonts->AddFontFromFileTTF("fonts/Cousine-Regular.ttf", 15.0f);
	fonts.emplace(std::make_pair("Cousine-Regular", f));

	f = io.Fonts->AddFontFromFileTTF("fonts/DroidSans.ttf", 15.0f);
	fonts.emplace(std::make_pair("DroidSans", f));

	f = io.Fonts->AddFontFromFileTTF("fonts/Karla-Regular.ttf", 15.0f);
	fonts.emplace(std::make_pair("Karla-Regular", f));

	return true;
}