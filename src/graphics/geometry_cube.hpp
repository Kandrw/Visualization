#include <iostream>

#include <glm/glm.hpp>

#include "template_object.hpp"

class Shader;

class GeometryCube{
public:
    GeometryCube(float *pos_size_rgb);
    ~GeometryCube();
    //bool initialization();
    void render();
    void draw();
    void load_model_matrix(glm::mat4 view, glm::mat4 projection);
    void set_color(float[3]);
    void rotate(float angle, glm::vec3 xyz);
    void get_pos(float *x, float *y, float *z);
    void set_add_pos(float x, float y, float z);
    
public:
    float speed = 0.1;

private:
    bool load_shader();
    void generate_vertices();
private:
    Shader *shader = nullptr;
    std::string frag = "res/shaders/geometry_cube/fragment.glsl";
    std::string vert = "res/shaders/geometry_cube/vertex.glsl";
    unsigned int VBO, VAO;
protected:
    Data_object data_repn;
};
