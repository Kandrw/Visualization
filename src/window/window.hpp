
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define COUNT_KEYS 1024

class Window{
public:
    static GLuint WIDTH, HEIGHT;
    static GLFWwindow* window;
    static bool payse;

    static bool *keys;

    static float m_x, m_y;
    static int Initialize(int w, int h, const char *title);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static bool pressed(int key);
    static void cursor_position(GLFWwindow* window, double xpos, double ypos);
    static void setShouldClose(bool flag);
    static bool isShouldClose();
    static void swapBuffers();
};





