#version 330 core

out vec4 o_frag_colour;

in vec3 v_frag_pos;

void main() {
   o_frag_colour = vec4(v_frag_pos.x, v_frag_pos.y, v_frag_pos.z, 1);
}