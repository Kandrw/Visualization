#include "shader.hpp"

#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include "../output/output.hpp"

#define SIZE_LOG_BUFFER 512

Shader::Shader(unsigned int _id) : _id(_id){
}
Shader::~Shader(){
    glDeleteProgram(_id);
}
void Shader::use(){
	glUseProgram(_id);
}

unsigned int Shader::id(){
    return _id;
}

char *load_code(const char *);
int compileShader(std::string, GLint, GLuint*);

Shader *load_Shader(std::string fname_fragment, std::string fname_vertex){
    GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[SIZE_LOG_BUFFER];
    if(compileShader(fname_fragment, GL_FRAGMENT_SHADER, &fragment)){
        return nullptr;
    }
    if(compileShader(fname_vertex, GL_VERTEX_SHADER, &vertex)){
        return nullptr;
    }
    /* Shader Program */
    GLuint id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(id, SIZE_LOG_BUFFER, nullptr, infoLog);
		print_log(CONSOLE, "[Error] (SHADER::PROGRAM) linking failed, shaders: %s, %s\n", fname_fragment.c_str(), fname_vertex.c_str());
		print_log(CONSOLE, "%s\n", infoLog);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return nullptr;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
    print_log(CONSOLE, "[Shader]: shader load - %d\n", (int)id);
    return new Shader(id);
}

/* Функции доступные только в модуле*/
char *load_code(const char *filename){
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
    code[i+1] = '\0';
    rewind(file);
    i = 0;
    while( (code[i] = getc(file)) != EOF){
        i++;
    }
    //for(int i2 = 0; i2 <= i; ++i2){
        //output<<(int)code[i2]<<" ";
    //}
    code[i] = '\0';
    //output<<"\n";
    fclose(file);
    return code;
}
int compileShader(std::string fname_shader, GLint type_shader, GLuint *shader_result){
    const GLchar *shader_code;
    GLuint shader;
    shader_code = load_code(fname_shader.c_str());
    if(!shader_code){
        print_log(CONSOLE, "[Error]: file shader not found: %s\n", fname_shader.c_str());
        return -1;
    }
    GLint success;
	GLchar infoLog[SIZE_LOG_BUFFER];
    shader = glCreateShader(type_shader);
	glShaderSource(shader, 1, &shader_code, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(shader, SIZE_LOG_BUFFER, nullptr, infoLog);
		print_log(CONSOLE, "[Error]: compilation failed: %s\n", fname_shader.c_str());
		print_log(CONSOLE, "%s\n", infoLog);
		return -1;
	}
    *shader_result = shader;
    return 0;
}














