#include <SFML/Graphics.hpp>
#include "Grid/Grid.h"

static sf::Color tileColors[6];
void initializeTileColors()
{
    tileColors[TileState::notVisited] = sf::Color::White;
    tileColors[TileState::visited] = sf::Color::Cyan;
    tileColors[TileState::active] = sf::Color::Green;
    tileColors[TileState::wall] =sf::Color::Black;
    tileColors[TileState::source]= sf::Color::Yellow;
    tileColors[TileState::destination]= sf::Color::Red;

}
void renderGrid(Grid *gridObj,sf::RenderWindow *window)
{

    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(gridObj->tileSize, gridObj->tileSize));
    tile.setOutlineThickness(1.0f);
    tile.setOutlineColor(sf::Color::Black);

    for(int i=0;i<gridObj->gridSize;i++)
    {
        for(int j=0;j<gridObj->gridSize;j++)
        {
            tile.setFillColor(tileColors[gridObj->grid[i][j].state]);
            tile.setPosition(i*gridObj->tileSize,j*gridObj->tileSize);
            window->draw(tile);
        }
    }

}


void renderLoop()
{
    const int WINDOW_WIDTH=900;
    const int WINDOW_HEIGHT=900;
    sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    Grid grid(WINDOW_WIDTH);
    initializeTileColors();
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        app.clear();
        renderGrid(&grid,&app);
        app.display();
    }
}
