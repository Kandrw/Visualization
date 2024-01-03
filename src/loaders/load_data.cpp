#include "load_data.hpp"

#include <fstream>


#include "../output/output.hpp"




int *read_bin_type_int(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        print_log(CONSOLE, "[Error load] not found - %s\n", fname);
        return nullptr;
    }
    int *array = new int[N];
    int size = fread(array, sizeof(int), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        print_log(CONSOLE, "[Error read] reading data <%s> error: N = %d, read(data) = %d\n", fname.c_str(), N, size);
        return nullptr;
    }
    fclose(filew);
    return array;
}

double *read_bin_type_double(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        print_log(CONSOLE, "[Error load] not found - %s\n", fname.c_str());
        return nullptr;
    }
    double *array = new double[N];
    int size = fread(array, sizeof(double), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        //output<<"[Error read] reading data<"<<fname<<"> error: N = "<<N<<", read(data) = "<<size<<"\n";
        print_log(CONSOLE, "[Error read] reading data <%s> error: N = %d, read(data) = %d\n", fname.c_str(), N, size);
        return nullptr;
    }
    fclose(filew);
    return array;
}
float *read_bin_type_float(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        //output<<"[Error load] not found - "<<fname<<"\n";
        print_log(CONSOLE, "[Error load] not found - %s\n", fname.c_str());
        return nullptr;
    }
    float *array = new float[N];
    int size = fread(array, sizeof(float), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        //output<<"[Error read] reading data<"<<fname<<"> error: N = "<<N<<", read(data) = "<<size<<"\n";
        print_log(CONSOLE, "[Error read] reading data <%s> error: N = %d, read(data) = %d\n", fname.c_str(), N, size);
        return nullptr;
    }
    fclose(filew);
    return array;
}