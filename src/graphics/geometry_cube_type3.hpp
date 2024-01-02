

#include <iostream>

#include <glm/glm.hpp>

#include "template_object.hpp"
#include "../graphics/geometry_line.hpp"

class Shader;


class GeometryCubeT3{
public:
    GeometryCubeT3(float *pos_size_rgb, int id);
    ~GeometryCubeT3();
    void render();
    void draw();
    void load_model_matrix(glm::mat4 view_camera, glm::mat4 projection);
    void set_color(float[3]);
    void rotate(float angle, glm::vec3 xyz);
    void setLightColorPos(glm::vec3 pos, glm::vec3 color);
    int get_id();
    void control();
    GeometryLine *line = nullptr;
    void Line_load_matrix_draw(glm::mat4 view_camera, glm::mat4 projection);
    
private:
    bool load_shader();
    void generate_vertices_normales();
    void _move();
private:
    Shader *shader = nullptr;
    std::string frag = "res/shaders/geometry_cube/fragment_norm.glsl";
    std::string vert = "res/shaders/geometry_cube/vertex_norm.glsl";
    unsigned int VBO, VAO;

protected:
    Data_object data_repn;
    
    //glm::vec3 normal_pos = glm::vec3(1.f, 0.f, 0.f);
    //float speed = 0.1;
};



