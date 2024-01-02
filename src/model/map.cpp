#include "map.hpp"

#include <iostream>
#include <cstdlib>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../output/output.hpp"
#include "../loaders/load_data.hpp"
#include "../shaders/shader.hpp"
#include "../window/window.hpp"

#include "cube.hpp"

#define VERTEX(array, index, x, y, z, normz) \
        array[index] = x; \
        array[index + 1] = (float)z / normz; \
        array[index + 2] = y; \
        index+=3;

Map::Map(int N) : N(N){

    load_data();

    size = (float)sqrt(N) * step;
    output<<"size = "<<size<<"\n";
    
    output<<"N = "<<N<<"\n";
    sizemapx = (N-1) * step;
    sizemapz = (N-1) * step;
    output<<"sizemapx = "<<sizemapx<<"\n";
    init_cubes();
    output<<"[Map] Create map\n";

}
Map::~Map(){
    if(array_heights){
        delete[] array_heights;
    }
    for(int i = 0; i < count_cube; ++i){
        delete cubes[i];
        cubes[i] = nullptr;
    }
    cubes.clear();

}
int Map::getN(){
    return N;
}
void Map::get_pos(float *x, float *y, float *z){
    if(x)
        *x = this->posx;
    if(y)
        *y = this->posy;
    if(z)
        *z = this->posz;
}
bool Map::load_data(){
    array_heights = read_bin_type_int(fname_heights, N);
    if(!array_heights){
        return false;
    }
    output<<"[Map]: load data, N = "<<N<<"\n";
    return true;
}
void Map::init_cubes(){
    int i;
    Cube *cube;
    GeometryCube *gcube;
    for(i = 0; i < count_cube; ++i){
        cube = new Cube(((rand() % sizemapx) + posx) / 200.f, 3, ((rand() % sizemapz) + posz) / 300.f);
        gcube = new GeometryCube(cube);
        cubes.push_back(gcube);
    }
}
void Map::draw_cube(glm::mat4 view, glm::mat4 projection, glm::mat4 model){
    for(int i = 0; i < count_cube; ++i){
        cubes[i]->load_model_matrix(view, projection, model);
        cubes[i]->draw();
    }
}
//-----------------------------------------------------
GeometryMap::GeometryMap(Map *map){
    load_shader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    this->map = map;
    N = map->getN();
    size_buffer = (sqrt(N)-1) * (sqrt(N)-1) * (3 * 3 * 2);//точки, вершины, треугольники
    buffer = new float[size_buffer];
    render();
    output<<"[GeometryMap]: Init Geometry object\n";
}
GeometryMap::~GeometryMap(){
    //delete map;
    delete[] buffer;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
bool GeometryMap::load_shader(){
    std::string frag = "res/shaders/geometry_map/fragment.glsl";
    std::string vert = "res/shaders/geometry_map/vertex.glsl";
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}

void GeometryMap::render(){
    output<<"Render start\n";
    int ix, iy;
    int x = sqrt(N), y = sqrt(N);
    int index = 0;
    float step = map->step;
    float px = map->posx, py = map->posy, pz = map->posz;
    int *data = map->array_heights;
    int normz = map->norm_height;
    for(iy = 0; iy < y-1; ++iy){
        px = map->posx;
        for(ix = 0; ix < x-1; ++ix){
            VERTEX(buffer, index, py, px, *(data + iy * y + ix), normz);
            VERTEX(buffer, index, py, px + step, *(data + iy * y + ix + 1), normz);
            VERTEX(buffer, index, py + step, px + step, *(data + (iy + 1) * y + ix + 1), normz);
            VERTEX(buffer, index, py, px, *(data + iy * y + ix), normz);
            VERTEX(buffer, index, py + step, px, *(data + (iy + 1) * y + ix), normz);
            VERTEX(buffer, index, py + step, px + step, *(data + (iy + 1) * y + ix + 1), normz);
            px += step;
        }
        py += step;
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_buffer * sizeof(float), buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); 
    output<<"Render end\n";
}
void GeometryMap::draw(){
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, size_buffer);
    glBindVertexArray(0);
}
void GeometryMap::load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model){
    shader->use();
    GLuint viewLoc = glGetUniformLocation(shader->id(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projectionLoc = glGetUniformLocation(shader->id(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    GLuint modelLoc = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}






