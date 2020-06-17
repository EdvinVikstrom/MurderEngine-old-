#version 460 core

in vec3 f_normal;
in vec2 f_texCoord;
in vec4 f_color;

uniform sampler2D texture;

layout(location = 0) out vec4 outColor;

void main()
{
  outColor = texture2D(texture, f_texCoord);
}
