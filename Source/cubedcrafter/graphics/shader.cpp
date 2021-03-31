#include "asserts.h"
#include "shader.h"

#include <glad/glad.h>
#include <fstream>
#include <string>

// Adding a either a vertex or fragment shader to the shader program.
static GLuint addShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

  const GLchar* code[1]{};
  code[0] = shaderCode;

  GLint codeLength[1]{};
  codeLength[0] = static_cast<GLuint>(strlen(shaderCode));

  glShaderSource(shader, 1, code, codeLength);
  glCompileShader(shader);

#ifdef CC_BUILD_DEBUG
  GLint result = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (!result) {
    GLchar error_buffer[1024] = { 0 };
    glGetShaderInfoLog(shader, sizeof(error_buffer), nullptr, error_buffer);
    CC_ASSERT(false, error_buffer);
  }
#endif

  glAttachShader(program, shader);

  return shader;
}

Shader::Shader(const char* filePath)
{
	// Create empty shader program
	shaderID = glCreateProgram();
	CC_ASSERT(shaderID, "ERROR: Creating shader program.");

	// Adding suffix's to file path to seperate vert and frag files.
	std::string vertPath(filePath);
	vertPath += ".vert.glsl";
	std::string fragPath(filePath);
	fragPath += ".frag.glsl";

	// Importing everything from shader.vert.glsl and shader.frag.glsl into strings
	std::ifstream vertFile(vertPath);
	CC_ASSERT(vertFile.is_open(), "ERROR: Opening Vertex File");
	std::string vertCode((std::istreambuf_iterator<char>(vertFile)), std::istreambuf_iterator<char>());

	std::ifstream fragFile(fragPath);
	CC_ASSERT(fragFile.is_open(), "ERROR: Opening Fragment File");
	std::string fragCode((std::istreambuf_iterator<char>(fragFile)), std::istreambuf_iterator<char>());

	GLuint vertShader = addShader(shaderID, vertCode.c_str(), GL_VERTEX_SHADER);
	GLuint fragShader = addShader(shaderID, fragCode.c_str(), GL_FRAGMENT_SHADER);

	// Link and error checking
	glLinkProgram(shaderID);
#ifdef CC_BUILD_DEBUG
	GLint result = 0;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		GLchar errorBuffer[1024] = { 0 };
		glGetProgramInfoLog(shaderID, sizeof(errorBuffer), nullptr, errorBuffer);
		CC_ASSERT(false, errorBuffer);
	}
#endif //CC_BUILD_DEBUG

	// Validate and error checking
	glValidateProgram(shaderID);
#ifdef CC_BUILD_DEBUG
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		GLchar errorBuffer[1024] = { 0 };
		glGetProgramInfoLog(shaderID, sizeof(errorBuffer), nullptr, errorBuffer);
		CC_ASSERT(false, errorBuffer);
	}
#endif //CC_BUILD_DEBUG


	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
	glDeleteProgram(shaderID);
}

void Shader::bind() const
{
	glUseProgram(shaderID);
}