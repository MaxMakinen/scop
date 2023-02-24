/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_buffer_layout.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:25:43 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 10:37:06 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef VERTEX_BUFFER_LAYOUT_HPP
# define VERTEX_BUFFER_LAYOUT_HPP

# include <vector>
# include <GL/glew.h>
# include "scop.hpp"
# include "vertex_buffer.hpp"
# include "error_handling.hpp"

struct vertex_buffer_element
{
	uint32_t	type;
	uint32_t	count;
	uint32_t	normalised;

	static uint32_t get_size_of_type(uint32_t type)
	{
		switch (type)
		{
			case GL_FLOAT:			return (4);
			case GL_UNSIGNED_INT:	return (4);
			case GL_UNSIGNED_BYTE:	return (1);
		}
		ASSERT(false);
		return (0);
	}
};

class vertex_buffer_layout
{
	private:
		std::vector<vertex_buffer_element> m_elements;
		GLsizeiptr m_stride;
	public:
		vertex_buffer_layout()
			: m_stride(0) {}

		template< typename T >
		void push(uint32_t count);


		inline const std::vector<vertex_buffer_element> get_elements() const { return (m_elements);}
		inline GLsizeiptr get_stride() const { return (m_stride);}
};

template<>
inline void vertex_buffer_layout::push<float>(uint32_t count)
{
	m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
	m_stride += vertex_buffer_element::get_size_of_type(GL_FLOAT) * count;
};

template<>
inline void vertex_buffer_layout::push<unsigned int>(uint32_t count)
{
	m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	m_stride += vertex_buffer_element::get_size_of_type(GL_UNSIGNED_INT) * count;
};

template<>
inline void vertex_buffer_layout::push<unsigned char>(uint32_t count)
{
	m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	m_stride += vertex_buffer_element::get_size_of_type(GL_UNSIGNED_BYTE) * count;
};

#endif