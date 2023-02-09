/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:20:39 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/09 12:20:40 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_HPP
# define ERROR_HANDLING_HPP

#include <signal.h>
#include <GL/glew.h>

#ifdef SIGTRAP
//# define ASSERT(x) if (!(x)) __builtin_trap()
# define ASSERT(x) if (!(x)) raise(SIGTRAP)
#else
# define ASSERT(x) if (!(x)) raise(SIGABRT)
#endif
#define GLCall(x) do { GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__)); } while (0)

void	GLClearError();
bool	GLLogCall(const char *function, const char *file, int line);

#endif