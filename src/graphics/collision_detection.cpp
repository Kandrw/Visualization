#include "collision_detection.hpp"

#include <vector>

#include "../output/output.hpp"






Collision_detection::Collision_detection(){
    output<<"[INIT Collision_detection]\n";

}

int Collision_detection::add_object(Data_object *object){
    list.push_back(object);
}

float Collision_detection::detection(int id, float x, float y, float z){
    for(int i = 0; i < list.size(); ++i){
        if(id != list[i]->id){
            
        }
    }
}















