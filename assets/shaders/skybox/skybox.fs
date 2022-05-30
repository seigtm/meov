#version 440 core

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec4 Color;
    vec3 TexCoords;
    vec4 ViewPos;
}
fs_in;

uniform samplerCube textureCubemap1;

void main() {
    FragColor = texture(textureCubemap1, fs_in.TexCoords);
}
