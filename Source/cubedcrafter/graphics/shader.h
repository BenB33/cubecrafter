#ifndef CUBED_CRAFTER_GRAPHICS_SHADER_H
#define CUBED_CRAFTER_GRAPHICS_SHADER_H

class Shader
{
private:
	unsigned int shaderID;

public:
	Shader(const char* filePath);
	~Shader();

	void bind() const;

};

#endif // CUBED_CRAFTER_GRAPHICS_SHADER_H