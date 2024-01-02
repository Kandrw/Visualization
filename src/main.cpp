#include <iostream>
#include <cstdlib>
#include <ctime>


#define GLEW_STATIC

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>


#include "windows.h"

#include "output/output.hpp"
#include "window/window.hpp"
#include "shaders/shader.hpp"

#include "graphics/geometry_object.hpp"
#include "graphics/geometry_point.hpp"

#define COUNT_POINTS 100
#define RANDOM_POS ((float)rand() / RAND_MAX) - ( (float)rand() / RAND_MAX )
#define RANDOM_SIZE (((float)rand() / RAND_MAX) / 10.0f) + 0.01f

float color1[18] = {
        0.0f, 0.0f, 0.0f,
        0.1f, 0.6f, 0.1f,
        0.1f, 0.6f, 0.1f,
        0.1f, 0.6f, 0.1f,
        0.0f, 0.0f, 0.0f,
        0.1f, 0.6f, 0.1f,
};
float color2[18] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
};

float color3[18] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.9f,
        0.0f, 0.0f, 0.9f,
        0.0f, 0.0f, 0.9f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.9f,
};



int main(int argc, char *argv[]){
    Window::Initialize(800, 800, "Visualization_2"); 

    
    std::string frag = "res/shaders/fragment.glsl";
    std::string vert = "res/shaders/vertex.glsl";
    
    //Shader *shader = load_Shader(frag, vert);
    //GeometryObj *geometryobj1 = new GeometryObj();
    //int N_point = 
    

    GeometryPoint points[COUNT_POINTS];
    GeometryPoint *point = &points[0];
    for(int i = 1; i < COUNT_POINTS/3; ++i){
        points[i].set_position(RANDOM_POS, RANDOM_POS);
        points[i].set_size(0.02, 0.02);
        points[i].type = 'n';
        points[i].set_color(color2, 18);
        points[i].render();
    }
    for(int i = COUNT_POINTS/3; i < COUNT_POINTS/3 * 2 + 10; ++i){
        points[i].set_position(RANDOM_POS, RANDOM_POS);
        points[i].set_size(0.025, 0.025);
        points[i].type = 'g';
        points[i].set_color(color1, 18);
        points[i].render();
    }
    for(int i = COUNT_POINTS/3 * 2 + 10; i < COUNT_POINTS; ++i){
        points[i].set_position(RANDOM_POS, RANDOM_POS);
        points[i].set_size(0.025, 0.025);
        points[i].type = 'b';
        points[i].speed = 0.5;
        points[i].set_color(color3, 18);
        points[i].render();
    }

    //glClearColor(0.6f,0.62f,0.65f,1);
    glm::mat4 mat_rotate = glm::mat4(1.0f);
    while (!Window::isShouldClose())
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //mat_rotate = glm::mat4(1.0f);
        interaction_of_objects(points, COUNT_POINTS);
        if(Window::pressed(GLFW_KEY_SPACE)){
            Window::payse = !Window::payse;
        }
        if(Window::pressed(GLFW_KEY_ESCAPE)){
            Window::setShouldClose(true);
        }
        if(Window::pressed(GLFW_KEY_W)){
            output<<"W\n";
            mat_rotate = glm::mat4(1.0f);
            //mat_rotate = glm::rotate(mat_rotate, ygol, glm::vec3(0.0, 0.0, 1.0)); 
            point->set_position(0.0f, 0.05f);
        }
        if(Window::pressed(GLFW_KEY_D)){
            output<<"D\n";
            point->set_position(0.05f, 0.0f);
        }
        if(Window::pressed(GLFW_KEY_S)){
            output<<"S\n";
            mat_rotate = glm::mat4(1.0f);
            //mat_rotate = glm::rotate(mat_rotate, ygol, glm::vec3(0.0, 0.0, 1.0));
            point->set_position(0.0f, -0.05f);
        }
        if(Window::pressed(GLFW_KEY_A)){
            output<<"A\n";
            point->set_position(-0.05f, 0.0f);
        }
        point->render();
        //point.rotate(mat_rotate);
        for(int i = 0; i < COUNT_POINTS; ++i){
            points[i].draw();
        }
        Window::swapBuffers();
        Sleep(20);
        
    }
    output.setColorStream('0', '7');
    output<<"End program\n";
    glfwTerminate();
    //delete shader;
    //delete geometryobj1;

    return 0;
}



