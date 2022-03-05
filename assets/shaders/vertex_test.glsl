#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexPos;

out VsOut{
   vec4 color;
   vec2 texPos;
} vs_out;

uniform mat4 worldTransform = mat4(
   1, 0, 0, 0,
   0, 1, 0, 0,
   0, 0, 1, 0,
   0, 0, 0, 1
);

void main() {
   // vec3 T = normalize(vec3(worldTransform * vec4(aTangent,   0.0)));
   // vec3 B = normalize(vec3(worldTransform * vec4(aBitangent, 0.0)));
   // vec3 N = normalize(vec3(worldTransform * vec4(aColor,    0.0)));
   // vs_out.TBN = mat3(T, B, N);
   vs_out.color = aColor;
   vs_out.texPos = aTexPos;

   gl_Position = worldTransform * vec4(aPos, 1.0);
}