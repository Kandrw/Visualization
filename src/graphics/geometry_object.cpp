#include "geometry_object.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "../output/output.hpp"
#include "../shaders/shader.hpp"

GeometryObj::GeometryObj(){
    bool init = true;
    if(!load_shader()){
        init = false;
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    render();
    if(!init)
        output<<"[GeometryObj]: failed init\n";
    else
        output<<"[GeometryObj]: Init Geometry object\n";
}
GeometryObj::~GeometryObj(){
    if(shader){
        delete shader;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}



int GeometryObj::get_N(){
    return N;
}
void GeometryObj::set_N(int N){
    this->N = N;
}

bool GeometryObj::load_shader(){
    std::string frag = "res/shaders/geometry_obj/fragment.glsl";
    std::string vert = "res/shaders/geometry_obj/vertex.glsl";
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}
void GeometryObj::join_data(){
    int i, i2;
    for(i = 0; i < sizeof(vertices)/4; ++i){
       data[i] = vertices[i];
    }
    for(i2 = 0; i2 < sizeof(color)/4; ++i2, ++i){
        data[i] = color[i2];
    }    
}
void GeometryObj::generate_vertices(){
    vertices[0] = x; vertices[1] = y; vertices[2] = z;
    vertices[3] = x; vertices[4] = y + sizey; vertices[5] = z;
    vertices[6] = x + sizex; vertices[7] = y; vertices[8] = z;
    vertices[9] = x; vertices[10] = y + sizey; vertices[11] = z;
    vertices[12] = x + sizex; vertices[13] = y + sizey; vertices[14] = z;
    vertices[15] = x + sizex; vertices[16] = y; vertices[17] = z;
}

void GeometryObj::render(){
    generate_vertices();
    join_data();
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    //output << "sizeof(vertices) = "<<sizeof(data)<<"\n";
    //позиция в шейдере, размер аргумента в шейдере, тип, нормализация(вкл\выкл), шаг между данными, начало данных
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)sizeof(vertices));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0); // Unbind VAO
    //output<<"Render\n";
}

void GeometryObj::draw(){
    shader->use();
    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
//Не рабочий
void GeometryObj::rotate(glm::mat4 mat_rotate){
    GLuint transformLoc = glGetUniformLocation(shader->id(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mat_rotate));
}
void GeometryObj::set_position(float dx, float dy){
    this->x += dx;
    //this->z += dx;
    
    this->y += dy;

}
void GeometryObj::load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model){
    shader->use();
    GLuint viewLoc = glGetUniformLocation(shader->id(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projectionLoc = glGetUniformLocation(shader->id(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    GLuint modelLoc = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}