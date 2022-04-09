#version 440 core

in vec4 color;
in vec2 texPos;

out vec4 FragColor;

uniform sampler2D textureDiffuse1;
uniform sampler2D textureNormal1;

void main() {
    vec3 normal = texture(textureNormal1, texPos).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    vec3 color = texture(textureDiffuse1, texPos).rgb;

    vec3 ambient = 0.1 * color;

    FragColor = vec4(ambient + color, 1.0);
}
