/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_array.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:33 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 11:16:33 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vertex_array.hpp"

vertex_array::vertex_array()
{
	GLCall(glGenVertexArrays(1, &m_renderer_id));
}

vertex_array::~vertex_array()
{
	GLCall(glDeleteVertexArrays(1, &m_renderer_id));
}

void vertex_array::add_buffer(const vertex_buffer &vb, const vertex_buffer_layout &layout)
{
	bind();
	vb.bind();
	const auto &elements = layout.get_elements();
	uint64_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto &element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.get_stride(), (void *)offset));
		offset += element.count * vertex_buffer_element::get_size_of_type(element.type);
	}
}

void vertex_array::bind() const
{
	GLCall(glBindVertexArray(m_renderer_id));
}

void vertex_array::unbind() const
{
	GLCall(glBindVertexArray(0));
}

void vertex_array::delete_buffer() const
{
	GLCall(glDeleteVertexArrays(1, &m_renderer_id));
}

void vertex_array::LinkAttrib(const vertex_buffer &vb, GLuint layout, GLuint numComp, GLenum type, GLsizeiptr stride, void *offset)
{
	//bind();
	vb.bind();
	glVertexAttribPointer(layout, numComp, type, GL_FALSE, stride, offset );
	glEnableVertexAttribArray(layout);
	vb.unbind();
}