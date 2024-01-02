#version 330 core
//in vec3 ourColor;
out vec4 color;
in vec3 position1;

void main(){
    float g = 1.0f - (position1.y / 2.0f);
    float b = position1.y < 1.4 ? 0.3: 0.0f;
    color = vec4(0.1, g, b, 1.0f);
}