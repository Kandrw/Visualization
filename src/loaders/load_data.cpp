#include "load_data.hpp"

#include <fstream>


#include "../output/output.hpp"




int *read_bin_type_int(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        output<<"[Error load] not found - "<<fname<<"\n";
        return nullptr;
    }
    int *array = new int[N];
    int size = fread(array, sizeof(int), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        output<<"[Error read] reading data<"<<fname<<"> error: N = "<<N<<", read(data) = "<<size<<"\n";
        return nullptr;
    }
    fclose(filew);
    return array;
}

double *read_bin_type_double(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        output<<"[Error load] not found - "<<fname<<"\n";
        return nullptr;
    }
    double *array = new double[N];
    int size = fread(array, sizeof(double), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        output<<"[Error read] reading data<"<<fname<<"> error: N = "<<N<<", read(data) = "<<size<<"\n";
        return nullptr;
    }
    fclose(filew);
    return array;
}
float *read_bin_type_float(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        output<<"[Error load] not found - "<<fname<<"\n";
        return nullptr;
    }
    float *array = new float[N];
    int size = fread(array, sizeof(float), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        output<<"[Error read] reading data<"<<fname<<"> error: N = "<<N<<", read(data) = "<<size<<"\n";
        return nullptr;
    }
    fclose(filew);
    return array;
}