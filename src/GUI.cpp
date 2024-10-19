#include "GUI.h"
GUI::GUI() {}

GUI::GUI(Renderer& renderer, World& world, InputHandler& inputHandler) : m_renderer(&renderer) , m_world(&world) , m_inputHandler(&inputHandler)
{
	show_demo_window = true;
	show_another_window = false;
	clear_color = ImVec4(0.0f, 1.0f, 0.60f, 1.00f);
    clear_scr_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void GUI::init()
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_renderer->getwindow(), true);
	io = &ImGui::GetIO();
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui::StyleColorsDark();
}

void GUI::newFrame()
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

void GUI::drawFrame()
{
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Settings");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("Fly-like Cam:\nWASD for movement\nSpace/LShift for Up/Down Fly");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        bool mouseState = m_inputHandler->getMouseState();
        if (ImGui::Checkbox("Process Mouse Movement", &mouseState)) 
        {
            m_inputHandler->setMouseState(mouseState); // Set the new state
        }

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

        ImGui::ColorEdit3("Quad Color", (float*)&clear_color); // Edit 3 floats representing a color
        //if (ImGui::IsItemActive()) 
        {
            glm::vec3 glmColor = glm::vec3(clear_color.x, clear_color.y, clear_color.z);
            m_world->update(glmColor); // Notify World
        }

        ImGui::ColorEdit3("Screen Color", (float*)&clear_scr_color); 
        //if (ImGui::IsItemActive())
        {
            //glm::vec3 glmColor = glm::vec3(clear_scr_color.x, clear_scr_color.y, clear_scr_color.z);
            m_renderer->clear(clear_scr_color); // Notify World
        }

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}

void GUI::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
