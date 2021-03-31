#version 330 core

out vec4 o_frag_colour;

in vec4 v_pos_col;

void main() {
   o_frag_colour = v_pos_col + 0.5;
}