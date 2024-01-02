
#include <iostream>

class Shader{
private:
    unsigned int _id;
public:
    
    Shader(unsigned int _id);
    ~Shader();
    void use();
    unsigned int id();
       

};
Shader *load_Shader(std::string fname_fragment, std::string fname_vertex);