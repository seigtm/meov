#version 330 core

#define MAX_POINT_LIGHTS 1

out vec4 FragmentColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PhongsLightComponents {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    bool enabled;
    vec3 direction;
    PhongsLightComponents params;
};

struct PointLight {
    bool enabled;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    PhongsLightComponents params;
};

struct SpotLight {
    bool enabled;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
    PhongsLightComponents params;
};

in VertexShaderOutput {
    vec3 FragmentPosition;
    vec3 Normal;
    vec2 TextureCoordinates;
}
VSOut;

uniform vec3 viewPosition;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

float GetDiffuse(vec3 normal, vec3 direction);
float GetSpecular(vec3 viewDir, vec3 reflectDir);

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 normal = normalize(VSOut.Normal);
    vec3 viewDirection = normalize(viewPosition - VSOut.FragmentPosition);

    vec3 result = CalculateDirectionalLight(dirLight, normal, viewDirection);
    // if(activePoints > 0) {
    // if(activePoints <= MAX_POINT_LIGHTS)
    // activePoints = MAX_POINT_LIGHTS - 1;
    for(int i = 0; i < MAX_POINT_LIGHTS; ++i)
        result += CalculatePointLight(pointLights[i], normal, VSOut.FragmentPosition, viewDirection);
    // }
    result += CalculateSpotLight(spotLight, normal, VSOut.FragmentPosition, viewDirection);
    FragmentColor = vec4(result, 1.0);
}

//================================== Functions ================================== //

float GetDiffuse(vec3 normal, vec3 direction) {
    return max(dot(normal, direction), 0.0);
}

float GetSpecular(vec3 viewDir, vec3 reflectDir) {
    return pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    if(!light.enabled)
        return vec3(0);

    vec3 lightDirection = normalize(-light.direction);
    float diff = GetDiffuse(normal, lightDirection);     // Diffuse shading
    vec3 reflectDir = reflect(-lightDirection, normal);  // Specular shading
    float spec = GetSpecular(viewDir, reflectDir);

    vec2 texCoords = VSOut.TextureCoordinates;
    // Combine results:
    vec3 ambient = light.params.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.params.diffuse * diff * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.params.specular * spec * vec3(texture(material.specular, texCoords));
    return ambient + diffuse + specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if(!light.enabled)
        return vec3(0);

    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = GetDiffuse(normal, lightDirection);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = GetSpecular(viewDir, reflectDir);
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    vec2 texCoords = VSOut.TextureCoordinates;
    vec3 ambient = light.params.ambient * vec3(texture(material.diffuse, texCoords)) * attenuation;
    vec3 diffuse = light.params.diffuse * diff * vec3(texture(material.diffuse, texCoords)) * attenuation;
    vec3 specular = light.params.specular * spec * vec3(texture(material.specular, texCoords)) * attenuation;
    return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if(!light.enabled)
        return vec3(0);

    vec3 lightDirection = normalize(light.position - fragPos);
    float diff = GetDiffuse(normal, lightDirection);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = GetSpecular(viewDir, reflectDir);
    float dist = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    // spotlight intensity
    float theta = dot(lightDirection, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec2 texCoords = VSOut.TextureCoordinates;
    vec3 ambient = light.params.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.params.diffuse * diff * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.params.specular * spec * vec3(texture(material.specular, texCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return ambient + diffuse + specular;
}