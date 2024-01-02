#version 330 core

out vec4 color;

in vec3 normal;
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 color_obj;

void main(){
    //color = vec4(color_obj.r * (normal.r / 2.f), color_obj.g * (normal.g / 2.f), color_obj.b * (normal.b / 2.f), 1.0f);
    //color = vec4(color_obj * normal, 1.f);
    //color = vec4(color_obj, 1.f);
    //color = vec4( 0.1f, 0.1f, 0.4f, 1.0f);
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * color_obj;
    color = vec4(result, 1.0f);
}