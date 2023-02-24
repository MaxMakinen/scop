/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_buffer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:33 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/23 14:21:37 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index_buffer.hpp"
#include "vector.hpp"

index_buffer::index_buffer( GLuint *indices, GLsizeiptr count )
{
	GLCall(glGenBuffers(1, &m_Renderer_id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW));
}

index_buffer::~index_buffer()
{
	GLCall(glDeleteBuffers(1, &m_Renderer_id));
}

void index_buffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_id));
}

void index_buffer::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void index_buffer::delete_index() const
{
	GLCall(glDeleteBuffers(1, &m_Renderer_id));
}

