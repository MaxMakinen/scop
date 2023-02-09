/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:18:58 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/09 12:19:00 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "error_handling.hpp"

void	GLClearError()
{
	while(glGetError() != GL_NO_ERROR); // GL_NO_ERROR guaranteed to be 0. so could be !glGetError()
}

bool	GLLogCall(const char *function, const char *file, int line)
{
	while(GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " 
		<< function << " " << file << ":" << line << std::endl;
		return (false);
	}
	return (true);
}

