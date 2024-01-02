#include "geometry_point.hpp"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../output/output.hpp"
#include "../shaders/shader.hpp"

float color3d[18] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.6f,
        0.0f, 0.1f, 0.6f,
        0.0f, 0.1f, 0.6f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.6f,
};
float color1d[18] = {
        0.1f, 0.1f, 0.1f,
        0.1f, 0.6f, 0.1f,
        0.1f, 0.6f, 0.1f,
        0.1f, 0.6f, 0.1f,
        0.1f, 0.1f, 0.1f,
        0.1f, 0.6f, 0.1f,
};


float distance_points(float x1, float y1, float x2, float y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

GeometryPoint::GeometryPoint(){
    this->load_shader();
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    generate_vertices();
    render();

}

GeometryPoint::~GeometryPoint(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if(shader)
        delete shader;
}
bool GeometryPoint::load_shader(){
    std::string frag = "res/shaders/geometry_point/frag.glsl";
    std::string vert = "res/shaders/geometry_point/vert.glsl";
    shader = load_Shader(frag, vert);
    if(!shader)
        return false;
    return true;
}
void GeometryPoint::render(){
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
void GeometryPoint::draw(){
    shader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void GeometryPoint::join_data(){
    int i, i2;
    for(i = 0; i < sizeof(vertices)/4; ++i){
       data[i] = vertices[i];
    }
    for(i2 = 0; i2 < sizeof(color)/4; ++i2, ++i){
        data[i] = color[i2];
    }    
}

void GeometryPoint::set_position(float dx, float dy){
    this->x += dx;
    this->y += dy;
}
void GeometryPoint::set_color(float *col, int N){
    for(int i = 0; i < N; ++i){
        this->color[i] = col[i];
    }
}
void GeometryPoint::generate_vertices(){
    vertices[0] = x; vertices[1] = y;
    vertices[3] = x; vertices[4] = y + sizey;
    vertices[6] = x + sizex; vertices[7] = y;
    vertices[9] = x; vertices[10] = y + sizey;
    vertices[12] = x + sizex; vertices[13] = y + sizey;
    vertices[15] = x + sizex; vertices[16] = y;
    //color[0] = x; color[1] = y;
}

void GeometryPoint::set_size(float dx, float dy){
    this->sizex = dx;
    this->sizey = dy;
}

float GeometryPoint::get_posx(){
    return x;
}
float GeometryPoint::get_posy(){
    return y;
}
float GeometryPoint::distance_point(GeometryPoint *point){
    return distance_points(x, y, point->get_posx(), point->get_posy());
}

void interaction_of_objects(GeometryPoint *points, int N){
    for(int i = 1; i < N; ++i){

        float min_dist_n = 1.0f;
        float min_dist_g = 1.0f;
        float min_dist_b = 1.0f;
        
            
        int index_n, index_g, index_b;

        for(int i2 = 0; i2 < N; ++i2){
                if(i != i2){
                    if(points[i2].type == 'n'){
                        float dist = points[i].distance_point(&points[i2]);
                        if(dist < min_dist_n){
                            min_dist_n = dist;
                            index_n = i2;
                        }
                    }
                    else if(points[i2].type == 'g'){
                        float dist = points[i].distance_point(&points[i2]);
                        if(dist < min_dist_g){
                            min_dist_g = dist;
                            index_g = i2;
                        }
                    }
                    else if(points[i2].type == 'b'){
                        float dist = points[i].distance_point(&points[i2]);
                        if(dist < min_dist_b){
                            min_dist_b = dist;
                            index_b = i2;
                        }
                    }
                    
                }
        }
        if(min_dist_n >= 0.2f){
            //min_dist_n = 0.0f;
        }
        if(min_dist_g >= 0.4f){
           // min_dist_g = 0.0f;
        }
        //if(min_dist_n < 0.0f && )
        
        if(points[i].type == 'n'){
            float new_pos = (points[i].speed - min_dist_n)/100.0f;
            points[i].set_position( 
points[i].get_posx() > points[index_n].get_posx()? new_pos : -1.0f * new_pos, 
points[i].get_posy() > points[index_n].get_posy()? new_pos : -1.0f * new_pos
            );
            new_pos = (points[i].speed - min_dist_g)/100.0f;
            if(new_pos < 0.0004f){
points[i].set_position( 
points[i].get_posx() > points[index_g].get_posx()? new_pos : -1.0f * new_pos, 
points[i].get_posy() > points[index_g].get_posy()? new_pos : -1.0f * new_pos
                );
            }
            else{
                points[i].set_position( 
points[i].get_posx() > points[index_g].get_posx()? -1.0f * new_pos : new_pos, 
points[i].get_posy() > points[index_g].get_posy()? -1.0f * new_pos : new_pos
                );
            }
            
        }
        else if(points[i].type == 'g'){
            float new_pos = (points[i].speed - min_dist_n)/100.0f;
            points[i].set_position( 
    points[i].get_posx() > points[index_n].get_posx()? new_pos : -1.0f * new_pos, 
    points[i].get_posy() > points[index_n].get_posy()? new_pos : -1.0f * new_pos
            );
            new_pos = (points[i].speed - min_dist_g)/100.0f;
            points[i].set_position( 
    points[i].get_posx() > points[index_g].get_posx()? new_pos : -1.0f * new_pos, 
    points[i].get_posy() > points[index_g].get_posy()? new_pos : -1.0f * new_pos
            );
            new_pos = (points[i].speed - min_dist_b)/100.0f;
            points[i].set_position( 
    points[i].get_posx() > points[index_b].get_posx()? new_pos : -1.0f * new_pos, 
    points[i].get_posy() > points[index_b].get_posy()? new_pos : -1.0f * new_pos
            );
            
        }
        


        else if(points[i].type == 'b'){
            float new_pos = (points[i].speed - min_dist_n)/100.0f;
            points[i].set_position( 
    points[i].get_posx() > points[index_n].get_posx()? -1.0f * new_pos : new_pos, 
    points[i].get_posy() > points[index_n].get_posy()? -1.0f * new_pos : new_pos
            );
            if(min_dist_g <= 0.03){
                points[index_g].type = 'b';
                points[index_g].set_color(color3d, 18);

            }
            new_pos = (points[i].speed - min_dist_g)/100.0f;
            points[i].set_position( 
    points[i].get_posx() > points[index_g].get_posx()? -1.0f * new_pos : new_pos, 
    points[i].get_posy() > points[index_g].get_posy()? -1.0f * new_pos : new_pos
            );
            if(min_dist_b <= 0.15){
                points[index_g].type = 'g';
                points[index_g].set_color(color1d, 18);
            }
            new_pos = (points[i].speed - min_dist_b)/50.0f;
            points[i].set_position( 
    points[i].get_posx() > points[index_b].get_posx()? new_pos : -1.0f * new_pos, 
    points[i].get_posy() > points[index_b].get_posy()? new_pos : -1.0f * new_pos
            );

        }
        if(points[i].get_posx() >= 0.99){
                    points[i].set_position(-0.01 , 0);
        }
        else if(points[i].get_posx() <= -0.99){
                    points[i].set_position(0.01 , 0);
        }
        if(points[i].get_posy() >= 0.99){
                    points[i].set_position(0, -0.01);
        }
        else if(points[i].get_posy() <= -0.99){
                    points[i].set_position(0, 0.01);
        }

        points[i].render();
    }
}

//Отключена в шейдере
/*
void GeometryPoint::rotate(glm::mat4 mat_rotate){
    GLuint transformLoc = glGetUniformLocation(shader->id(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mat_rotate));
}
*/



