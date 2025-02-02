#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aColorMult;    
//layout (location = 1) in vec2 aTexCoord;

//out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 color;

out vec3 fragColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	fragColor = color * aColorMult;
	//TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}