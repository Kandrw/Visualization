#include <iostream>

#include <glm/glm.hpp>

class Shader;

class GeometryCube;

class Cube{
    friend class GeometryCube;
public:
    Cube(float posx, float posy, float posz);


    float sizex = 2.0f, sizey = 2.0f, sizez = 2.0f;
    float posx, posy, posz;

    float speed = 0.3;
    float speedy = 0.3;
};



class GeometryCube{

public:
    GeometryCube(Cube *cube);
    ~GeometryCube();

    void render();
    void draw();
    //void set_position(float dx, float dy);
    void load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model);
    glm::mat4 model = glm::mat4(1.0f);
    //float x = 0.0, y = 2.0, z = 3.0;
    //float speed = 0.05;
    //void move(float *buffer, int N);
    void move();
private:
    bool load_shader();
    void generate_vertices();
private:
    Cube *cube;
    //float scale_global;
    Shader *shader = nullptr;
    std::string frag = "res/shaders/geometry_cube/fragment.glsl";
    std::string vert = "res/shaders/geometry_cube/vertex.glsl";
    unsigned int VBO, VAO;
    
    //float sizex = 1.0f, sizey = 1.0f, sizez = 1.0f;
    float buffer[18 * 6];
    int size_buffer = 108;

    


};


