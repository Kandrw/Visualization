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

#include "model/map.hpp"


int main(int argc, char *argv[]){
    srand(time(NULL));
    
    Window::Initialize(1000, 1000, "Visualization_3.1"); 
    //glClearColor(0.6f,0.62f,0.65f,1);
    //Вкл буфер глубины
    glEnable(GL_DEPTH_TEST);
    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::radians(90.0f));

    //
    Map map(1e6);
    GeometryMap gmap(&map);
    //
    output<<"[OBJECTS INIT]\n";

    output<<glGetString(GL_VERSION)<<"\n";
    float lastTime = glfwGetTime();
	float delta = 0.0f;
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
        }
        if(con_tab){
            camera.camera_enevts(delta);
        }
        map.draw_cube(camera.getView(), camera.getProjection(), gmap.model);
        gmap.load_model_matrix(camera.getView(), camera.getProjection(), gmap.model);
        gmap.draw();
        
        Window::swapBuffers();
        Window::pullEvents();
        Sleep(30);
        
    }
    output.setColorStream('0', '7');
    output<<"End program\n";
    glfwTerminate();
    
    return 0;
}



