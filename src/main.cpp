/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakinen <mmakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:01:46 by mmakinen          #+#    #+#             */
/*   Updated: 2023/02/24 16:43:51 by mmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"
#include "error_handling.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer_layout.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vector.hpp"
#include "mesh.hpp"

void controls(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main(void)
{
	float	height = 600.f;
	float	width = 800.f;
	
	/* Initialise the GLFW library*/
	if (!glfwInit())
		return (-1);

	/* Tell GLFW what version of OpenGl We're using*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its openGL Context*/
	GLFWwindow *window = glfwCreateWindow(width, height, "~ Scop ~", NULL ,NULL);
	if (window == NULL)
	{
		std::cout << "Error!: Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return (-1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	/* initialize GLEW after creating a valid OpenGL rendering context. */
	if(glewInit() != GLEW_OK)
		std::cout << "Error!: glewInit not ok." << std::endl;

	/* Specify the wievport of OpenGL in the window.
	In this case the viewport goes from x = 0, y = 0 to x = width, y = height*/
	GLCall(glViewport(0, 0, width, height));

	/* Set framerate */
	//glfwSwapInterval(30);

	/* Set keyboard controls */
	glfwSetKeyCallback(window, controls);

	/* Get info of GPU and supported OpenGL vesion*/
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << std::endl;

    // load resources, initialize the OpenGL states, ...

	// Vertices coordinates
	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4
	};


	// Enable blending and set blending rules
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	// Load shaders
	shader shader("resources/shaders/basic.glsl");
	shader.bind();

	// Generates Vertex Array Object and binds it
	vertex_array VAO1;
	VAO1.bind();

	// Generates Vertex Buffer Object and links it to vertices
	vertex_buffer VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	index_buffer EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	// Unbind all to prevent accidentally modifying them
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shader.get_id(), "scale");

	// Load texture
	texture texture("resources/textures/brick.png");
	texture.texUnit(shader, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shader.bind();
	
		double	crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

		mat4x4f	model;
		mat4x4f	view;
		mat4x4f	proj;
		vec3f	axis(0.0f, 1.0f, 0.0f);

	//	model.rotate(rotation, axis);
		view.translate((vec3f){0.0f, -0.5f, -2.0f});
		proj.perspective((float)height, (float)width, 0.1f, 100.0f, 45.f);

		int model_loc;
		GLCall(model_loc = glGetUniformLocation(shader.get_id(), "model"));
		GLCall(glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]));
		int view_loc;
		GLCall(view_loc = glGetUniformLocation(shader.get_id(), "view"));
		GLCall(glUniformMatrix4fv(view_loc, 1, GL_TRUE, &view[0][0]));
		int proj_loc;
		GLCall(proj_loc = glGetUniformLocation(shader.get_id(), "proj"));
		GLCall(glUniformMatrix4fv(proj_loc, 1, GL_TRUE, &proj[0][0]));


		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		texture.bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
//
//        // clear the buffers
//		renderer.clear();
//
//        // draw...
//		shader.bind();
//		texture.bind();
//		shader.set_uniform_4f("u_color", r, 0.3f, 0.8f, 1.0f);
//
//		renderer.draw(va, ib, shader);
//
//		if (r > 1.0f)
//			increment = -0.05f;
//		else if (r < 0.0f)
//			increment = 0.05f;
//		r += increment;
//        // end the current frame (internally swaps the front and back buffers)
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events*/
//		glfwPollEvents();
    }

    // Destroy window before ending program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending program
	glfwTerminate();
    return (0);
}
