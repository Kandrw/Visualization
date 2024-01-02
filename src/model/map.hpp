#include <vector>
#include <iostream>

#include <glm/glm.hpp>

class Cube;
class GeometryCube;
class Shader;
class GeometryMap;

class Map{
    friend class GeometryMap;
public:
    Map(int N);
    ~Map();
    int getN();
    void get_pos(float *x, float *y, float *z);
    void draw_cube(glm::mat4 view, glm::mat4 projection, glm::mat4 model);

private:
    bool load_data();
    void init_cubes();

private:
    std::string fname_heights = "res/data/heights.bin";
    std::string fname_lats= "res/data/lats.bin";
    std::string fname_lons = "res/data/lons.bin";
    int N;
    int *array_heights = nullptr;
    
    int sizemapx, sizemapy = 20, sizemapz;
    //int posmapx = -15, posmapy = 1, posmapz;
    //object
    int count_cube = 10;
    std::vector<GeometryCube*> cubes;
    //render
    float norm_height = 100.f;
    //float scale_global = 1.0f;//относительно нормализованных координат
    float posx = 0.0f, posy = 0.0f, posz = 0.0f;
    float step = 0.2f;
    float size;
    //float indent = 0.0;

};


class GeometryMap{

public:
    GeometryMap(Map *map);
    ~GeometryMap();
    void render();
    void draw();
    void load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model);
    //void transform_update();
    //glm::mat4 view = glm::mat4(1.0f);
    //glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
private:
    bool load_shader();
private:
    int N;
    Map *map = nullptr;
    Shader *shader = nullptr;
    std::string frag = "res/shaders/geometry_map/fragment.glsl";
    std::string vert = "res/shaders/geometry_map/vertex.glsl";
    unsigned int VBO, VAO;
    float *buffer = nullptr;
    int size_buffer;
};











