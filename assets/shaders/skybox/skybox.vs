#version 440 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexPos;

out VS_OUT {
    vec3 FragPos;
    vec4 Color;
    vec2 TexCoords;
    vec4 ViewPos;
}
vs_out;

uniform mat4 projection = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 model = mat4(1);

void main() {
    vs_out.FragPos = aPos;
    vs_out.Color = aColor;
    vs_out.TexCoords = aTexPos;
    vs_out.ViewPos = view * vec4(0);

    vec4 pos = projection * view * model * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}