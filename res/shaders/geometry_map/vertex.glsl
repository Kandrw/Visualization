#version 330 core
layout (location = 0) in vec3 position; // Устанавливаем позиция переменной с координатами в 0
//layout (location = 1) in vec3 color;    // А позицию переменной с цветом в 1

//out vec3 ourColor; // Передаем цвет во фрагментный шейдер
out vec3 position1;
//uniform mat4 transform;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
    //gl_Position = transform * vec4(position, 1.0);
    //gl_Position = vec4(position, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0f);
    //gl_Position =  view * projection* model * vec4(position, 1.0f);
    
    position1 = position;
    //ourColor = color; // Устанавливаем значение цвета, полученное от вершинных данных
}