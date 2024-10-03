#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D textureID;

void main()
{
	FragColor = texture(textureID, TexCoord) ;
}