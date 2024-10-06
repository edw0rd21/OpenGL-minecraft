#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Quad.h"   
#include "Renderer.h"
#include "Camera.h"

class World {
public:

    World() : camera(glm::vec3(3.0f, 3.0f, 3.0f)) {}

    //void addCube(const Quad& quad) {
    //    quads.push_back(quad);
    //}


    void render(float aspectRatio)
    {
        glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        renderer.draw(projection, view, model);
    }


    //void update(float deltaTime) {
    //    
    //    for (Cube& cube : cubes) {
    //        cube.update(deltaTime); 
    //    }
    //}

private:
    Quad quad;
    Camera camera;
    Renderer renderer;

};
