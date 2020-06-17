#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;

layout(location = 0) uniform mat4 projection;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;

out vec3 f_normal;
out vec2 f_texCoord;
out vec4 f_color;

void main()
{
  gl_Position = projection * view * model * position;
  f_normal = normal;
  f_texCoord = texCoord;
  f_color = color;
}
