#include <iostream>
#include <cstdarg>
#include <cstring>

#define CONSOLE 1
#define LOG 2
 

void myPrintf(int OUT, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    //printf("[%s]\n", format);
    // if(strncmp("LOG", format, 3) == 0){
    //     printf("TEST COMP\n");
    // }
    va_end(args);
}

int main()
{
    myPrintf(CONSOLE, "LOG Hello, %s! It's %d degrees outside.\n", "John", 25);
    myPrintf(CONSOLE, "LOG Hello %f %f \n", 3.00002, -4);
    
    return 0;
}