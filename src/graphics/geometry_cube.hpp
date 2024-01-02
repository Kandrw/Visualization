#include <glm/glm.hpp>



class Shader;

class GeometryCube{

public:
    GeometryCube();
    GeometryCube(float x, float y, float z);
    ~GeometryCube();

    void render();
    void draw();
    void set_position(float dx, float dy);
    void load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model);
    glm::mat4 model = glm::mat4(1.0f);
    float x = 0.0, y = 2.0, z = 3.0;
    float speed = 0.05;
    void move(float *buffer, int N);
private:
    bool load_shader();
    void generate_vertices();
private:
    Shader *shader = nullptr;
    unsigned int VBO, VAO;
    
    float sizex = 1.0f, sizey = 1.0f, sizez = 1.0f;

    float data[36];
    float buffer[18 * 6];//108
    int size_buffer = 108;//108

    


};



