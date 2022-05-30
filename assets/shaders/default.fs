#version 440 core

out vec4 FragColor;

uniform vec3 lightPos;
uniform bool blinn;
uniform bool hasTextures;
uniform sampler2D textureDiffuse1;
uniform sampler2D textureNormal1;

in VS_OUT {
    vec3 FragPos;
    vec4 Color;
    vec2 TexCoords;
    vec4 ViewPos;
}
fs_in;

vec3 GetNormal(vec2 TexCoords) {
    vec3 normal = vec3(TexCoords, 1.0);
    if(hasTextures) {
        normal = texture(textureNormal1, TexCoords).rgb;
        return normalize(normal * 2.0 - 1.0);
    }
    return normal;
}

vec3 GetColor(vec2 TexCoords) {
    if(hasTextures) {
        return texture(textureDiffuse1, TexCoords).rgb;
    }
    return vec3(TexCoords, 1.0);
}

void main() {
    const vec3 normal = GetNormal(fs_in.TexCoords);

    vec3 color = GetColor(fs_in.TexCoords);
    vec3 ambient = 0.05 * color;    // TODO: give option to change ambient from outside.

    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;

    vec3 viewDir = normalize(fs_in.ViewPos.xyz - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;

    if(blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    } else {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    }
    vec3 specular = vec3(0.3) * spec;    // TODO: give option to change power of lightning, this vec3(0.3).
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
