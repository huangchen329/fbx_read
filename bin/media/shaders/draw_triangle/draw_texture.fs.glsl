#version 430 core

in vec2 fs_texCoord;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

out vec4 color;

void main(void)
{
	color = mix(texture(ourTexture1, fs_texCoord), texture(ourTexture2, fs_texCoord), 0.5);
}