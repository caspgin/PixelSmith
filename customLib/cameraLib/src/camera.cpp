#include "glm/ext/matrix_transform.hpp"
#include <camera.h>
#include <GLFW/glfw3.h>

const GLfloat PITCH_CONSTRAIN_MIN 	= -89.0f;
const GLfloat PITCH_CONSTRAIN_MAX 	= 89.0f;
const GLfloat MOUSE_SENSITIVITY 	= 0.1f;
const glm::vec3 FRONT 				= glm::vec3(0.0f, 0.0f, -1.0f);
const GLfloat FOV_MAX				= 45.0f;
const GLfloat FOV_MIN				= 0.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up) 
	: mPosition(position), mUp(up), mForward(FRONT), mYaw(YAW), mPitch(PITCH),  mMovementSpeed(MOVEMENT_SPEED), mFov(FOV_MAX) 
{
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(mPosition, mPosition + mForward, WORLD_UP);
}


void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {

    xoffset *= MOUSE_SENSITIVITY;
    yoffset *= MOUSE_SENSITIVITY; 
 
    this->mYaw   += xoffset; 
    this->mPitch += yoffset; 
	    
	if(constrainPitch){    
		this->mPitch = glm::clamp(this->mPitch, PITCH_CONSTRAIN_MIN, PITCH_CONSTRAIN_MAX);
	}       
    
	updateCameraVectors();
}  

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {

	float velocity = this->mMovementSpeed * deltaTime;

	if (direction == Camera_Movement::FORWARD)
		this->mPosition += this->mForward * velocity;
	if (direction == Camera_Movement::BACKWARD)
		this->mPosition -= this->mForward * velocity;
	if (direction == Camera_Movement::LEFT)
		this->mPosition -= this->mRight * velocity;
	if (direction == Camera_Movement::RIGHT)
		this->mPosition += this->mRight * velocity;
}

void Camera::updateCameraVectors(){

    glm::vec3 front;     
    front.x = cos(glm::radians(this->mYaw)) * cos(glm::radians(this->mPitch));
    front.y = sin(glm::radians(this->mPitch));
    front.z = sin(glm::radians(this->mYaw)) * cos(glm::radians(this->mPitch));
    this->mForward = glm::normalize(front);

	this->mRight = glm::normalize(glm::cross(this->mForward, WORLD_UP));
	this->mUp    = glm::normalize(glm::cross(this->mRight, this->mForward));
}

void Camera::setMovementSpeed(float movementSpeed) {
	this->mMovementSpeed = movementSpeed;
}

void Camera::processMouseScroll(float yoffset)
{
	this->mFov -= (float)yoffset;
	this->mFov = glm::clamp(this->mFov, FOV_MIN, FOV_MAX);
}

const glm::vec3 Camera::getPosition() const {
	return this->mPosition;
}

const glm::vec3 Camera::getForwardVector() const {
	return this->mForward;
}

const glm::vec3 Camera::getUpVector() const {
	return this->mUp;
}

const glm::vec3 Camera::getRightVector() const {
	return this->mRight;
}

const GLfloat Camera::getFOV() const {
	return this->mFov;
}

