#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_tex_coord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_tex_coord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_tex_coord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{	
	vec4 texColor = texture(u_texture, v_tex_coord);
//	color = texColor;
	color = texColor;
	if (texColor.a < 0.1)
		color = u_color;
};