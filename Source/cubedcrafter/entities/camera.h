#ifndef CUBED_CRAFTER_ENTITIES_CAMERA
#define CUBED_CRAFTER_ENTITIES_CAMERA

#include <glm/glm.hpp>
#include "graphics/shader.h"
#include "graphics/window.h"

class Camera
{
private:
	void recalculateView();

	glm::vec3 position;
	glm::vec3 rotation;

	float moveSpeed = 0.06f;
	float rotateSpeed = 0.02f;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

public:
	Camera();

	void setPerspective(float screenWidth, float screenHeight);
	void setOrthographic();

	void freeCam(const Window& window);

	void loadToShader(const Shader& shader) const;
};


#endif // CUBED_CRAFTER_ENTITIES_CAMERA