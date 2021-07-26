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


#pragma comment(lib, "antlr4-runtime.lib")
#include "ANTLR/antlr4-runtime/antlr4-runtime.h"
//#include "ANTLR/generated/Python3Lexer.h"
//#include "ANTLR/generated/Python3Parser.h"


// Include From Generated Files, thus is updated every time new is created.
#include "EvaGrammarLexer.h"
#include "EvaGrammarParser.h"


#include <vector>
#include <any>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

struct AppConsole;


std::string exec_command(const char* cmd);

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

	char buffer[2024 * 16];

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
    static AppConsole* g_Console;

	std::string title;
	int width = 0;
	int height = 0;
	GLFWwindow* window = nullptr;


	char source_input[2024 * 16];
	char file_creation_buf[2024];
	const char *standard_file_path = "source/";
	std::string recently_used_files_path = "recently_used_files.json";
	std::string currently_worked_file;
	int file_count = 0;

	std::map<std::string, SourceBuffer*> worked_source_files;


	float source_font_scale = 1.0f;
	std::map<std::string, ImFont*> fonts;
	std::string current_font_selected;

private:

	bool _initImGui();
	bool _initStyles();
	bool _initFonts();

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

    void _sendFileToCheck(const std::string file, bool app_console_output = false);
};











struct AppConsole
{
    enum Color
    {
        RED,
        GREEN,
        YELLOW,
        MAGENTA,
        BLUE
    };

    char                  InputBuf[256];
    ImVector<char*>       Items;
    ImVector<const char*> Commands;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter       Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;

    AppConsole()
    {
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;
        AutoScroll = true;
        ScrollToBottom = false;
    }
    ~AppConsole()
    {
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            free(History[i]);
    }

