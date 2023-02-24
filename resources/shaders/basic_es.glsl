#shader vertex
#version 300 es

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_tex_coord;


void main()
{
	gl_Position = position;
	v_tex_coord = texCoord;
};

#shader fragment
#version 300 es

layout(location = 0) out mediump vec4 color;

in mediump vec2 v_tex_coord;

uniform mediump vec4 u_color;
uniform sampler2D u_texture;

void main()
{
	mediump vec4 texColor = texture(u_texture, v_tex_coord);

	color = texColor;
	if (texColor.a < 0.1)
		color = u_color;
};
