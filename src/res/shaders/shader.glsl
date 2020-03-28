#vertex
#version 330 core

layout(location = 0) in vec4 v_position;
layout(location = 1) in vec4 v_normal;
layout(location = 2) in vec4 v_texCoord;

void main()
{
  gl_Position = vec4(0, 0, 0, 0);
}

#end
#fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec4 vertex_color;

void main()
{
  color = vec4(1.0F, 0.0F, 0.6F, 1.0F);
}

#end
