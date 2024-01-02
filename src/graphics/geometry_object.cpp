#include "geometry_object.hpp"

#include <iostream>

#include "../output/output.hpp"
#include "../loaders/load_data.hpp"
#include "../shaders/shader.hpp"

GeometryObj::GeometryObj(){
    bool init = true;
    if(!load_data()){
        init = false;
    }
    if(!load_shader()){
        init = false;
    }
    if(!init)
        output<<"[GeometryObj]: failed init\n";
    else
        output<<"[GeometryObj]: Init Geometry object\n";
}
GeometryObj::~GeometryObj(){
    if(array_heights){
        delete[] array_heights;
    }
    if(array_lats){
        delete[] array_lats;
    }
    if(array_lons){
        delete[] array_lons;
    }
    if(shader){
        delete shader;
    }

    buffer = new float[100 * 6];

}

bool GeometryObj::load_data(){
    std::string fname_heights = "res/data/heights.bin";
    std::string fname_lats= "res/data/lats.bin";
    std::string fname_lons = "res/data/lons.bin";
    set_N(100);
    array_heights = read_bin_type_int(fname_heights, get_N());
    if(!array_heights){
        return false;
    }
    array_lats = read_bin_type_float(fname_lats, get_N());
    if(!array_lats){
        return false;
    }
    array_lons = read_bin_type_float(fname_lons, get_N());
    if(!array_lons){
        return false;
    }
    output<<"[GeometryObj]: load data, N = "<<N<<"\n";
    return true;
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


void GeometryObj::render(){
    int i, i2, i3;
    int X = 10, Y = 10;
    int index = 0;
    float step = 0.1;
    float iter = 0.0;
    for(i = 0; i < Y-1; ++i){
        for(i2 = 0; i2 < X-1; ++i2){
            buffer[index++] = iter;
            buffer[index++] = iter;
            buffer[index++] = iter;
            
        }
    }
}




