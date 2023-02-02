#include <iostream>
#include "../include/scop.hpp"



int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

	// initialize GLEW after creating a valid OpenGL rendering context. Automatically done by SFML in previous command
	if(glewInit() != GLEW_OK)
		std::cout << "Error!: glewInit not ok" << std::endl;

    // load resources, initialize the OpenGL states, ...

	float positions[6] = {
		-0.5, -0.5f,
		0.0, 0.5f,
		0.5, -0.5f,
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	// glBindBuffer(GL_ARRAY_BUFFER, 0);
    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
		glDrawArrays(GL_TRIANGLES, 0, 3);

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...
	window.setActive(false);

    return (0);
}