#include "GUI.h"
GUI::GUI() {}

GUI::GUI(Renderer& renderer, World& world, InputHandler& inputHandler) : m_renderer(&renderer) , m_world(&world) , m_inputHandler(&inputHandler)
{
	show_demo_window = true;
    renderMode_window = false;
	clear_color = ImVec4(voxel.color.x, voxel.color.y, voxel.color.z, 1.00f);
    
    clear_scr_color = ImVec4(m_renderer->getScrColor().x, m_renderer->getScrColor().y, m_renderer->getScrColor().z, 1.0f);
    mouseState = m_inputHandler->mouseState;
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
        static int i = 1;
        static int j = 1;
        static int counter = 0;

        ImGui::Begin("Settings");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("Fly-like Cam:\nWASD for movement\nSpace/LShift for Up/Down Fly");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

        if (ImGui::Checkbox("Process Mouse Movement", &mouseState))
        {
            m_inputHandler->setMouseState(mouseState); // Set the new state
        }

        bool newState = m_world->rotationState;
        if (ImGui::Checkbox("Rotate", &m_world->rotationState))
        {
            m_world->rotationState; // Set the new state
        }

        if (ImGui::InputInt("Chunk Size", &i, 1, 1000))           
        {
            m_world->setChunkNum(i);
        }   
        if (ImGui::InputInt("Voxels per Chunk", &j, 1, 100))            
        {
            m_world->setChunkSize(j);
        }

        ImGui::ColorEdit3("Voxel Color", (float*)&clear_color); // Edit 3 floats representing a color
        if (ImGui::IsItemActive())
        {
            glm::vec3 glmColor = glm::vec3(clear_color.x, clear_color.y, clear_color.z);
            m_world->update(glmColor); // Notify World
        }

        ImGui::ColorEdit3("Screen Color", (float*)&clear_scr_color); 
        if (ImGui::IsItemActive())
        {
            glmScrColor = glm::vec3(clear_scr_color.x, clear_scr_color.y, clear_scr_color.z);
            m_renderer->update(glmScrColor); // Notify World
        }

        if (ImGui::Button("Render Mode"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            renderMode_window = true;
            counter++;
        }

        if (renderMode_window)
        {
            ImGui::Begin("Another Window", &renderMode_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Toggle between Pyramid and Cube Model");

            bool renderState = m_renderer->renderState;
            ImGui::Checkbox("Change Object", &renderState);

            if (renderState == 0)            
                ImGui::Text("Currently rendering: Cube");           
            else
                ImGui::Text("Currently rendering: Pyramid");

            m_renderer->updateMode(renderState);
          
            if (ImGui::Button("Close"))
                renderMode_window = false;
            ImGui::End();
        }

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
        ImGui::End();
    }
}

void GUI::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
