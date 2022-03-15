R"glsl(
#version 440 core

in vec4 color;
in vec2 texPos;

out vec4 FragColor;

uniform sampler2D textureDiffuse1;
// uniform sampler2D textureNormal1;

void main() {
    // FragColor = mix(texture(textureDiffuse1, texPos), color, 0.5);
    FragColor = texture(textureDiffuse1, texPos);
}
)glsl";