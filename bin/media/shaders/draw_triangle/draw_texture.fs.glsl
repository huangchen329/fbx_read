#version 430 core

in vec2 fs_texCoord;
uniform sampler2D ourTexture;

out vec4 color;

void main(void)
{
	color = texture(ourTexture, fs_texCoord);
}