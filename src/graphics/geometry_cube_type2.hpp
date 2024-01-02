#include <iostream>

#include <glm/glm.hpp>

#include "template_object.hpp"

class Shader;

class GeometryCubeT2{
public:
    GeometryCubeT2(float *pos_size_rgb);
    ~GeometryCubeT2();
    void render();
    void draw();
    void load_model_matrix(glm::mat4 view, glm::mat4 projection);
    void set_color(float[3]);
    void rotate(float angle, glm::vec3 xyz);
    void setLightColorPos(glm::vec3 pos, glm::vec3 color);
private:
    bool load_shader();
    void generate_normales();
    void generate_vertices();
private:
    Shader *shader = nullptr;
    std::string frag = "res/shaders/geometry_cube/fragment_norm.glsl";
    std::string vert = "res/shaders/geometry_cube/vertex_norm.glsl";
    unsigned int VBO, VAO;
protected:
    Data_object data_repn;
};
