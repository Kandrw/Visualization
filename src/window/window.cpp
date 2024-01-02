#include "window.hpp"

//#include <iostream>
#include <cstring>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../output/output.hpp"


GLFWwindow* Window::window;

bool Window::payse = false;
GLuint Window::WIDTH, Window::HEIGHT;
bool *Window::keys;
float Window::m_x, Window::m_y;




int Window::Initialize(int w, int h, const char *title){
    WIDTH = w;
    HEIGHT = h;
    payse = false;
    keys = new bool[COUNT_KEYS];
    memset(keys, false, sizeof(bool) * COUNT_KEYS);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);

    if(window == nullptr){
        output << "Failed create window\n";
        glfwTerminate();
		    return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
		    output << "Failed to initialize GLEW\n";
		    return -1;
	    }
    glViewport(0, 0, WIDTH, HEIGHT);
    


}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    
    if(key >= COUNT_KEYS){
        output <<"Error: key > count_key\n";
    }

    else if(action == GLFW_PRESS){

        keys[key] = true;
    }
    else if(action == GLFW_RELEASE){
        keys[key] = false;
    }
}

bool Window::pressed(int key){
    if(key < 0 || key > COUNT_KEYS){
        output <<"Not found key: "<<key<<"\n";
        return false;
    }
    return keys[key];

}

void Window::cursor_position(GLFWwindow* window, double xpos, double ypos){
    m_x = xpos;
    m_y = ypos;
}

void Window::setShouldClose(bool flag){
	glfwSetWindowShouldClose(window, flag);
}

bool Window::isShouldClose(){
    return glfwWindowShouldClose(window);
}
void Window::swapBuffers(){
    glfwSwapBuffers(window);
}


