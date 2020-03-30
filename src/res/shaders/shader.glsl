#vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform vec4 translate;

void main()
{
  gl_Position = position;
}

#end
#fragment
#version 330 core

layout(location = 0) out vec4 o_color;
uniform vec4 color;

void main()
{
  o_color = color;
}

#end
