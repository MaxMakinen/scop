/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_buffer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:15 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 10:37:59 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef INDEX_BUFFER_HPP
# define INDEX_BUFFER_HPP

# include <GL/glew.h>
# include "error_handling.hpp"

class index_buffer
{
	private:
		GLuint m_Renderer_id;
		GLuint m_Count;
	public:
		index_buffer( GLuint *indices, GLsizeiptr count );
		~index_buffer();

		void bind() const;
		void unbind() const;
		void delete_index() const;

		inline GLuint get_count() const { return ((GLuint)m_Count); }
};

#endif
