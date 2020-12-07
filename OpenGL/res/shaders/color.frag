#version 330 core

out vec4 FragColor;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
	float ndc = depth * 2.0 - 1.0;
	 return (2.0 * near * far) / (far + near - ndc * (far - near));
}

struct Material {
vec3 ambient;
vec3 diffuse;
vec3 specular;
float shininess;
};

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main()
{
	//Ambient
	vec3 ambient = light.ambient * material.ambient ;

	//Diffuse
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(Normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//Specular
	vec3 viewDir = normalize(viewPos -FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular; 
	float depth = LinearizeDepth(gl_FragCoord.z/far);
	FragColor = vec4(vec3(depth), 1.0);
}

