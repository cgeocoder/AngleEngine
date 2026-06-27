#version 330 core

layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec2 in_TextureCoord;

out vec2 out_TextureCoord;

void main() {
	gl_Position = in_Position;
	out_TextureCoord = in_TextureCoord;
}