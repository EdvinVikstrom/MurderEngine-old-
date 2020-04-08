#vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoord;

layout(location = 0) uniform mat4 projection_mat;
layout(location = 1) uniform mat4 view_mat;
layout(location = 2) uniform mat4 model_mat;

out vec2 v_texCoord;

void main()
{
  gl_Position = position * projection_mat * view_mat * model_mat;
  v_texCoord = texCoord;
}

#end
#fragment
#version 460 core

layout(location = 0) out vec4 o_color;

in vec2 v_texCoord;
layout(location = 3) uniform sampler2D active_tex;

void main()
{
  vec4 tex_color = texture(active_tex, v_texCoord);
  o_color = tex_color;
}

#end
