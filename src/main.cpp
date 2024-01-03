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

//#include "model/map.hpp"
#include "graphics/geometry_cube.hpp"
#include "graphics/geometry_cube_type2.hpp"
#include "graphics/geometry_cube_type3.hpp"
#include "graphics/geometry_line.hpp"




int main(int argc, char *argv[]){
    srand(time(NULL));
    
    Window::Initialize(1000, 1000, "Visualization_3.3"); 
    init_log();

    //output<<"verson:  "<<glGetString(GL_VERSION)<<"\n";
    //glClearColor(0.6f,0.62f,0.65f,1);
    //Вкл буфер глубины
    glEnable(GL_DEPTH_TEST);
    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f), glm::radians(90.0f));

    //
    //Map map(1e6);
    //GeometryMap gmap(&map);
    // в нули позицию из за матриц
    
    float pos_size_rgb[] = {-1.f, 0.f, -1.f, 2.0f, 4.0f, 2.f, 0.8f, 0.8f, 0.8f};
    glm::vec3 light1 = glm::vec3(1.f, 1.f, 1.f);
    //float pos_size_rgb2[] = {10.f, 0.f, -10.f, 2.0f, 4.0f, 2.f, 0.1f, 0.8f, 0.1f};
    float pos_size_rgb2[] = {10.f, 0.f, -10.f, 2.0f, 4.0f, 2.f, 0.3f, 0.0f, 0.6f};
    //GeometryCube cube(pos_size_rgb);
    GeometryCube cube_light(pos_size_rgb);

    GeometryCubeT2 cube2(pos_size_rgb2);
    //cube2.setLightColorPos(glm::vec3(1.f, 0.f, -1.f), glm::vec3(1.f, 1.f, 1.f));

    float pos_size_rgb3[] = {-20.f, -5.f, -20.f, 40.0f, 1.0f, 40.f, 0.2f, 0.5f, 0.2f};
    GeometryCubeT2 cube3(pos_size_rgb3);
    
    float pos_size_rgb4[] = {-8.f, 0.f, -2.f, 4.0f, 2.0f, 4.f, 0.1f, 0.0f, 0.8f};
    GeometryCubeT3 cube4(pos_size_rgb4, 34);

    //output<<;
    print_log(CONSOLE, "[OBJECTS INIT]\n");
    //Последняя задача: линия указывающая направление
    float lastTime = glfwGetTime();
	float delta = 0.0f;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    bool con_tab = false;
    glm::mat4 view1;
    bool tamer = 0;
    float x = 10.f, y = 6.f, z = 2.f;
    int select_obj = 0;
    while (!Window::isShouldClose()){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float currentTime = glfwGetTime();
		delta = currentTime - lastTime;
		lastTime = currentTime;
        if(Window::clicked(GLFW_MOUSE_BUTTON_LEFT)){
           print_log(CONSOLE,"MOUSE_BUTTON_LEFT\n");
        }
        if(Window::pressed(GLFW_KEY_SPACE)){
            Window::payse = !Window::payse;
        }
        if(Window::pressed(GLFW_KEY_ESCAPE)){
            Window::setShouldClose(true);
        }
        if(Window::jpressed(GLFW_KEY_TAB)){
            print_log(CONSOLE, "TAB\n");
            con_tab = !con_tab;
            Window::setCursorMode(con_tab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        }
        if(Window::jpressed(GLFW_KEY_E)){
            print_log(CONSOLE, "E\n");
        }
        if(con_tab){
            camera.camera_events(delta);
        }
        else{
            

            if(Window::pressed(GLFW_KEY_1)){
                select_obj = 1;
                
            }
            if(Window::pressed(GLFW_KEY_2)){
                select_obj = 2;
                
            }
    
            if(Window::pressed(GLFW_KEY_F)){
                //cube4.line = &line;
            }
            if(select_obj == 1){
                cube4.control();
            }
            else if(select_obj == 2){
                if(Window::pressed(GLFW_KEY_W)){
                    //output<<"D\n";
                    //cube.rotate(45, glm::vec3(0, 0, 1));
                    //cube.set_add_pos(0, 0, -cube.speed);
                    //line.rotate(45, glm::vec3(0, 0, 1));
                }
                if(Window::pressed(GLFW_KEY_D)){
                    //output<<"D\n";
                    //cube.rotate(45, glm::vec3(0, 0, 1));
                    //cube.set_add_pos(cube.speed, 0, 0);
                    //line.rotate(45, glm::vec3(0, 0, 1));
                }
                if(Window::pressed(GLFW_KEY_S)){
                    //output<<"S\n";
                    //cube.rotate(-45, glm::vec3(1, 0, 0));
                    //cube.set_add_pos(0, 0, cube.speed);
                    //line.rotate(-45, glm::vec3(1, 0, 0));
                }
                if(Window::pressed(GLFW_KEY_A)){
                    //output<<"A\n";
                    //cube.rotate(-45, glm::vec3(0, 0, 1));
                    //cube.set_add_pos(-cube.speed, 0, 0);
                    //line.rotate(-45, glm::vec3(0, 0, 1));
                }
            }
            
        }
        //cube.get_pos(&x, &y , &z);

        //glm::mat4 view = glm::translate(camera.getView(), glm::vec3(x, y, z));
        
        //cube.load_model_matrix(camera.getView(), camera.getProjection());
        //cube.draw();

        //cube.load_model_matrix(camera.getView(), camera.getProjection());
        //cube.draw();
        
        

        cube2.setLightColorPos(glm::vec3(x, y, z), light1);
        cube2.load_model_matrix(camera.getView(), camera.getProjection());
        cube2.draw();

        cube3.setLightColorPos(glm::vec3(x, y, z), light1);
        cube3.load_model_matrix(camera.getView(), camera.getProjection());
        cube3.draw();
        

        cube4.setLightColorPos(glm::vec3(x, y, z), light1);
        cube4.load_model_matrix(camera.getView(), camera.getProjection());
        cube4.draw();

        cube4.Line_load_matrix_draw(camera.getView(), camera.getProjection());

        
        
        
        
        Window::swapBuffers();
        Window::pullEvents();
        Sleep(30);
        
    }
    print_log(CONSOLE, "End program\n");
    glfwTerminate();
    
    return 0;
}



