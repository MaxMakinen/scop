/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:46 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/09 12:01:48 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
// TODO can i remove stream includes?
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "renderer.hpp"
#include "error_handling.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer_layout.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vector.hpp"

int main(void)
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

	window.setFramerateLimit(60);

	// initialize GLEW after creating a valid OpenGL rendering context. Automatically done by SFML in previous command
	if(glewInit() != GLEW_OK)
		std::cout << "Error!: glewInit not ok" << std::endl;

    // load resources, initialize the OpenGL states, ...

	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, //0
		 0.5f, -0.5f, 1.0f, 0.0f, //1
		 0.5f,  0.5f, 1.0f, 1.0f, //2
		-0.5f,  0.5f, 0.0f, 1.0f  //3
	};

	unsigned int	indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Enable blending and set blending rules
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	vertex_array va;

	vertex_buffer vb(positions, 4 * 4 * sizeof(float));

	vertex_buffer_layout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.add_buffer(vb, layout);

	index_buffer ib(indices, 6);

	// Create projection matrix
	mat4x4f proj;
	//proj.ortho(-2.0f, 2.0f, -1.5f, 1.5f);
	//proj.orthographic(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	proj.perspective(window.getSize().x, window.getSize().y, 0.1f, 100.0f, 90.0f);
	proj.invert();
	
	// Load shaders
	shader shader("../resources/shaders/basic.shader");
	shader.bind();
	shader.set_uniform_4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
	shader.set_uniform_mat4f("u_MVP", proj);

	// Load texture
	texture texture("../resources/textures/dickbutt.png");
	texture.bind();
	shader.set_uniform_1i("u_texture", 0);

	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();
	texture.unbind();

	renderer renderer;
    // run the main loop
    bool running = true;
	float r = 0.0f;
	float increment = 0.05f;
    while (running)
    {

        // clear the buffers
		renderer.clear();

        // draw...
		shader.bind();
		texture.bind();
		shader.set_uniform_4f("u_color", r, 0.3f, 0.8f, 1.0f);

		renderer.draw(va, ib, shader);

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;
		r += increment;
        // end the current frame (internally swaps the front and back buffers)
        window.display();

        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				running = false;
				break;
			}
            else if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
				// adjust perspective projection matrix if window resized.
				proj.perspective_resize(event.size.height, event.size.width);
				shader.set_uniform_mat4f("u_MVP", proj);
            }
        }
    }

    // release resources...
	window.setActive(false);

    return (0);
}
