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
		output << "[Error] (SHADER::PROGRAM) linking failed, shaders: " <<fname_fragment<<", "<<fname_vertex<<"\n";
		output << infoLog << "\n";

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return nullptr;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
    output<<"[Shader]: shader load - "<<id<<"\n";
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
        output << "[Error]: file shader not found: "<<fname_shader<<"\n";
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
		output << "[Error]: compilation failed: "<<fname_shader<<"\n";
		output << infoLog << "\n";
		return -1;
	}
    *shader_result = shader;
    return 0;
}














