#version 440 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexPos;

out vec4 color;
out vec2 texPos;

uniform mat4 projection = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 model = mat4(1);

void main() {
   color = aColor;
   texPos = aTexPos;

   gl_Position = projection * view * model * vec4(aPos, 1.0);
}