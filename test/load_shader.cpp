
#include <iostream>
#include <fstream>

#define output std::cout




char *load_code1(char *filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        return nullptr;
    }
    //std::string str_code = "", ;
    while(!file.eof()){

    }
    //std::string f = file.rdbuf();
    //output<<f;
    //std::string s = file.rdbuf();

}



char *load_code2(char *filename){
    FILE *file = fopen(filename, "r");
    if(!file){
        return nullptr;
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    size = 298;
    output<<"size = "<<size<<"\n";
    
    char* where = new char[size];

    rewind(file);
    fread(where, sizeof(char), size, file);
    where[size-1] = '\0';
    //std::string f = file->
    output<<where<<"\n";
    //fseek(file, 0, SEEK);
    rewind(file);
    int i = 0;
    char bb;
    while((bb = getc(file)) != EOF){
        i++;
    }
    output<<"i = "<<i<<"\n";
    //"\D5\Visualization\Visuali";
    //std::string s = file.rdbuf();
    fclose(file);
}

char *load_code(char *filename){
    FILE *file = fopen(filename, "r");
    if(!file){
        return nullptr;
    }
    char buf;
    int i = 0;
    while( (buf = getc(file)) != EOF){
        i++;
    }
    char *code = new char[i+2];
    //output<<"size = "<<i<<"\n";
    code[i+1] = '\0';
    rewind(file);
    i = 0;
    while( (code[i] = getc(file)) != EOF){
        i++;
    }
    //code[i] = '\0';
    //output<<"size2 = "<<i<<"\n";
    //output<<"code:\n"<<code<<"\n";
    fclose(file);
    return code;
}









int main(){
    char f1[] = "fragment.glsl";
    load_code(f1);


    output<<"End\n";
    return 0;
}
















