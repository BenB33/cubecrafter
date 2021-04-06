#version 330 core

layout (location = 0) in vec3 a_pos;

out vec3 v_frag_pos;

uniform mat4 u_model_matrix;
uniform mat4 u_view_projection_matrix;

void main() {
	v_frag_pos = a_pos;
	gl_Position = u_view_projection_matrix * u_model_matrix * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}