#version 330 core
in vec3 position1;
out vec4 color;

uniform vec3 color_obj;
//uniform vec3 light;

void main(){
    //float g1 = 
    //float r1 = position1.x * position1.x + position1.y * position1.y;
    color = vec4(color_obj.r, color_obj.g, color_obj.b, 1.0f);
    //color = vec4( 0.1f, 0.1f, 0.4f, 1.0f);
}