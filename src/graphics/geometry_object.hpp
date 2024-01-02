#include <glm/glm.hpp>

class Shader;

class GeometryObj{

public:
    GeometryObj();
    ~GeometryObj();
    
    int get_N();
    void set_N(int N);
    void render();
    void draw();
    void rotate(glm::mat4 mat_rotate);
    void set_position(float dx, float dy);
    void load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model);
    glm::mat4 model = glm::mat4(1.0f);
    
private:
    bool load_shader();
    void join_data();
    
    void generate_vertices();
private:
    int N;
    
    Shader *shader = nullptr;
    unsigned int VBO, VAO;
    float x = 0.0, y = 0.0, z = 0.0;
    float sizex = 2.5f, sizey = 2.5f;
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
        0.0f, 0.6f, 1.0f,
        1.0f, 1.0f, 1.0f,
        0.3f, 0.0f, 0.3f,

    };
    float data[36];



    


};



