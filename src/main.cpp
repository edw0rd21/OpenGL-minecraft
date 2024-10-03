#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Shader.h"
#include "camera.h"
#include "management.h"

int main()
{
    GLFWwindow* window = Init();

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("shader/shader.vert", "shader/shader.frag");

    float vertices[] = {
        //front
        -0.5f, -0.5f, -0.5f,   0.5f, 0.0f,           //bottom left
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,           //bottom right
         0.5f,  0.5f, -0.5f,   1.0f, 0.5f,           //top right
         0.5f,  0.5f, -0.5f,   1.0f, 0.5f,           //top right
        -0.5f,  0.5f, -0.5f,   0.5f, 0.5f,           //top left
        -0.5f, -0.5f, -0.5f,   0.5f, 0.0f,           //bottom right

        //back
        -0.5f, -0.5f,  0.5f,   0.5f, 0.0f,           //bottom left
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,           //bottom right
         0.5f,  0.5f,  0.5f,   1.0f, 0.5f,           //top right
         0.5f,  0.5f,  0.5f,   1.0f, 0.5f,           //top right
        -0.5f,  0.5f,  0.5f,   0.5f, 0.5f,           //top left
        -0.5f, -0.5f,  0.5f,   0.5f, 0.0f,           //bottom right

        //left
        -0.5f,  0.5f,  0.5f,   0.5f, 0.5f,           //top left (front)
        -0.5f,  0.5f, -0.5f,   1.0f, 0.5f,           //top left (back)
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,           //bottom left (back)
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,           //bottom left (back)
        -0.5f, -0.5f,  0.5f,   0.5f, 0.0f,           //bottom left (front)
        -0.5f,  0.5f,  0.5f,   0.5f, 0.5f,           //top left (front)

        //right
         0.5f,  0.5f,  0.5f,   0.5f, 0.5f,           //top right (front)
         0.5f,  0.5f, -0.5f,   1.0f, 0.5f,           //top right (back)
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,           //top right (back)
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,           //top right (back)
         0.5f, -0.5f,  0.5f,   0.5f, 0.0f,           //top right (front)
         0.5f,  0.5f,  0.5f,   0.5f, 0.5f,           //top right (front)

         //bottom
        -0.5f, -0.5f, -0.5f,   0.0f, 0.5f,
         0.5f, -0.5f, -0.5f,   0.5f, 0.5f,
         0.5f, -0.5f,  0.5f,   0.5f, 0.0f,
         0.5f, -0.5f,  0.5f,   0.5f, 0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.5f,

        //top
        -0.5f,  0.5f, -0.5f,   0.5f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.5f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.5f,
        -0.5f,  0.5f,  0.5f,   0.5f, 0.5f,
        -0.5f,  0.5f, -0.5f,   0.5f, 1.0f
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
      
    //ourShader.use(); 
    //ourShader.setInt("bull", 0);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
            
        // input
        processInput(window);

        // render
        glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, loadTexture());

        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.f);
        ourShader.setMat4("projection", projection);
            
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

      /*  glBindVertexArray(VAO);

        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);*/

        const int CHUNK_SIZE = 50; 
        std::vector<glm::vec3> cubePositions;

        for (int x = 0; x < CHUNK_SIZE; ++x) {
            for (int y = 0; y < 2; ++y) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    // Calculate the position for each cube
                    glm::vec3 position = glm::vec3(x, y, z);
                    cubePositions.push_back(position);
                }
            }
        }

        for (const auto& position : cubePositions)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36); 
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // deallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
