#include <iostream>
#include <sstream>
#include <typeinfo>


#define OUTPUT1(input) (str1<< input)
#define OUTPUT str1


class Output{
public:
    static std::stringstream buffer;
    void print(){
        std::cout<<buffer.str();
        
    }
    void clear(){
        buffer.str("");
    }
};

std::stringstream Output::buffer;
template<typename T> Output& operator << (Output &output, T t);




int test2(){
    Output out, *ptr;
    ptr = &out;
    out<<"AAAA - " << 1 <<"\n";
    //ptr->print();
    *ptr<<" BBBB - " << 2 << "\n";
    //ptr->print();
    //std::cerr;
}

int main(){
    test2();
    std::cout<<"End program\n";
}
template<typename T> Output& operator << (Output &output, T t){
    output.buffer<<t;
    output.print();
    output.clear();
    return output;
}
