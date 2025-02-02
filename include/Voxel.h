#pragma once
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

struct Voxel
{
public:

    static constexpr float t_vertices[] = {
       -0.5f, -0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f, 
        0.0f,  0.5f, 0.0f 
    };

    static constexpr float q_vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    static constexpr float q_indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    static constexpr float c_vertices[] = {
            // positions                // color multiplier
            //back  
            -0.5f, -0.5f, -0.5f,        0.8f,
             0.5f, -0.5f, -0.5f,        0.8f,
             0.5f,  0.5f, -0.5f,        0.8f,
            -0.5f,  0.5f, -0.5f,        0.8f,
            //front
            -0.5f, -0.5f,  0.5f,        0.8f,
             0.5f, -0.5f,  0.5f,        0.8f,
             0.5f,  0.5f,  0.5f,        0.8f,
            -0.5f,  0.5f,  0.5f,        0.8f,
            //left
            -0.5f,  0.5f, -0.5f,        0.65f,  
            -0.5f,  0.5f,  0.5f,        0.65f,
            -0.5f, -0.5f,  0.5f,        0.65f,
            -0.5f, -0.5f, -0.5f,        0.65f,
            //right
             0.5f,  0.5f, -0.5f,        0.65f,  
             0.5f,  0.5f,  0.5f,        0.65f,
             0.5f, -0.5f,  0.5f,        0.65f,
             0.5f, -0.5f, -0.5f,        0.65f,
             //bottom
             -0.5f, -0.5f, -0.5f,       1.0f,  
              0.5f, -0.5f, -0.5f,       1.0f,
              0.5f, -0.5f,  0.5f,       1.0f,
             -0.5f, -0.5f,  0.5f,       1.0f,
             //top
             -0.5f,  0.5f, -0.5f,       1.0f,  
              0.5f,  0.5f, -0.5f,       1.0f,
              0.5f,  0.5f,  0.5f,       1.0f,
             -0.5f,  0.5f,  0.5f,       1.0f
    };

    static constexpr unsigned int c_indices[] = {
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

    static constexpr float p_vertices[] = {
        // Base square
        -0.5f, -0.5f, -0.5f,  // 0 (Bottom-Left)
         0.5f, -0.5f, -0.5f,  // 1 (Bottom-Right)
         0.5f, -0.5f, 0.5f,   // 2 (Top-Right)
        -0.5f, -0.5f, 0.5f,   // 3 (Top-Left)

        // Apex vertex
         0.0f,  0.5f, 0.0f   // 4 (Apex)
    };

    static constexpr unsigned int p_indices[] = {
        // Base (Square)
        0, 1, 2, 
        2, 3, 0,

        // Sides (Triangles)
        0, 1, 4,  // Front-Right
        1, 2, 4,  // Front-Left
        2, 3, 4,  // Back-Left
        3, 0, 4   // Back-Right
    };


    std::vector<unsigned int>texCoords;

    static constexpr std::size_t c_size = sizeof(c_vertices);
    static constexpr std::size_t c_indexCount = sizeof(c_indices) / sizeof(c_indices[0]);

    glm::vec3 position;

    void setVoxelDist(int value)
    {
        voxelDist = value;
    }
    int getvoxelDist()
    {
        return voxelDist;
    }

    int instanceID;
    int voxelDist = 1;

    glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);

    static constexpr std::size_t t_size = sizeof(t_vertices); 

    static constexpr std::size_t q_size = sizeof(q_vertices);
    static constexpr std::size_t q_indexCount = sizeof(q_indices) / sizeof(q_indices[0]);

    static constexpr std::size_t p_size = sizeof(q_indices);
    static constexpr std::size_t p_indexCount = sizeof(p_indices) / sizeof(p_indices[0]);
};

