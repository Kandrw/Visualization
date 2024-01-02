#include <iostream>
#include <sstream>
#include <typeinfo>


#define OUTPUT1(input) (str1<< input)
#define OUTPUT str1


class Output{
public:
    int A = 23;
    static std::stringstream buffer;
    void print(){
        std::cout<<buffer.str()<<"\n";
        //buffer.clear();
        buffer.str("");
    }
};

std::stringstream Output::buffer;
int sum(int n, ...){

}
template<typename T> int test_args_template(std::stringstream *str1, T t, ... ){

}
/*
template<typename T> Output operator << (Output output, T t ){
    //std::cout<< type_info(t)<<"\n";
    std::cout<<"<sdf1>\n";
    //std::cout<<typeid(t).name()<<"\n";
    //Output::buffer << t;
    output.buffer<<t;
    output.A = 234;
    return output;
}
*/
/*
template<typename T> Output * operator << (Output &output, T t ){
    //std::cout<< type_info(t)<<"33\n";
    //std::cout<<(char)typeid(t).name()<<"\n";
    std::cout<<"<sdf>";
    //Output::buffer << t;
    output->buffer<<t;
    return output;
}
*/

template<typename T> Output& operator << (Output &output, T t){
    //std::cout<< type_info(t)<<"33\n";
    //std::cout<<(char)typeid(t).name()<<"\n";
    std::cout<<"<sdf>";
    //Output::buffer << t;
    output.buffer<<t;
    output.A = -345;
    return output;
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
    Output out, *ptr;
    std::cout<<"A1 = "<<out.A<<"\n";
    ptr = &out;
    out<<" AAAA - " << 1;
    ptr->print();
    *ptr<<" BBBB - " << 2;
    ptr->print();
    std::cout<<"A1 = "<<out.A<<"\n";
}

int main(){
    test2();
    std::cout<<"End program\n";
}
