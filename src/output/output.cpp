#include "output.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdarg>
#include <cstring>

#define LOG_FILE "log.log"
//#define ERRORS_FILE "error.log"



// std::stringstream Output::buffer;
// bool Output::stream_cout = 1; 

// Output output;

// Output::Output(){
//     //printf("\E[2m");
//     //system("")
//     setColorStream('0', '9');
//     std::cout<<"[Init output]\n";


// }

// void Output::print(){
//     std::cout<<buffer.str();
    
// }
// void Output::clear(){
//     buffer.str("");
// }

// Output *Output::setColorStream(char fcolor, char bgcolor){
//     static char buffer_edit_color[9] = "color --";
//     buffer_edit_color[6] = fcolor;
//     buffer_edit_color[7] = bgcolor;
//     system(buffer_edit_color);
//     return this;
// }
void setColorStream(char fcolor, char bgcolor){
    static char buffer_edit_color[9] = "color --";
    buffer_edit_color[6] = fcolor;
    buffer_edit_color[7] = bgcolor;
    system(buffer_edit_color);
}
FILE *file_log = NULL;

int init_log(){
    file_log = fopen(LOG_FILE, "w");
    print_log(CONSOLE, "[INIT_LOG]\n");
    return 0;
}

void print_log(int out, const char* format, ...){
    va_list args;
    va_start(args, format);

    switch (out){
    case CONSOLE:
        vfprintf(stdout, format, args);
    default:
        vfprintf(file_log, format, args);
        break;
    }
    va_end(args);
}