    // Portable helpers
    static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
    static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
    static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
    static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }


    static ImVec4 getColorVec(Color col)
    {
        switch (col)
        {
        case Color::RED:
            return ImVec4(.8f, .0f, .0f, 1.0f);
            break;
        case Color::GREEN:
            return ImVec4(.0f, .8f, .0f, 1.0f);
            break;
        case Color::MAGENTA:
            return ImVec4(.8f, .0f, .8f, 1.0f);
            break;
        case Color::BLUE:
            return ImVec4(.0f, .0f, .8f, 1.0f);
            break;
        case Color::YELLOW:
            return ImVec4(.8f, .8f, .0f, 1.0f);
            break;
        default:
            return ImVec4(.0f, .0f, .0f, 1.0f);
        }
    }

    void    ClearLog()
    {
        for (int i = 0; i < Items.Size; i++)
            free(Items[i]);
        Items.clear();
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf) - 1] = 0;
        va_end(args);
        Items.push_back(Strdup(buf));
    }

    void    Draw(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(1, 1), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
        // So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Close Console"))
                *p_open = false;
            ImGui::EndPopup();
        }


        if (ImGui::SmallButton("Clear")) { ClearLog(); }
        ImGui::SameLine();
        bool copy_to_clipboard = ImGui::SmallButton("Copy");


        ImGui::Separator();


        // Options menu
        if (ImGui::BeginPopup("Options"))
        {
            ImGui::Checkbox("Auto-scroll", &AutoScroll);
            ImGui::EndPopup();
        }

        // Options, Filter
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");

        ImGui::Separator();

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) ClearLog();
            ImGui::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets.
        // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
        // to only process visible items. The clipper will automatically measure the height of your first item and then
        // "seek" to display only items in the visible area.
        // To use the clipper we can replace your standard loop:
        //      for (int i = 0; i < Items.Size; i++)
        //   With:
        //      ImGuiListClipper clipper;
        //      clipper.Begin(Items.Size);
        //      while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // - That your items are evenly spaced (same height)
        // - That you have cheap random access to your elements (you can access them given their index,
        //   without processing all the ones before)
        // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
        // We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
        // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
        // to improve this example code!
        // If your items are of variable height:
        // - Split them into same height items would be simpler and facilitate random-seeking into your list.
        // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        std::string item_string;
        for (int i = 0; i < Items.Size; i++)
        {
            const char* item = Items[i];
            if (!Filter.PassFilter(item))
                continue;

            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.)
            ImVec4 color;
            bool has_color = false;

            if(strstr(item, "#R#"))
            {
                color = getColorVec(Color::RED); has_color = true;
                item_string = getItemWithoutColorDefinition(std::string(item));
                item = item_string.c_str();
            }
            else if (strstr(item, "#G#"))
            {
                color = getColorVec(Color::GREEN); has_color = true;
                item_string = getItemWithoutColorDefinition(std::string(item));
                item = item_string.c_str();
            }
            else if (strstr(item, "#B#"))
            {
                color = getColorVec(Color::BLUE); has_color = true;
                item_string = getItemWithoutColorDefinition(std::string(item));
                item = item_string.c_str();
            }
            else if (strstr(item, "#Y#"))
            {
                color = getColorVec(Color::YELLOW); has_color = true;
                item_string = getItemWithoutColorDefinition(std::string(item));
                item = item_string.c_str();
            }
            else if (strstr(item, "#M#"))
            {
                color = getColorVec(Color::MAGENTA); has_color = true;
                item_string = getItemWithoutColorDefinition(std::string(item));
                item = item_string.c_str();
            }



            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            
            ImGui::TextUnformatted(item);
            
            if (has_color)
                ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();

        if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        ScrollToBottom = false;

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        ImGui::End();
    }

    // Function does not need to know about color definitions, only the format,
    // which is encoded and #X# where X is some Character.
    std::string getItemWithoutColorDefinition(const std::string& item)
    {
        std::string item_string = item; // Create a working copy.
        std::string item_without_color_def;

        int i = 0;
        while (item_string[i] != '\0') // Iterate through string
        {
            // And ignore the color definition: e.g. #R# for red.
            if (item_string[i] == '#' || (i > 0 && item_string[i - 1] == '#'))
            {

                i++;
                continue;
            }
            else
            {
                // But store the other charachters.
                item_without_color_def += item_string[i];
                i++;
            }

        }

        return item_without_color_def;
    }



    // Not Implemented
    void    ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back.
        // This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = History.Size - 1; i >= 0; i--)
            if (Stricmp(History[i], command_line) == 0)
            {
                free(History[i]);
                History.erase(History.begin() + i);
                break;
            }
        History.push_back(Strdup(command_line));

        // Process command
        if (Stricmp(command_line, "CLEAR") == 0)
        {
            ClearLog();
        }
        else if (Stricmp(command_line, "HELP") == 0)
        {
            AddLog("Commands:");
            for (int i = 0; i < Commands.Size; i++)
                AddLog("- %s", Commands[i]);
        }
        else if (Stricmp(command_line, "HISTORY") == 0)
        {
            int first = History.Size - 10;
            for (int i = first > 0 ? first : 0; i < History.Size; i++)
                AddLog("%3d: %s\n", i, History[i]);
        }
        else
        {
            AddLog("Unknown command: '%s'\n", command_line);
        }

        // On command input, we scroll to bottom even if AutoScroll==false
        ScrollToBottom = true;
    }

    // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data)
    {
        AppConsole* console = (AppConsole*)data->UserData;
        return console->TextEditCallback(data);
    }

    int     TextEditCallback(ImGuiInputTextCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for (int i = 0; i < Commands.Size; i++)
                if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(Commands[i]);

            if (candidates.Size == 0)
            {
                // No match
                AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if (candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0]);
                data->InsertChars(data->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can..
                // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                AddLog("Possible matches:\n");
                for (int i = 0; i < candidates.Size; i++)
                    AddLog("- %s\n", candidates[i]);
            }

            break;
        }
        case ImGuiInputTextFlags_CallbackHistory:
        {
            // Example of HISTORY
            const int prev_history_pos = HistoryPos;
            if (data->EventKey == ImGuiKey_UpArrow)
            {
                if (HistoryPos == -1)
                    HistoryPos = History.Size - 1;
                else if (HistoryPos > 0)
                    HistoryPos--;
            }
            else if (data->EventKey == ImGuiKey_DownArrow)
            {
                if (HistoryPos != -1)
                    if (++HistoryPos >= History.Size)
                        HistoryPos = -1;
            }

            // A better implementation would preserve the data on the current input line along with cursor position.
            if (prev_history_pos != HistoryPos)
            {
                const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
        }
        }
        return 0;
    }
};