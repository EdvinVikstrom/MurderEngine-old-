#vertex
#version 460 core

layout(location = 0) in vec4 position;

layout(location = 0) uniform vec4 translate;
layout(location = 1) uniform vec4 rotation;
layout(location = 2) uniform vec4 scale;

layout(location = 3) uniform mat2x3 diffuse;
layout(location = 4) uniform mat2x3 gloss;
layout(location = 5) uniform mat2x3 metallic;
layout(location = 6) uniform mat2x3 roughness;
layout(location = 7) uniform mat2x3 emission;
layout(location = 8) uniform mat2x3 ior;

void main()
{
  gl_Position = position + translate;
}

#end
#fragment
#version 460 core

layout(location = 0) out vec4 o_color;

void main()
{
  o_color = vec4(1.0F, 0.2F, 0.7F, 1.0F);
}

#end
