#ifndef GEOMETRYLINE_H
#define GEOMETRYLINE_H

#include <iostream>

#include <glm/glm.hpp>

#include "template_object.hpp"

class Shader;

class GeometryLine{
public:
    GeometryLine(glm::vec3 pos, float size, glm::vec3 norm);
    ~GeometryLine();
    void render();
    void draw();
    void load_model_matrix(glm::mat4 view_camera, glm::mat4 projection);
    //void set_color(float[3]);
    void rotate(float angle, glm::vec3 xyz);
    //void setLightColorPos(glm::vec3 pos, glm::vec3 color);
    //int get_id();
    //void control();
private:
    bool load_shader();
    void generate_vertices_normales();
private:
    Shader *shader = nullptr;
    std::string frag = "res/shaders/geometry_line/fragment.glsl";
    std::string vert = "res/shaders/geometry_line/vertex.glsl";
    unsigned int VBO, VAO;
protected:
    Data_object data_repn;
    //glm::vec3 normal_pos = glm::vec3(1.f, 0.f, 0.f);
    //float speed = 0.1;
};
#endif