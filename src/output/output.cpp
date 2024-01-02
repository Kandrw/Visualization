#include "output.hpp"

#include <iostream>
#include <sstream>

std::stringstream Output::buffer;
bool Output::stream_cout = 1; 

Output output;

Output::Output(){
    //printf("\E[2m");
    //system("")
    setColorStream('0', '9');
    std::cout<<"[Init output]\n";
}

void Output::print(){
    std::cout<<buffer.str();
    
}
void Output::clear(){
    buffer.str("");
}

Output *Output::setColorStream(char fcolor, char bgcolor){
    static char buffer_edit_color[9] = "color --";
    buffer_edit_color[6] = fcolor;
    buffer_edit_color[7] = bgcolor;
    system(buffer_edit_color);
    return this;
}




