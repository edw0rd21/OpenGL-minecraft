#include "GUI.h"

GUI::GUI() {}

GUI::GUI(Renderer& renderer, World& m_world, InputHandler& inputHandler, Camera& cam)
    : m_renderer(&renderer) , 
    m_world(&m_world) , 
    m_inputHandler(&inputHandler) ,
    m_camera(&cam)
{
	show_demo_window = false;
    renderMode_window = false;
    camSettings = false;
    clear_color = ImVec4(chunk.color.x, chunk.color.y, chunk.color.z, 1.0f);
    clear_scr_color = ImVec4(m_renderer->getScrColor().x, m_renderer->getScrColor().y, m_renderer->getScrColor().z, 1.0f);
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
	ImGui_ImplOpenGL3_Init("#version 330");

    if (glGetError() != GL_NO_ERROR) {
        std::cerr << "ImGui OpenGL init failed" << std::endl;
    }

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
        static int i = m_world->numChunks;
        static int j = 1;
        static int f = voxel.getvoxelDist();

        static float speed = SPEED;
        static float sens = SENSITIVITY;
        static float fov = ZOOM;

        static int counter = 0;

        ImGui::Begin("Settings");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("Fly-like Cam:\nWASD for movement\nSpace/LShift for Up/Down Fly");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

        bool mouseState = m_inputHandler->getMouseState();
        if (ImGui::Checkbox("Process Mouse Movement", &mouseState))
        {
            m_inputHandler->setMouseState(mouseState); // Set the new state
            //std::cout << "Mouse State:" << (mouseState ? "true" : "false") << std::endl;
        }

        bool newState = m_world->rotationState;
        if (ImGui::Checkbox("Rotate", &m_world->rotationState))
        {
            m_world->rotationState; // Set the new state
        }

        if (ImGui::InputInt("Chunk Number", &i, 1, 1000))           
        {
            m_world->setChunkNum(i);
        }   
        if (ImGui::InputInt("Chunk Size (voxels/chunk)", &j, 1, 100))            
        {
            chunk.setChunkSize(j);
            //m_world->setChunkSize(j);
        }

        if (ImGui::SliderInt("Voxel Distance", &f, 1, 5))
        {
            voxel.setVoxelDist(f);
        }

        ImGui::ColorEdit3("Voxel Color", (float*)&clear_color);
        if (ImGui::IsItemActive())
        {
            glm::vec3 glmColor = glm::vec3(clear_color.x, clear_color.y, clear_color.z);
            m_world->setVoxelColor(glmColor);
        }

        ImGui::ColorEdit3("Screen Color", (float*)&clear_scr_color); 
        if (ImGui::IsItemActive())
        {
            glmScrColor = glm::vec3(clear_scr_color.x, clear_scr_color.y, clear_scr_color.z);
            m_renderer->setScrClr(glmScrColor);
        }

        if (ImGui::Button("Render Mode"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            renderMode_window = true;
            counter++;
        }

        if (ImGui::Button("Camera Settings"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            camSettings = true;
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

        if (camSettings)
        {
            ImGui::Begin("Window", &camSettings);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Change Camera Settings");

            if (ImGui::SliderFloat("Speed", &speed, 10.0f, 200.0f))
            {
                m_camera -> updateCameraSettings(speed, sens, fov);
            }

            if (ImGui::SliderFloat("Sensitivity", &sens, 0.01f, 0.5f))
            {
                m_camera->updateCameraSettings(speed, sens, fov);
            }

            if (ImGui::SliderFloat("Zoom", &fov, 20.0f, 100.0f))
            {
                m_camera->updateCameraSettings(speed, sens, fov);
            }

            if (ImGui::Button("Close"))
                camSettings = false;

            ImGui::End();
        }

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
