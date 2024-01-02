#include <glm/glm.hpp>

#ifndef TEMPLATE_OBJECT




#define TEMPLATE_OBJECT

struct Data_object{
    float pos_size_rgb[9];//pos_xyz, size_xyz, rgb
    float *buffer;
    int size_buffer;
    int size_vertices;
    int size_norm;
    glm::mat4 model;
    int id;
    
    glm::vec3 pos;
    glm::vec3 direction;
    float speed;
    float angle;
};










#endif











