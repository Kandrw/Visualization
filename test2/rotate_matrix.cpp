#include <iostream>

#include <cmath>

#include <glm/glm.hpp>


#define PI 3.14159265358979323846
void rotate(float *vert, float *mat, int N){
    for(int i = 0; i < N; ++i){
        //std::cout<<"i*N = "<< i *N <<"\n";
        *(vert + i * N) = *(vert + i * N) * mat[0] + *(vert + i * N + 1) * mat[2];
        *(vert + i * N + 1) = *(vert + i * N) * mat[1] + *(vert + i * N + 1) * mat[3];
        
    }
}
void print_m(float *vert, int N){
    for(int i = 0; i < N; ++i){
        for(int i2 = 0; i2 < N; ++i2){
            std::cout << *(vert + i * N + i2)<<" ";
        }
        std::cout<<"\n";
    }
}

int main(){
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[1][1];
    for(int i = 0; i < 4; ++i){
        for(int i2 = 0; i2 < 4; ++i2){
            std::cout<<rotation[i][i2]<<" ";
        }
        std::cout<<"\n";
    }
    
    float vertices[9] = {
        0.2f,  0.2f, 0.0f,
       -0.2f,  0.2f, 0.0f,
       -0.2f, -0.2f, 0.0f,
    };
    //print_m(vertices, 3);
    //float q = -90.0; 

    //float matrix[4] = { cosf(q), -1.0f * sinf(q), sinf(q), cosf(q)};
    //rotate(vertices, matrix, 3);
    //print_m(vertices, 3);

    
    
}
