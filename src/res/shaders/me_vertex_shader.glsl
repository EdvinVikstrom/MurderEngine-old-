#version FUCK YOU OPENGL

in vec3 vertex_position;

int main()
{

  gl_Position = vec4(vertex_position, 1.0);
}
