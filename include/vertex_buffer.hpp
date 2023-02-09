/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_buffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:15 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/09 13:12:39 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef VERTEX_BUFFER_HPP
# define VERTEX_BUFFER_HPP

# include "scop.hpp"

class vertex_buffer
{
	private:
		GLuint m_Renderer_id;
	public:
		vertex_buffer(const void *data, GLuint size);
		~vertex_buffer();

		void bind() const;
		void unbind() const;
};

#endif
