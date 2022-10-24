#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aNormal;
layout(location = 2) in vec2 aTexPos;

out VertexShaderOutput {
    vec3 FragmentPosition;
    vec3 Normal;
    vec2 TextureCoordinates;
    float Alpha;
}
VSOut;

uniform mat4 projection = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 model = mat4(1);

void main() {
    VSOut.FragmentPosition = vec3(model * vec4(aPos, 1.0));
    VSOut.Normal = normalize(mat3(transpose(inverse(model))) * aNormal.xyz);
    VSOut.TextureCoordinates = aTexPos;
    VSOut.Alpha = aNormal.w;

    gl_Position = projection * view * vec4(VSOut.FragmentPosition, 1.0);
}
