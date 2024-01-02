#include "geometry_map.hpp"

#include <iostream>
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

#define VERTEX(index, x, y, z) \
        buffer[index] = x; \
        buffer[index + 1] = (float)z / 100.f; \
        buffer[index + 2] = y; \
        index+=3;
#define RANDOM_SIZE (((float)rand() / RAND_MAX) / 10.0f) + 0.01f
//#define RANDOM_SIZE 0.0f

GeometryMap::GeometryMap(){
    bool init = true;
    set_N(1000000);
    if(!load_data())
        init = false;
    
    if(!load_shader()){
        init = false;
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    size_buffer = (sqrt(N)-1) * (sqrt(N)-1) * (3 * 3 * 2);
    buffer = new float[size_buffer];
    //aspectRatio = (float)Window::HEIGHT / (float)Window::WIDTH;
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    //projection = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    //load_model_matrix(view, projection, model);
    render();
    if(!init)
        output<<"[GeometryMap]: failed init\n";
    else
        output<<"[GeometryMap]: Init Geometry object\n";
}
GeometryMap::~GeometryMap(){
    if(array_heights){
        delete[] array_heights;
    }
    if(array_lats){
        delete[] array_lats;
    }
    if(array_lons){
        delete[] array_lons;
    }
    if(shader){
        delete shader;
    }
    delete[] buffer;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

}

bool GeometryMap::load_data(){
    std::string fname_heights = "res/data/heights.bin";
    std::string fname_lats= "res/data/lats.bin";
    std::string fname_lons = "res/data/lons.bin";
    array_heights = read_bin_type_int(fname_heights, get_N());
    if(!array_heights){
        return false;
    }
    array_lats = read_bin_type_float(fname_lats, get_N());
    if(!array_lats){
        return false;
    }
    array_lons = read_bin_type_float(fname_lons, get_N());
    if(!array_lons){
        return false;
    }
    output<<"[GeometryMap]: load data, N = "<<N<<"\n";
    return true;
}


int GeometryMap::get_N(){
    return N;
}
void GeometryMap::set_N(int N){
    this->N = N;
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
    int ix, iy;
    int x = sqrt(N), y = sqrt(N);
    int index = 0;
    float step = 0.3;
    float px = 0.0, py = 0.0, pz = 0.0;
    //float px = -1.0f * (float)(x/2) * step;
    //float py = px;
    
    int *data = array_heights;
    for(iy = 0; iy < y-1; ++iy){
        px = 0.0;
        for(ix = 0; ix < x-1; ++ix){
            VERTEX(index, py, px, *(data + iy * y + ix));
            VERTEX(index, py, px + step, *(data + iy * y + ix + 1));
            VERTEX(index, py + step, px + step, *(data + (iy + 1) * y + ix + 1));
            VERTEX(index, py, px, *(data + iy * y + ix));
            VERTEX(index, py + step, px, *(data + (iy + 1) * y + ix));
            VERTEX(index, py + step, px + step, *(data + (iy + 1) * y + ix + 1));
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
    output<<"Render\n";
}

void GeometryMap::transform_update(){
    if(Window::clicked(GLFW_MOUSE_BUTTON_LEFT)){
        //output<<"MOUSE_BUTTON_LEFT\n";
        camY += -Window::deltaY / Window::HEIGHT * 2;
        camX += -Window::deltaX / Window::HEIGHT * 2;
        model = glm::mat4(1.0f);
        model = glm::rotate(model, camY, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, camX, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
    }
    
    if(Window::pressed(GLFW_KEY_Q)){
        model = glm::rotate(model, -1.0f * glm::radians(ygol), type_axis);
    }
    if(Window::pressed(GLFW_KEY_E)){
        model = glm::rotate(model, glm::radians(ygol), type_axis);
    }
    if(Window::pressed(GLFW_KEY_1)){
        type_axis = glm::vec3(0.1f, 0.0f, 0.0f);
    }
    if(Window::pressed(GLFW_KEY_2)){
        type_axis = glm::vec3(0.0f, 0.1f, 0.0f);
    }
    if(Window::pressed(GLFW_KEY_3)){
        type_axis = glm::vec3(0.0f, 0.0f, 0.1f);
    }
    if(Window::pressed(GLFW_KEY_4)){
        model = glm::scale(model, glm::vec3(0.9, 0.9, 0.9));
    }
    if(Window::pressed(GLFW_KEY_5)){
        model = glm::scale(model, glm::vec3(1.1, 1.1, 1.1));
    }
    if(Window::scrollY < 0.0 && scale > 0.005){
            if(scale -= 0.1 <= 0){
                scale -= (scale/2.0f);
            }
            else
                scale -= 0.1;
            model = glm::mat4(1.0f);
            model = glm::rotate(model, camY, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, camX, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            Window::scrollY = 0.0;
    }
    else if(Window::scrollY > 0.0 && scale < 3.0){
            scale += scale/3.0f;
            model = glm::mat4(1.0f);
            model = glm::rotate(model, camY, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, camX, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            Window::scrollY = 0.0;
    }
    //load_model_matrix(view, projection, model);

}

void GeometryMap::draw(){
    shader->use();
    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, size_buffer);
    glBindVertexArray(0);
}

void GeometryMap::set_position(float dx, float dy){
    //this->x += dx;
    //this->z += dx;
    //this->y += dy;
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

void GeometryMap::init_cubes(){
    

}