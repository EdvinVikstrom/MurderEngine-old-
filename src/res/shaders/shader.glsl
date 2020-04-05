#vertex
#version 460 core

layout(location = 0) in vec4 position;

void main()
{
  gl_Position = position;
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
