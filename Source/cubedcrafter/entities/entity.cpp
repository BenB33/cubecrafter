#include "entity.h"

#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(const std::shared_ptr<Mesh>& mesh) : mesh(mesh), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1)
{

}


void Entity::render(const Shader& shader) const
{
	glm::mat4 model_matrix(1);
	model_matrix = glm::translate(model_matrix, position);
	model_matrix = glm::rotate(model_matrix, rotation.x, glm::vec3(1, 0, 0));
	model_matrix = glm::rotate(model_matrix, rotation.y, glm::vec3(0, 1, 0));
	model_matrix = glm::rotate(model_matrix, rotation.z, glm::vec3(0, 0, 1));
	model_matrix = glm::scale(model_matrix, scale);
	shader.uploadMatrix(model_matrix, "u_model_matrix");
	mesh->render();
}


glm::vec3 Entity::getPosition() const { return position; }
void Entity::setPosition(const glm::vec3& newPosition) { position = newPosition; }

glm::vec3 Entity::getRotation() const { return rotation; }
void Entity::setRotation(const glm::vec3& newRotation) { rotation = newRotation; }

glm::vec3 Entity::getScale() const { return scale; }
void Entity::setScale(const glm::vec3& newScale) { scale = newScale; }