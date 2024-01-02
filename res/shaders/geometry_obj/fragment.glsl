#version 330 core
in vec3 ourColor;
in vec3 position1;
out vec4 color;


void main(){
    //float g1 = 
    float r1 = position1.x * position1.x + position1.y * position1.y;
    float g1 = ourColor.g;
    if( r1 < 2.0f && r1 > 1.7f){
        g1 = 1.0f;
    }
    color = vec4( ourColor.r, g1, ourColor.b, 1.0f);
}