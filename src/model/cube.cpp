#include "cube.hpp"

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





Cube::Cube(float posx, float posy, float posz) : posx(posx), posy(posy), posz(posz){
    output<<"[|] x = "<<posx<<"  y = "<<posy<<"  z = "<<posz<<"\n";
}

GeometryCube::GeometryCube(Cube *cube) : cube(cube){
    output<<"[GeometryCube] initialization...\n";
    load_shader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    render();
    output<<"[GeometryCube] initialization\n";
}
GeometryCube::~GeometryCube(){
    delete shader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete cube;
}

bool GeometryCube::load_shader(){
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}
void GeometryCube::generate_vertices(){
    float x = cube->posx, y = cube->posy, z = cube->posz;
    float sizex = cube->sizex, sizey = cube->sizey, sizez = cube->sizez;
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


void GeometryCube::render(){
    generate_vertices();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_buffer * sizeof(float), buffer, GL_STATIC_DRAW);
    //позиция в шейдере, размер аргумента в шейдере, тип, нормализация(вкл\выкл), шаг между данными, начало данных
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GeometryCube::draw(){
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, size_buffer);
    glBindVertexArray(0);
}
void GeometryCube::load_model_matrix(glm::mat4 view, glm::mat4 projection, glm::mat4 model){
    shader->use();
    GLuint viewLoc = glGetUniformLocation(shader->id(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projectionLoc = glGetUniformLocation(shader->id(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    GLuint modelLoc = glGetUniformLocation(shader->id(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void move(){
    
}




