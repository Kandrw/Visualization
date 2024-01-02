#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "window.hpp"
#include "../output/output.hpp"

Camera::Camera(glm::vec3 position, float fov) : position(position), fov(fov), rotation(1.0f){
    updateVectors();
}
void Camera::updateVectors(){
	front = glm::vec3(rotation * glm::vec4(0,0,-1,1));
	right = glm::vec3(rotation * glm::vec4(1,0,0,1));
	up = glm::vec3(rotation * glm::vec4(0,1,0,1));
}
void Camera::rotate(float x, float y, float z){
	rotation = glm::rotate(rotation, z, glm::vec3(0,0,1));
	rotation = glm::rotate(rotation, y, glm::vec3(0,1,0));
	rotation = glm::rotate(rotation, x, glm::vec3(1,0,0));

	updateVectors();
}
void Camera::camera_enevts(float delta){
	if(Window::pressed(GLFW_KEY_W)){
        //output<<"W\n";
        position += front * delta * speed;
    }
    if(Window::pressed(GLFW_KEY_D)){
        //output<<"D\n";
        position += right * delta * speed;
    }
    if(Window::pressed(GLFW_KEY_S)){
        //output<<"S\n";
        position -= front * delta * speed;
    }
    if(Window::pressed(GLFW_KEY_A)){
        //output<<"A\n";
        position -= right * delta * speed;
    }
    if (Window::pressed(GLFW_KEY_SPACE)){
		position += up * delta * speed;
	}
	if (Window::pressed(GLFW_KEY_LEFT_SHIFT)){
		position.y -= delta * speed;
	}
	if (Window::pressed(GLFW_KEY_Q)){
		speed = 30.0f;
	}
	if (Window::pressed(GLFW_KEY_E)){
		speed = 5.0f;
	}
	

        
	camY += -Window::deltaY / Window::HEIGHT * 2;
	camX += -Window::deltaX / Window::HEIGHT * 2;

	if (camY < -glm::radians(89.0f)){
		camY = -glm::radians(89.0f);
	}
	if (camY > glm::radians(89.0f)){
		camY = glm::radians(89.0f);
	}
	rotation = glm::mat4(1.0f);
	rotate(camY, camX, 0);
		
}
glm::mat4 Camera::getProjection(){
	float aspect = (float)Window::WIDTH / (float)Window::HEIGHT;
	return glm::perspective(fov, aspect, 0.1f, 100.0f);
    //return glm::perspective(45.0f, aspect, 0.1f, 100.0f);
    
}

glm::mat4 Camera::getView(){
	return glm::lookAt(position, position+front, up);
}
