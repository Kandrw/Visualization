#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/ext.hpp>

int distance_points(int x1, int y1, int x2, int y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
float distance_points(float x1, float y1, float x2, float y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}



int main(){
    //std::cout<<distance_points(0.1f, 0.1f, -0.1f, -0.1f);
    //glm::mat4 model = glm::mat4(1.0f);
    //std::cout<<model[1][4];
    //float 
    glm::vec3 norm = glm::vec3(1.f, 0.f, 0.f);
    std::cout<<"xyz: "<<norm.x<<" "<<norm.y<<" "<<norm.z<<"\n";
    //glm::mat4 rotation = glm::mat4(1.f);
    //rotation = glm::rotate(rotation, (float)glm::radians(45), glm::vec3(1,0,0));
    norm = glm::rotate(norm, (float)glm::radians(45.f), glm::vec3(0,1,0));
    std::cout<<"xyz90: "<<norm.x<<" "<<norm.y<<" "<<norm.z<<"\n";
    float speed = 4;
    glm::vec3 dpos = norm * speed;
    std::cout<<"dpos: "<<dpos.x<<" "<<dpos.y<<" "<<dpos.z<<"\n";
    std::cout<<"rad = "<<glm::radians(45.f)<<"\n";
    //glm::rotate(norm, 34);
    glm::vec3 pos = glm::vec3(20, 20, 20);
    std::cout<<"pos: "<<pos.x<<" "<<pos.y<<" "<<pos.z<<"\n";
    pos += dpos;
    std::cout<<"newpos: "<<pos.x<<" "<<pos.y<<" "<<pos.z<<"\n";
}
















