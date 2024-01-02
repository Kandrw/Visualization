//#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Shader;

class GeometryPoint
{
private:

    float x = 0.1, y = 0.1, z = 0.0;
    float sizex = 0.1f, sizey = 0.1f;
    Shader *shader = nullptr; 

    unsigned int VBO, VAO;
    

    float vertices[18] = {
        0.1f,  0.1f, 0.0f,
       -0.1f,  0.1f, 0.0f,
       -0.1f, -0.1f, 0.0f,
       0.1f,  0.1f, 0.0f,
       0.1f,  -0.1f, 0.0f,
       -0.1f, -0.1f, 0.0f,
    };
    float color[18] = {
        1.0f, 1.0f, 1.0f,
        0.6f, 0.6f, 1.0f,
        0.3f, 0.0f, 0.3f,
        0.6f, 0.6f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.3f, 0.0f, 0.3f,

    };
    float data[36];

    void join_data();
    bool load_shader();
    void generate_vertices();
public:
    char type = 'g';
    float speed = 0.3;
    GeometryPoint();
    ~GeometryPoint();
    //bool load_shader();
    void render();
    void draw();
    void set_position(float dx, float dy);
    void set_size(float dx, float dy);
    float get_posx();
    float get_posy();
    float distance_point(GeometryPoint *point);
    void set_color(float *col, int N);
    //void rotate(glm::mat4 mat_rotate);
    
};


float distance_points(float x1, float y1, float x2, float y2);
void interaction_of_objects(GeometryPoint *points, int N);

