#vertex
#version 460 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

out vec3 fragColor;

void main()
{
  gl_Position = vec4(inPosition, 0.0, 1.0);
  fragColor = inColor;
}

#fragment
#version 460 core

layout(location = 0) out vec4 outColor;

in vec3 fragColor;

void main() {
  outColor = vec4(fragColor, 1.0F);
}
