#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

out vec4 fragColour;

uniform sampler2D inputTexture;

void main()
{
	fragColour = texture(inputTexture, TexCoords);
}