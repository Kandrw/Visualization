#include <iostream>
#include <cstdlib>
#define VERTEX(index, x, y, z) \
        buffer[index] = x; \
        buffer[index + 1] = y; \
        buffer[index + 2] = (float)z / 200.f; \
        index+=3;

#define RANDOM_SIZE (((float)rand() / RAND_MAX)) + 0.01f

//#define RANDOM_SIZE 6.6

#define RU 3.3
#define RD 4.4
#define LD 5.5
#define RD2 6.6

float *read_bin_type_float(std::string fname, int N);
int *read_bin_type_int(std::string fname, int N);


int main(){

    int N = 5;
    int count_vert = N * N;
    float px = 0.0, py = 0.0, pz = 0.0;
    float step = 0.1;
    //float 
    int size_buf = (N-1) * (N-1) * (3 * 3 * 2);
    std::cout<<"size_buf = "<<size_buf<<"\n";
    float *buffer = new float[size_buf];
    for(int i = 0; i < size_buf; ++i){
        buffer[i] = 9.9f;
    }
    int x, y, z;
    int con = 0;
    int index = 0;
    int c_treg = 0;
    float new_rand;
    std::string fname_heights = "../res/data/heights.bin";
    int *data = read_bin_type_int(fname_heights, 25);
    //float *data = new float[25];
    for(int i = 0; i < 25; ++i){
        //data[i] = RANDOM_SIZE;
        std::cout<<data[i]<<" ";
    }

    std::cout<<"\n";
    for(y = 0; y < N - 1; ++y){
        px = 0.0;
        for(x = 0; x < N - 1; ++x){

            
            std::cout<<"y = "<<y<<"  x = "<<x<<"  ";
            //printf("[ < %2.1f %2.1f | %2.1f %2.1f | %2.1f %2.1f > ", py, px, py, px + step, py+step, px+step );
            VERTEX(index, py, px, *(data + y * N + x));
            VERTEX(index, py, px + step, *(data + y * N + x + 1));
            VERTEX(index, py + step, px + step, *(data + (y + 1) * N + x + 1));
            //index += 9;

            //printf("< %2.1f %2.1f | %2.1f %2.1f | %2.1f %2.1f > ] ", py, px, py+step, px, py+step, px+step );
            //index += 9;
            VERTEX(index, py, px, *(data + y * N + x));
            VERTEX(index, py + step, px, *(data + (y + 1) * N + x));
            VERTEX(index, py + step, px + step, *(data + (y + 1) * N + x + 1));
            c_treg += 2;
            px += step;
        }
        std::cout<<"\n\n";
        py += step;
    }
    for(int i = 0; i < size_buf; ++i){
        printf("%2.2f ", buffer[i]);
        if((i+1) % 18 == 0){
            std::cout<<"\n";
        }
    }
    std::cout<<"\n";
    
    std::cout<<"index = "<<index<<"  c_treg = "<<c_treg<<"\n";
    delete[] buffer;
    std::cout<<"END\n";
    return 0;
}


float *read_bin_type_float(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        std::cout<<"[Error load] not found - "<<fname<<"\n";
        return nullptr;
    }
    float *array = new float[N];
    int size = fread(array, sizeof(float), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        std::cout<<"[Error read] reading data<"<<fname<<"> error: N = "<<N<<", read(data) = "<<size<<"\n";
        return nullptr;
    }
    fclose(filew);
    return array;
}

int *read_bin_type_int(std::string fname, int N){
    FILE *filew = fopen(fname.c_str(), "rb");
    if(!filew){
        std::cout<<"[Error load] not found - "<<fname<<"\n";
        return nullptr;
    }
    int *array = new int[N];
    int size = fread(array, sizeof(int), N, filew);
    if(size != N){
        delete[] array;
        fclose(filew);
        std::cout<<"[Error read] reading data<"<<fname<<"> error: N = "<<N<<", read(data) = "<<size<<"\n";
        return nullptr;
    }
    fclose(filew);
    return array;
}

