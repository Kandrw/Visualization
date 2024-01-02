#version 330 core




//in vec4 vertexColor;

uniform vec4 ourColor;
uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform vec2 k_pl1;

out vec4 color;






void main(){


    //vec2 uv = (gl_FragCoord.xy - 0.5 * u_resolution.xy)/u_resolution.y;
    
    color = vec4 (0.4,0.5,0.9, 1.0);
    
}