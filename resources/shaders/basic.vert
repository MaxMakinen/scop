#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_tex_coord;

//uniform mat4 u_MVP;

void main()
{
	gl_Position = position;
	v_tex_coord = texCoord;
}
