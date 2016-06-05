#version 430 core

uniform vec3 lightdir;

in vec3 FragPos;
in vec3 Normal;
//in vec4 vs_color;
out vec4 color;

void main(void)
{
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightdir), 0.0);
	vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
	color = vec4(vec3(1.0, 1.0, 1.0) * diffuse, 1.0);
}