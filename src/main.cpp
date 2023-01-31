#include <iostream>
#include "../include/scop.hpp"


int main()
{
	std::cout << "Borg\n";
    sf::Window window(sf::VideoMode(800, 600), "My Window");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
	std::cout << "Bananaman\n";
    return 0;
}