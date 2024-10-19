#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <vector>

#include "vendor/imgui/imgui.h"
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

struct Quad
{
    Quad()
    {
        quadColor = glm::vec3(0.0f, 1.0f, 0.0f);

        t_size = t_vertices.size() * sizeof(float);

        q_size = q_vertices.size() * sizeof(float);
        q_indexCount = q_indices.size();

        c_size = c_vertices.size() * sizeof(float);
        c_indexCount = c_indices.size();
    }
    std::vector<float> t_vertices = { 
       -0.5f, -0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f, 
        0.0f,  0.5f, 0.0f 
    };

    std::vector<float> q_vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    std::vector<unsigned int> q_indices = { 
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    std::vector<float> c_vertices = {
         //back  
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f,  

        //front
        -0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 

        //left
        -0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f,  
        
        //right
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f, -0.5f,  

         //bottom
        -0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  

        //top
        -0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f   
    };

    std::vector<unsigned int> c_indices = {
        // Back
        0, 1, 2,
        2, 3, 0,

        // Front 
        4, 5, 6,
        6, 7, 4,

        // Left 
        8, 9, 10,
        10, 11, 8,

        // Right 
        12, 13, 14,
        14, 15, 12,

        // Bottom 
        16, 17, 18,
        18, 19, 16,

        // Top 
        20, 21, 22,
        22, 23, 20

    };

    std::vector<unsigned int>texCoords;

    GLsizeiptr t_size, q_size, c_size;
    std::size_t q_indexCount;
    std::size_t c_indexCount;

    glm::vec3 quadColor;

};

