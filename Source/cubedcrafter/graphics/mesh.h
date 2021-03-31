#ifndef CUBED_CRAFTER_GRAPHICS_MESH_H
#define CUBED_CRAFTER_GRAPHICS_MESH_H



class Mesh 
{
private:
	unsigned int vbo_id, vao_id, ibo_id;
	int indexCount;

public:
	Mesh(float* vertices, int vertexCount_, unsigned int* indices, int indexCount_);
	~Mesh();
	void render() const;

};


#endif // CUBED_CRAFTER_GRAPHICS_MESH_H