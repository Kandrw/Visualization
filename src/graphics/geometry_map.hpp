#include <glm/glm.hpp>

class Shader;
class GeometryCube;

class GeometryMap{

public:
    GeometryMap();
    ~GeometryMap();
    
    int get_N();
    void set_N(int N);
    void render();
    void draw();
    void set_position(float dx, float dy);
    void load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model);
    void transform_update();
    //glm::mat4 view = glm::mat4(1.0f);
    //glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    GeometryCube *cube = nullptr;
private:
    bool load_data();
    bool load_shader();
private:
    int N;
    int *array_heights = nullptr;
    float *array_lats = nullptr;
    float *array_lons = nullptr;
    Shader *shader = nullptr;
    unsigned int VBO, VAO;
    //float x = 0.0f, y = 0.0f, z = 0.0f;
    float step = 0.01f;
    float *buffer = nullptr;
    int size_buffer;
    float scale = 1.0f;
    float camX = 0.0f;
	float camY = 0.0f;
    glm::vec3 type_axis = glm::vec3(0.1, 0.0, 0.0);
    float ygol = 10.0f;

private:
    void init_cubes();
    float scale_map = 3.0f;
    
    //GeometryCube cubes[10];
    //int cb = sizeof(cubes)/sizeof(GeometryCube);
};



