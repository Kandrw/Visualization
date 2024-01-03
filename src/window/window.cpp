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
unsigned int Window::_frames[1032];
float Window::m_x, Window::m_y;
float Window::deltaX, Window::deltaY;
float Window::scrollY = 0.0f;
float Window::_current = 0.0f;

int Window::Initialize(int w, int h, const char *title){
    WIDTH = w;
    HEIGHT = h;
    payse = false;
    keys = new bool[COUNT_KEYS+8];
    memset(keys, false, sizeof(bool) * (COUNT_KEYS + 8));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, title, nullptr, nullptr);

    if(window == nullptr){
        print_log(CONSOLE, "Failed create window\n");
        glfwTerminate();
		    return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback); 
    glfwSetCursorPosCallback(window, cursor_position);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
		    print_log(CONSOLE, "Failed to initialize GLEW\n");
		    return -1;
	}
    glViewport(0, 0, WIDTH, HEIGHT);
    


}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    
    if(key >= COUNT_KEYS){
        print_log(CONSOLE, "Error: key > count_key\n");
    }

    else if(action == GLFW_PRESS){
        keys[key] = true;
        _frames[key] = _current;
    }
    else if(action == GLFW_RELEASE){
        keys[key] = false;
        _frames[key] = _current;
    }
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS){
		Window::keys[_MOUSE_BUTTONS+button] = true;
		//Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
	}
	else if (action == GLFW_RELEASE){
		Window::keys[_MOUSE_BUTTONS+button] = false;
		//Events::_frames[_MOUSE_BUTTONS+button] = Events::_current;
	}
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    scrollY = (float)yoffset;
}

bool Window::pressed(int key){
    if(key < 0 || key > COUNT_KEYS){
        print_log(CONSOLE, "Not found key: %d\n", key);
        return false;
    }
    return keys[key];
}
bool Window::jpressed(int keycode){
	if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
		return false;
	return keys[keycode] && _frames[keycode] == _current;
}
bool Window::clicked(int button){
	int index = _MOUSE_BUTTONS+button;
	return keys[index];
}


void Window::cursor_position(GLFWwindow* window, double xpos, double ypos){
    
    deltaX += xpos - m_x;
    deltaY += ypos - m_y;
    
    m_x = xpos;
    m_y = ypos;
}
void Window::setCursorMode(int mode){
	glfwSetInputMode(window, GLFW_CURSOR, mode);
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

void Window::pullEvents(){
	_current++;
	deltaX = 0.0f;
	deltaY = 0.0f;
	glfwPollEvents();
}

