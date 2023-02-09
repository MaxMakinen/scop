/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_buffer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:33 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/09 13:12:27 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"
#include "vertex_buffer.hpp"
#include "renderer.hpp"


vertex_buffer::vertex_buffer(const void *data, GLuint size)
{
	GLCall(glGenBuffers(1, &m_Renderer_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertex_buffer::~vertex_buffer()
{
	GLCall(glDeleteBuffers(1, &m_Renderer_id));
}

void vertex_buffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_id));
}

void vertex_buffer::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
