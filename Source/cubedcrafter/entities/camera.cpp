#include "camera.h"
#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : viewMatrix(1), projectionMatrix(1), position(0, 0, 0), rotation(0, 0, 0)
{
	position = { 0, 0, 5 };
	recalculateView();
}


void Camera::recalculateView()
{
	viewMatrix = glm::mat4(1);
	viewMatrix = glm::rotate(viewMatrix, -rotation.x, glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, -rotation.y, glm::vec3(0, 1, 0));
	viewMatrix = glm::rotate(viewMatrix, -rotation.z, glm::vec3(0, 0, 1));
	viewMatrix = glm::translate(viewMatrix, -position);
}

void Camera::loadToShader(const Shader& shader) const
{
	glm::mat4 viewProjectionMatrix = projectionMatrix * viewMatrix;
	shader.uploadMatrix(viewProjectionMatrix, "u_view_projection_matrix");
}

void Camera::setPerspective(float screenWidth, float screenHeight)
{
	projectionMatrix = glm::perspective(glm::radians(45.0f), screenWidth/screenHeight, 0.1f, 1000.0f);
}
void Camera::setOrthographic()
{
	// FUCK
}

void Camera::freeCam(const Window& window)
{
	if (window.isKeyPressed(GLFW_KEY_UP))    rotation.x += rotateSpeed;
	if (window.isKeyPressed(GLFW_KEY_DOWN))  rotation.x -= rotateSpeed;
	if (window.isKeyPressed(GLFW_KEY_LEFT))  rotation.y += rotateSpeed;
	if (window.isKeyPressed(GLFW_KEY_RIGHT)) rotation.y -= rotateSpeed;
	
	rotation.x = std::clamp(rotation.x, glm::radians(-45.0f), glm::radians(45.0f));

	const glm::vec3 front = glm::normalize(glm::vec3(-sin(rotation.y), 0, -cos(rotation.y)));
	const glm::vec3 right = glm::cross(front, glm::vec3(0, 1, 0));


	if (window.isKeyPressed(GLFW_KEY_W)) position += front * moveSpeed;
	if (window.isKeyPressed(GLFW_KEY_A)) position -= right * moveSpeed;
	if (window.isKeyPressed(GLFW_KEY_S)) position -= front * moveSpeed;
	if (window.isKeyPressed(GLFW_KEY_D)) position += right * moveSpeed;


	if (window.isKeyPressed(GLFW_KEY_SPACE))      position.y += moveSpeed;
	if (window.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) position.y -= moveSpeed;
	
	
	recalculateView();
	
}