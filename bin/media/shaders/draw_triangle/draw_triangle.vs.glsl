#version 430 core

layout (location = 0) in vec3 position;
layout (location = 0) in vec3 normal;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//layout (location = 1) in vec4 color;

//out vec4 vs_color;
out vec3 FragPos;
out vec3 Normal;

void main(void)
{
	gl_Position = projection * view * model * vec4(position.xyz, 1.0);
	//vs_color = color;
	FragPos = vec3(model * vec4(position, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
}