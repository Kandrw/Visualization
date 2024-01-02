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
#include "window/camera.hpp"
#include "shaders/shader.hpp"

#include "graphics/geometry_object.hpp"
#include "graphics/geometry_point.hpp"
#include "graphics/geometry_map.hpp"
#include "graphics/geometry_cube.hpp"


#define RANDOM_POS ((float)rand() / RAND_MAX) - ( (float)rand() / RAND_MAX )
#define RANDOM_SIZE (((float)rand() / RAND_MAX) / 10.0f) + 0.01f
//#define HEIGHT 1000
//#define WIDTH 1000

int main(int argc, char *argv[]){
    srand(time(NULL));
    
    Window::Initialize(1000, 1000, "Visualization_3"); 
    //glClearColor(0.6f,0.62f,0.65f,1);
    //Вкл буфер глубины
    glEnable(GL_DEPTH_TEST);
    //std::string frag = "res/shaders/fragment.glsl";
    //std::string vert = "res/shaders/vertex.glsl";
    
    GeometryMap gmap;
    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::radians(90.0f));
    //GeometryObj gobj;

    GeometryCube cube;
    output<<"init matrix\n";

    output<<glGetString(GL_VERSION)<<"\n";
    float lastTime = glfwGetTime();
	float delta = 0.0f;
    float camX = 0.0f;
	float camY = 0.0f;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    bool con_tab = false;
    glm::mat4 view1;
    bool tamer = 0;
    while (!Window::isShouldClose()){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;
        if(Window::clicked(GLFW_MOUSE_BUTTON_LEFT)){
            output<<"MOUSE_BUTTON_LEFT\n";
        }
        if(Window::pressed(GLFW_KEY_SPACE)){
            Window::payse = !Window::payse;
        }
        if(Window::pressed(GLFW_KEY_ESCAPE)){
            Window::setShouldClose(true);
        }
        if(Window::jpressed(GLFW_KEY_TAB)){
            output<<"TAB\n";
            con_tab = !con_tab;
            Window::setCursorMode(con_tab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        }
        if(Window::jpressed(GLFW_KEY_E)){
            output<<"E\n";
            tamer = !tamer;
            output<<"tamer = "<<tamer<<"\n";
        }
        if(con_tab){
            camera.camera_enevts(delta);
            view1 = camera.getView();
            view1 = glm::translate(view1, glm::vec3(cube.x, cube.y, cube.z));
        }
        else{
            view1 = camera.getView();
            //gmap.transform_update();
            if(Window::pressed(GLFW_KEY_A)){
                cube.z -= cube.speed;
                //view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, cube.z));

            }
            if(Window::pressed(GLFW_KEY_D)){
                cube.z += cube.speed;
                //view1 = glm::translate(view1, glm::vec3(0.0f, 0.0f, cube.z));
            }
            if(Window::pressed(GLFW_KEY_W)){
                cube.x += cube.speed;
                //view1 = glm::translate(view1, glm::vec3(cube.x, 0.0f, 0.0f));
            }
            if(Window::pressed(GLFW_KEY_S)){
                cube.x -= cube.speed;
                //view1 = glm::translate(view1, glm::vec3(cube.x, 0.0f, 0.0f));
            }
            view1 = glm::translate(view1, glm::vec3(cube.x, cube.y, cube.z));
        }
        if(tamer){
            view1 = camera.getView();
            cube.y -= cube.speed;
            view1 = glm::translate(view1, glm::vec3(cube.x, cube.y, cube.z));
        }
        //view1 = glm::translate(view1, glm::vec3(cube.x, 0.0f, cube.z));
        /*
        model = glm::mat4(1.0f);
        model = glm::rotate(model, (GLfloat)glfwGetTime() * 5.0f, glm::vec3(0.5f, 1.0f, 0.0f));
        object.load_model_matrix(viewMatrix, projectionMatrix, model);
        object.draw();
        */
        gmap.load_model_matrix(camera.getView(), camera.getProjection(), gmap.model);
        gmap.draw();
        //gobj.load_model_matrix(view1, camera.getProjection(), gobj.model);
        //gobj.draw();
        cube.load_model_matrix(view1, camera.getProjection(), cube.model);
        cube.draw();
        Window::swapBuffers();
        Window::pullEvents();
        Sleep(30);
        
    }
    output.setColorStream('0', '7');
    output<<"End program\n";
    glfwTerminate();
    
    return 0;
}



