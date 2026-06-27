#version 330 core

layout (location = 0) out vec4 out_Color;

in vec2 in_TextureCoord;

// uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
	out_Color = texture(u_Texture, in_TextureCoord);
}