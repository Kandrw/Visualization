#include <iostream>
#include <cstdlib>

#include <ctime>

#define RANDOM_POS ((float)rand() / RAND_MAX) - ( (float)rand() / RAND_MAX )
#define RANDOM_SIZE (((float)rand() / RAND_MAX) / 10.0f) + 0.01f

void test_RANDOM_POS(){
    float r;
    std::cout<<"RAND_MAX = "<<RAND_MAX<<"\n";
    float min = 1.0f;
    float max = -1.0f;
    for(int i = 0; i < 3000000; ++i){
        r = ((float)rand() / RAND_MAX) - ( (float)rand() / RAND_MAX ) ; 
        //r *= 0.5f;
        if(r < min){
            min = r;
        }
        if(r > max){
            max = r;
        }
        //std::cout<<r<<"\n";
    }
    std::cout<<"min = "<<min<<"\n";
    std::cout<<"max = "<<max<<"\n";
}

int main(){
    srand(time(NULL));
    float r;
    std::cout<<"RAND_MAX = "<<RAND_MAX<<"\n";
    float min = 1.0f;
    float max = -1.0f;
    for(int i = 0; i < 30; ++i){
        r = (((float)rand() / RAND_MAX) / 10.0f) + 0.05f ; 
        //r *= 0.5f;
        if(r < min){
            min = r;
        }
        if(r > max){
            max = r;
        }
        std::cout<<r<<"\n";
    }
    std::cout<<"min = "<<min<<"\n";
    std::cout<<"max = "<<max<<"\n";
    
    
}







