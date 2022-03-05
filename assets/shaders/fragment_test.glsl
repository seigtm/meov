#version 440 core

in vsOut{
   vec4 color;
   vec2 texPos;
} vs_in;

out vec4 FragColor;

uniform sampler2D textureDiffuse1;
// uniform sampler2D textureNormal1;

void main() {
    FragColor = texture(textureDiffuse1, vs_in.texPos) * vs_in.color;
}
