#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        app.clear();

        app.display();
    }

    return EXIT_SUCCESS;
}
