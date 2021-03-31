#version 330 core

layout (location = 0) in vec3 a_pos;

out vec4 v_pos_col;

void main() {
  v_pos_col = vec4(a_pos, 1);
  gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}