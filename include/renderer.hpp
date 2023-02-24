/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:07 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 10:37:52 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDERER_HPP
# define RENDERER_HPP

# include <GL/glew.h>

# include "error_handling.hpp"
# include "vertex_array.hpp"
# include "index_buffer.hpp"
# include "shader.hpp"

class renderer
{
	private:

	public:
	void draw(const vertex_array &va, const index_buffer &ib, const shader &shader) const;
	void clear() const;
};

#endif