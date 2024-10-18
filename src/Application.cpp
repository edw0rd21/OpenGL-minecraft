#include "Application.h"

Application::Application() : renderer() , aspectRatio(0) , inputHandler() , world() {}

Application::Application(int width, int height, const std::string& title)
	: camera(glm::vec3(0.0f, 2.0f, 4.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f), 
	  renderer(width, height, title, camera, inputHandler), 
	  inputHandler(camera, renderer, width, height),
	  world(camera, renderer)
{
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

Application::~Application() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run() 
{ 	
	renderer.init();

	const char* glsl_version = "#version 130";
	ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(renderer.getwindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	mainLoop(); 
}

void update()
{

}

void Application::handleInput(float deltaTime) 
{
	inputHandler.handleKeyboard(deltaTime);
}

void Application::mainLoop()
{	
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(renderer.getwindow()))
	{	

		inputHandler.handleKeyboard(world.deltaTime);

		renderer.clear();

		ImGuiIO& io = ImGui::GetIO();
		int display_w, display_h;
		glfwGetFramebufferSize(renderer.getwindow(), &display_w, &display_h);
		io.DisplaySize = ImVec2((float)display_w, (float)display_h);  // Set the display size
        
		world.render(aspectRatio);

        ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
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
        //ImGui render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(renderer.getwindow());
		glfwPollEvents();
	}
}