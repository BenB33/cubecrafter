#ifndef CUBED_CRAFTER_ENTITIES_ENTITY
#define CUBED_CRAFTER_ENTITIES_ENTITY

#include <glm/glm.hpp>
#include <memory>

#include "graphics/mesh.h"
#include "graphics/shader.h"

class Entity
{
private:
	std::shared_ptr<Mesh> mesh;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Entity(const std::shared_ptr<Mesh>&mesh);
	
	void render(const Shader& shader) const;

	glm::vec3 getPosition() const;
	void setPosition(const glm::vec3& position);

	glm::vec3 getRotation() const;
	void setRotation(const glm::vec3& rotation);

	glm::vec3 getScale() const;
	void setScale(const glm::vec3& scale);
};

#endif // CUBED_CRAFTER_ENTITIES_ENTITY