#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
 
  
const GLfloat MOVEMENT_SPEED	= 2.5f;
const GLfloat YAW				= -90.0f;
const GLfloat PITCH				= 0.0f;
const glm::vec3 WORLD_UP		= glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 POSITION		= glm::vec3(0.0f, 0.0f, 3.0f);

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT
};

class Camera {
private:
	glm::vec3 mPosition;
	glm::vec3 mForward;
	glm::vec3 mUp;
	glm::vec3 mRight;
	GLfloat mYaw;
	GLfloat mPitch;
	GLfloat mMovementSpeed;
	GLfloat mFov;
	void updateCameraVectors();
public:
	Camera(glm::vec3 position = POSITION, glm::vec3 up = WORLD_UP);
	glm::mat4 getViewMatrix();
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
	void processKeyboard(Camera_Movement direction, float deltaTime);
	void setMovementSpeed(float movementspeed);
	void processMouseScroll(float yoffset);
	const glm::vec3 getPosition() const;
	const glm::vec3 getForwardVector() const;
	const glm::vec3 getUpVector() const;
	const glm::vec3 getRightVector() const;
	const GLfloat getFOV() const;

};


#endif // !  CAMERA_H
