#include "geometry_line.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../output/output.hpp"
#include "../shaders/shader.hpp"
#include "../window/window.hpp"



GeometryLine::GeometryLine(glm::vec3 pos, float size, glm::vec3 norm){
    
    print_log(CONSOLE, "[GeometryLine initialization...]\n");
    memset((void*)&data_repn, 0, sizeof(data_repn));
    //data_repn.pos = pos;
    data_repn.model = glm::mat4(1.0f);
    data_repn.size_buffer = 6;
    data_repn.buffer = new float[data_repn.size_buffer];
    //data_repn.buffer[0] = pos.x;
    memcpy(data_repn.buffer, (void*)&pos, 3 * sizeof(float));
    norm = norm * size;
    memcpy(data_repn.buffer + 3, (void*)&norm, 3 * sizeof(float));
    for(int i = 0; i < 6; ++i){
       print_log(CONSOLE, "%f  ", data_repn.buffer[i]);
    }
    print_log(CONSOLE, "\n");
    load_shader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    render();
    print_log(CONSOLE, "[GeometryLine initialization]\n");
}
GeometryLine::~GeometryLine(){
    delete[] data_repn.buffer;
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void GeometryLine::render(){
    shader->use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data_repn.size_buffer * sizeof(float), data_repn.buffer, GL_STATIC_DRAW);
    //позиция в шейдере, размер аргумента в шейдере, тип, нормализация(вкл\выкл), шаг между данными, начало данных
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
}

bool GeometryLine::load_shader(){
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}
void GeometryLine::draw(){
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}
void GeometryLine::load_model_matrix(glm::mat4 view_camera, glm::mat4 projection){

    glm::mat4 view = glm::translate(view_camera, data_repn.pos);
    //glm::mat4 model = glm::translate(data_repn.model, data_repn.pos);
    glm::mat4 model = data_repn.model;
    //glm::mat4 view = view_camera;
    
    shader->use();
    GLuint viewLoc = glGetUniformLocation(shader->id(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projectionLoc = glGetUniformLocation(shader->id(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    GLuint modelLoc = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}
void GeometryLine::rotate(float angle, glm::vec3 xyz){
    data_repn.model = glm::rotate(data_repn.model, glm::radians(angle), xyz);
}