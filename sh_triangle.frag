#version 450 core

varying lowp vec4 col;
out vec4 color;

void main(void) {
    color = col;
}
