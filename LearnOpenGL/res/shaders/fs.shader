#version 330 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float value;
void main()
{
	vec2 tex = vec2(2 * texCoord.x, 2 * texCoord.y);
	FragColor = mix(texture(texture1, texCoord), texture(texture2, tex), value);
}