#version 330 core

in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;
void main()
{
	//FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.3);
	FragColor = vec4(lightColor * objectColor, 1.0);
}