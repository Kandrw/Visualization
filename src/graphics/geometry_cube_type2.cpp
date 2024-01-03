#include "geometry_cube_type2.hpp"

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
GeometryCubeT2::GeometryCubeT2(float *pos_size_rgb){
    print_log(CONSOLE, "[GeometryCube initialization...\n");
    memcpy(data_repn.pos_size_rgb, pos_size_rgb, 9 * sizeof(float));
    data_repn.size_vertices = 3 * 3 * 2 * 6;
    data_repn.size_norm = data_repn.size_vertices;
    data_repn.size_buffer = data_repn.size_vertices + data_repn.size_norm;
    data_repn.buffer = new float[data_repn.size_buffer];
    data_repn.model = glm::mat4(1.0f);
    generate_vertices();
    //generate_normales();
    load_shader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    render();
    print_log(CONSOLE, "[GeometryCube initialization\n");
}
GeometryCubeT2::~GeometryCubeT2(){
    delete[] data_repn.buffer;
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
bool GeometryCubeT2::load_shader(){
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}
void GeometryCubeT2::draw(){
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, data_repn.size_vertices);
    glBindVertexArray(0);
}
void GeometryCubeT2::load_model_matrix(glm::mat4 view, glm::mat4 projection){
    shader->use();
    GLuint viewLoc = glGetUniformLocation(shader->id(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projectionLoc = glGetUniformLocation(shader->id(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    GLuint modelLoc = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(data_repn.model));
}

void GeometryCubeT2::render(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data_repn.size_buffer * sizeof(float), data_repn.buffer, GL_STATIC_DRAW);
    //позиция в шейдере, размер аргумента в шейдере, тип, нормализация(вкл\выкл), шаг между данными, начало данных
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    shader->use();
    GLuint colorLoc = glGetUniformLocation(shader->id(), "color_obj");
    glUniform3fv(colorLoc, 1, data_repn.pos_size_rgb + 6);
}
void GeometryCubeT2::setLightColorPos(glm::vec3 pos, glm::vec3 color){
    shader->use();
    GLuint posLoc = glGetUniformLocation(shader->id(), "lightPos");
    glUniform3fv(posLoc, 1, glm::value_ptr(pos));
    GLuint colorLoc = glGetUniformLocation(shader->id(), "lightColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));

}
void GeometryCubeT2::set_color(float rgb[3]){
    memcpy((char*)data_repn.pos_size_rgb+6, (char*)rgb, 3 * sizeof(float));
    shader->use();
    GLuint colorLoc = glGetUniformLocation(shader->id(), "color_obj");
    glUniform3fv(colorLoc, 1, data_repn.pos_size_rgb + 6);
}
void GeometryCubeT2::generate_vertices(){
    float *buffer = data_repn.buffer;
    float *ps = data_repn.pos_size_rgb;
    float x = ps[0], y = ps[1], z = ps[2];
    float sizex = ps[3], sizey = ps[4], sizez = ps[5];
    int index = 0;
    VERTEX(buffer, index, x        , y        , z        ); VERTEX(buffer, index,  0.f,  0.f, -1.f);
    VERTEX(buffer, index, x        , y + sizey, z        ); VERTEX(buffer, index,  0.f,  0.f, -1.f);
    VERTEX(buffer, index, x + sizex, y        , z        ); VERTEX(buffer, index,  0.f,  0.f, -1.f);
    VERTEX(buffer, index, x        , y + sizey, z        ); VERTEX(buffer, index,  0.f,  0.f, -1.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z        ); VERTEX(buffer, index,  0.f,  0.f, -1.f);
    VERTEX(buffer, index, x + sizex, y        , z        ); VERTEX(buffer, index,  0.f,  0.f, -1.f);

    VERTEX(buffer, index, x        , y        , z + sizez); VERTEX(buffer, index,  0.f,  0.f,  1.f);
    VERTEX(buffer, index, x        , y + sizey, z + sizez); VERTEX(buffer, index,  0.f,  0.f,  1.f);
    VERTEX(buffer, index, x + sizex, y        , z + sizez); VERTEX(buffer, index,  0.f,  0.f,  1.f);
    VERTEX(buffer, index, x        , y + sizey, z + sizez); VERTEX(buffer, index,  0.f,  0.f,  1.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z + sizez); VERTEX(buffer, index,  0.f,  0.f,  1.f);
    VERTEX(buffer, index, x + sizex, y        , z + sizez); VERTEX(buffer, index,  0.f,  0.f,  1.f);

    VERTEX(buffer, index, x        , y        , z        ); VERTEX(buffer, index,  0.f, -1.f,  0.f);
    VERTEX(buffer, index, x        , y        , z + sizez); VERTEX(buffer, index,  0.f, -1.f,  0.f);
    VERTEX(buffer, index, x + sizex, y        , z        ); VERTEX(buffer, index,  0.f, -1.f,  0.f);
    VERTEX(buffer, index, x        , y        , z + sizez); VERTEX(buffer, index,  0.f, -1.f,  0.f);
    VERTEX(buffer, index, x + sizex, y        , z        ); VERTEX(buffer, index,  0.f, -1.f,  0.f);
    VERTEX(buffer, index, x + sizex, y        , z + sizez); VERTEX(buffer, index,  0.f, -1.f,  0.f);

    VERTEX(buffer, index, x        , y + sizey, z        ); VERTEX(buffer, index,  0.f,  1.f,  0.f);
    VERTEX(buffer, index, x        , y + sizey, z + sizez); VERTEX(buffer, index,  0.f,  1.f,  0.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z        ); VERTEX(buffer, index,  0.f,  1.f,  0.f);
    VERTEX(buffer, index, x        , y + sizey, z + sizez); VERTEX(buffer, index,  0.f,  1.f,  0.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z        ); VERTEX(buffer, index,  0.f,  1.f,  0.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z + sizez); VERTEX(buffer, index,  0.f,  1.f,  0.f);

    VERTEX(buffer, index, x        , y        , z        ); VERTEX(buffer, index, -1.f,  0.f,  0.f);
    VERTEX(buffer, index, x        , y + sizey, z        ); VERTEX(buffer, index, -1.f,  0.f,  0.f);
    VERTEX(buffer, index, x        , y        , z + sizez); VERTEX(buffer, index, -1.f,  0.f,  0.f);
    VERTEX(buffer, index, x        , y        , z + sizez); VERTEX(buffer, index, -1.f,  0.f,  0.f);
    VERTEX(buffer, index, x        , y + sizey, z        ); VERTEX(buffer, index, -1.f,  0.f,  0.f);
    VERTEX(buffer, index, x        , y + sizey, z + sizez); VERTEX(buffer, index, -1.f,  0.f,  0.f);

    VERTEX(buffer, index, x + sizex, y        , z        ); VERTEX(buffer, index,  1.f,  0.f,  0.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z        ); VERTEX(buffer, index,  1.f,  0.f,  0.f);
    VERTEX(buffer, index, x + sizex, y        , z + sizez); VERTEX(buffer, index,  1.f,  0.f,  0.f);
    VERTEX(buffer, index, x + sizex, y        , z + sizez); VERTEX(buffer, index,  1.f,  0.f,  0.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z        ); VERTEX(buffer, index,  1.f,  0.f,  0.f);
    VERTEX(buffer, index, x + sizex, y + sizey, z + sizez); VERTEX(buffer, index,  1.f,  0.f,  0.f);
    print_log(CONSOLE, "index = %d\n", index);
    for(int i = 0; i < data_repn.size_buffer; ++i){
        print_log(CONSOLE, "%f ", buffer[i]);
    }
    print_log(CONSOLE, "\n");
}
void GeometryCubeT2::generate_normales(){
    float *buffer = data_repn.buffer + data_repn.size_vertices;
    float normales[] = {
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 
    0.0f,  0.0f, -1.0f, 

    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,
    0.0f,  0.0f, 1.0f,

    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,

    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,

    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,

    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f
    };
    memcpy(buffer, normales, sizeof(normales));
    print_log(CONSOLE, "size norm = %d", sizeof(normales) / sizeof(float));
    for(int i = 0; i < data_repn.size_norm; ++i){
        print_log(CONSOLE, "%f ", buffer[i]);
    }
    print_log(CONSOLE, "\n");

}

void GeometryCubeT2::rotate(float angle, glm::vec3 xyz){
    data_repn.model = glm::rotate(data_repn.model, glm::radians(angle), xyz);
}