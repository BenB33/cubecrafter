#ifndef CUBED_CRAFTER_GRAPHICS_SHADER_H
#define CUBED_CRAFTER_GRAPHICS_SHADER_H

#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int shaderID;

public:
	Shader(const char* filePath);
	~Shader();

	void bind() const;

	void uploadMatrix(const glm::mat4& matrix, const char* uniformName) const;
};

#endif // CUBED_CRAFTER_GRAPHICS_SHADER_H