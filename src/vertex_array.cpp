/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_array.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:33 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/09 13:12:12 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"
#include "vertex_array.hpp"
#include "renderer.hpp"
#include "vertex_buffer.hpp"


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
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto &element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.get_stride(), (const void *)offset));
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
