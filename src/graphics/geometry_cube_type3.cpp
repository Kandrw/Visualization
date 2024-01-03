#include "geometry_cube_type3.hpp"

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
#include "../graphics/geometry_line.hpp"

#define VERTEX(buffer, index, x, y, z)\
    buffer[index] = x;\
    buffer[index+1] = y;\
    buffer[index+2] = z;\
    index += 3;
GeometryCubeT3::GeometryCubeT3(float *pos_size_rgb, int id){
    memset((void*)&data_repn, 0, sizeof(data_repn));
    
    data_repn.id = id;
    print_log(CONSOLE, "[GeometryCubeT3 initialization...\n");
    memcpy((void*)data_repn.pos_size_rgb, (void*)pos_size_rgb, 9 * sizeof(float));
    data_repn.size_vertices = 3 * 3 * 2 * 6;
    data_repn.size_norm = data_repn.size_vertices;
    data_repn.size_buffer = data_repn.size_vertices + data_repn.size_norm;
    data_repn.buffer = new float[data_repn.size_buffer];
    data_repn.model = glm::mat4(1.0f);

    //data_repn.pos = glm::vec3(pos_size_rgb[0], pos_size_rgb[1], pos_size_rgb[2]);
    data_repn.pos = glm::vec3(0.f, 0.f, 0.f);
    data_repn.direction = glm::vec3(1.f, 0.f, 0.f);
    data_repn.speed = 0.2f;
    data_repn.angle = 10.f;
    

    generate_vertices_normales();
    load_shader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    render();

    //line = new GeometryLine(glm::vec3(1.f, 1.f, 0.f), 10.f, glm::vec3(0.f, 1.f, 0.f));
    line = new GeometryLine(glm::vec3(0.f, 1.f, 0.f), 10.f, data_repn.direction);
    
    print_log(CONSOLE, "[GeometryCubeT3 initialization\n");
}
GeometryCubeT3::~GeometryCubeT3(){
    delete[] data_repn.buffer;
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
bool GeometryCubeT3::load_shader(){
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}
void GeometryCubeT3::draw(){

    
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, data_repn.size_vertices);
    glBindVertexArray(0);

    
    
}
void GeometryCubeT3::load_model_matrix(glm::mat4 view_camera, glm::mat4 projection){

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
void GeometryCubeT3::Line_load_matrix_draw(glm::mat4 view_camera, glm::mat4 projection){
    line->load_model_matrix(view_camera, projection);
    line->draw();
}

void GeometryCubeT3::render(){

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
void GeometryCubeT3::setLightColorPos(glm::vec3 pos, glm::vec3 color){
    shader->use();
    GLuint posLoc = glGetUniformLocation(shader->id(), "lightPos");
    glUniform3fv(posLoc, 1, glm::value_ptr(pos));
    GLuint colorLoc = glGetUniformLocation(shader->id(), "lightColor");
    glUniform3fv(colorLoc, 1, glm::value_ptr(color));

}
void GeometryCubeT3::set_color(float rgb[3]){
    memcpy((char*)data_repn.pos_size_rgb+6, (char*)rgb, 3 * sizeof(float));
    shader->use();
    GLuint colorLoc = glGetUniformLocation(shader->id(), "color_obj");
    glUniform3fv(colorLoc, 1, data_repn.pos_size_rgb + 6);
}
void GeometryCubeT3::generate_vertices_normales(){
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

void GeometryCubeT3::rotate(float angle, glm::vec3 xyz){
    data_repn.model = glm::rotate(data_repn.model, glm::radians(angle), xyz);
}
int GeometryCubeT3::get_id(){
    return data_repn.id;
}

void GeometryCubeT3::control(){
    if(Window::pressed(GLFW_KEY_W)){
        data_repn.pos += data_repn.direction * data_repn.speed;
    }
    if(Window::pressed(GLFW_KEY_S)){
        data_repn.pos -= data_repn.direction * data_repn.speed;
    }
    if(Window::pressed(GLFW_KEY_A)){
        data_repn.direction = glm::rotate(data_repn.direction, glm::radians(data_repn.angle), glm::vec3(0.f, 1.f, 0.f));
        line->rotate(data_repn.angle, glm::vec3(0.f, 1.f, 0.f));
    }
    
    if(Window::pressed(GLFW_KEY_D)){
        data_repn.direction = glm::rotate(data_repn.direction, glm::radians(data_repn.angle * -1.f), glm::vec3(0.f, 1.f, 0.f));
        line->rotate(data_repn.angle * -1.f, glm::vec3(0.f, 1.f, 0.f));
    }
}
void GeometryCubeT3::_move(){
    
}


