#include <iostream>
#include <sstream>

#define OUTPUT1(input) (str1<< input)
#define OUTPUT str1


class Output{
    static std::stringstream buffer;

};


int sum(int n, ...){

}
template<typename T> int test_args_template(std::stringstream *str1, T t, ... ){

}

template<typename T> void operator << (std::stringstream *output, T t ){
    std::cout<< type_info(t)<<"s444444444444\n";
    output << t<<"fff";
}

void operator << (std::stringstream *output, Output t ){
    //output << t;


}




int test1(){
    std::stringstream str1;
    std::cout.precision(10);
    str1.precision(20);
    //str1.
    //str1.eof()
    str1 << 345 << " fasgf"<<4645.3456245<<" sdf";
    OUTPUT1("\nend" << " - no end\n" << 5345);
    std::string sb;
    //str1>>sb;
    sb = str1.str();
    std::cout<<sb<<"\n";
    std::cout<<"============\n";
    str1<<"sfsf245624562456";
    sb = str1.str();
    std::cout<<sb<<"\n";
    return 0;
}
int test2(){
    
}



int main(){
    test1();
    std::cout<<"End program\n";
}
