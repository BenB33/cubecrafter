#include "mesh.h"

#include <glad/glad.h>

Mesh::Mesh(float* vertices, int vertexCount_, unsigned int* indices, int indexCount_)
{
	indexCount = indexCount_;

	// Binding Vertex Array [VAO]
	// Vertex Array Object is an object that contains one or more vertex buffers and information on how openGL should
	// interprete those buffers.
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// Binding Buffers [VBO]
	// Vertex Buffer Object is a buffer of memory on the graphics card
	glGenBuffers(1, &vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
	glBufferData(GL_ARRAY_BUFFER, vertexCount_, vertices, GL_STATIC_DRAW);

	// Binding Index Buffer [IBO]
	// Index Buffer is a way of performing index draws with OpenGL. It tells OpenGL what order
	// to draw the vertices and how to connect them together.
	glGenBuffers(1, &ibo_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount_, indices, GL_STATIC_DRAW);

	// Telling OpenGL how to intepret the data inside of the vertex buffer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Unbinding shit
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao_id);
	glDeleteBuffers(1, &vbo_id);
	glDeleteBuffers(1, &ibo_id);
}

void Mesh::render() const
{
	glBindVertexArray(vao_id);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}