
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _MOUSE_BUTTONS 1024
#define COUNT_KEYS 1024

class Window{
public:
    static GLuint WIDTH, HEIGHT;
    static GLFWwindow* window;
    static bool payse;

    static bool *keys;
    static unsigned int _frames[1032];
    static float m_x, m_y;
    static float deltaX, deltaY;
    static float scrollY;
    static float _current;
    static int Initialize(int w, int h, const char *title);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static bool pressed(int key);
    static bool jpressed(int keycode);
    static bool clicked(int button);
    static void cursor_position(GLFWwindow* window, double xpos, double ypos);
    
    static void setShouldClose(bool flag);
    static bool isShouldClose();
    static void swapBuffers();
    static void setCursorMode(int mode);
    static void pullEvents();
};





