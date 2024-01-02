#include <glm/glm.hpp>

class Camera{
    void updateVectors();
	float camX = 0.0f;
	float camY = 0.0f;
	float fov;
    float speed = 5.0f;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 position;
	glm::mat4 rotation = glm::mat4(1.0f);
public:
	
	
	
	Camera(glm::vec3 position, float fov);

	void rotate(float x, float y, float z);
	glm::mat4 getProjection();
	glm::mat4 getView();
	void camera_enevts(float delta);

};