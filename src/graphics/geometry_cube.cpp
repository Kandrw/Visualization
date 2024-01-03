#include "geometry_cube.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../output/output.hpp"
#include "../shaders/shader.hpp"

#define VERTEX(buffer, index, x, y, z)\
    buffer[index] = x;\
    buffer[index+1] = y;\
    buffer[index+2] = z;\
    index += 3;
GeometryCube::GeometryCube(float *pos_size_rgb){
    print_log(CONSOLE, "[GeometryCube initialization...\n");
    memcpy(data_repn.pos_size_rgb, pos_size_rgb, 9 * sizeof(float));
    data_repn.size_vertices = 3 * 3 * 2 * 6;
    data_repn.size_norm = data_repn.size_vertices;
    data_repn.size_buffer = data_repn.size_vertices + data_repn.size_norm;
    data_repn.buffer = new float[data_repn.size_buffer];
    data_repn.model = glm::mat4(1.0f);
    generate_vertices();
    load_shader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    render();
    print_log(CONSOLE, "[GeometryCube initialization\n");
}
GeometryCube::~GeometryCube(){
    delete[] data_repn.buffer;
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
bool GeometryCube::load_shader(){
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}
void GeometryCube::draw(){
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, data_repn.size_vertices);
    glBindVertexArray(0);
}
void GeometryCube::load_model_matrix(glm::mat4 view_camera, glm::mat4 projection){
    glm::mat4 view = glm::translate(view_camera, data_repn.pos);
    //glm::mat4 model = glm::translate(data_repn.model, data_repn.pos);
    //glm::mat4 model = data_repn.model;
    shader->use();
    GLuint viewLoc = glGetUniformLocation(shader->id(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projectionLoc = glGetUniformLocation(shader->id(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    GLuint modelLoc = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(data_repn.model));
}

void GeometryCube::render(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data_repn.size_vertices * sizeof(float), data_repn.buffer, GL_STATIC_DRAW);
    //позиция в шейдере, размер аргумента в шейдере, тип, нормализация(вкл\выкл), шаг между данными, начало данных
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    shader->use();
    GLuint colorLoc = glGetUniformLocation(shader->id(), "color_obj");
    glUniform3fv(colorLoc, 1, data_repn.pos_size_rgb + 6);
}
void GeometryCube::set_color(float rgb[3]){
    memcpy((char*)data_repn.pos_size_rgb+6, (char*)rgb, 3 * sizeof(float));
    shader->use();
    GLuint colorLoc = glGetUniformLocation(shader->id(), "color_obj");
    glUniform3fv(colorLoc, 1, data_repn.pos_size_rgb + 6);
}
void GeometryCube::generate_vertices(){
    float *buffer = data_repn.buffer;
    float *ps = data_repn.pos_size_rgb;
    float x = ps[0], y = ps[1], z = ps[2];
    float sizex = ps[3], sizey = ps[4], sizez = ps[5];
    int index = 0;
    VERTEX(buffer, index, x        , y        , z        ); 
    VERTEX(buffer, index, x        , y + sizey, z        );
    VERTEX(buffer, index, x + sizex, y        , z        );
    VERTEX(buffer, index, x        , y + sizey, z        );
    VERTEX(buffer, index, x + sizex, y + sizey, z        );
    VERTEX(buffer, index, x + sizex, y        , z        );

    VERTEX(buffer, index, x        , y        , z + sizez);
    VERTEX(buffer, index, x        , y + sizey, z + sizez);
    VERTEX(buffer, index, x + sizex, y        , z + sizez);
    VERTEX(buffer, index, x        , y + sizey, z + sizez);
    VERTEX(buffer, index, x + sizex, y + sizey, z + sizez);
    VERTEX(buffer, index, x + sizex, y        , z + sizez);

    VERTEX(buffer, index, x        , y        , z        ); 
    VERTEX(buffer, index, x        , y        , z + sizez);
    VERTEX(buffer, index, x + sizex, y        , z        );
    VERTEX(buffer, index, x        , y        , z + sizez);
    VERTEX(buffer, index, x + sizex, y        , z        );
    VERTEX(buffer, index, x + sizex, y        , z + sizez);

    VERTEX(buffer, index, x        , y + sizey, z        ); 
    VERTEX(buffer, index, x        , y + sizey, z + sizez);
    VERTEX(buffer, index, x + sizex, y + sizey, z        );
    VERTEX(buffer, index, x        , y + sizey, z + sizez);
    VERTEX(buffer, index, x + sizex, y + sizey, z        );
    VERTEX(buffer, index, x + sizex, y + sizey, z + sizez);

    VERTEX(buffer, index, x        , y        , z        );
    VERTEX(buffer, index, x        , y + sizey, z        );
    VERTEX(buffer, index, x        , y        , z + sizez);
    VERTEX(buffer, index, x        , y        , z + sizez);
    VERTEX(buffer, index, x        , y + sizey, z        );
    VERTEX(buffer, index, x        , y + sizey, z + sizez);

    VERTEX(buffer, index, x + sizex, y        , z        );
    VERTEX(buffer, index, x + sizex, y + sizey, z        );
    VERTEX(buffer, index, x + sizex, y        , z + sizez);
    VERTEX(buffer, index, x + sizex, y        , z + sizez);
    VERTEX(buffer, index, x + sizex, y + sizey, z        );
    VERTEX(buffer, index, x + sizex, y + sizey, z + sizez);
}

void GeometryCube::rotate(float angle, glm::vec3 xyz){
    data_repn.model = glm::rotate(data_repn.model, glm::radians(angle), xyz);
}

void GeometryCube::get_pos(float *x, float *y, float *z){
    if(x)
        *x = data_repn.pos_size_rgb[0];
    if(y)
        *y = data_repn.pos_size_rgb[1];
    if(z)
        *z = data_repn.pos_size_rgb[2];
}

void GeometryCube::set_add_pos(float x, float y, float z){
    data_repn.pos_size_rgb[0] += x;
    data_repn.pos_size_rgb[1] += y;
    data_repn.pos_size_rgb[2] += z;
    
}