#version 430 core

layout (location = 0) in vec3 positon;
layout (location = 1) in vec2 texCoord;

out vec2 fs_texCoord;

void main(void)
{
	gl_Position = vec4(positon.xyz, 1.0);
	fs_texCoord = texCoord;
}