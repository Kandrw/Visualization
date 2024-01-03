#include <sstream>
#define CONSOLE 1
#define LOG 2
// class Output{
// public:
//     Output();
//     static std::stringstream buffer;
//     static bool stream_cout; 
//     void print();
//     void clear();
//     Output *setColorStream(char fcolor, char bgcolor);
// };
// template<typename T> Output& operator << (Output &output, T t){
//     output.buffer<<t;
//     output.print();
//     output.clear();
//     return output;
// }


//extern Output output;

void print_log(int out, const char* format, ...);
int init_log();
