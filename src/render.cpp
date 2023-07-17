#include <SFML/Graphics.hpp>
#include "Grid/Grid.h"
#include "Algorithms/BFS.h"
#include <thread>
#include <iostream>

static sf::Color tileColors[6];
void initializeTileColors()
{
    tileColors[TileState::notVisited] = sf::Color::White;
    tileColors[TileState::visited] = sf::Color::Cyan;
    tileColors[TileState::active] = sf::Color::Yellow;
    tileColors[TileState::wall] =sf::Color::Black;
    tileColors[TileState::source]= sf::Color::Green;
    tileColors[TileState::destination]= sf::Color::Red;

}
void renderGrid(Grid *gridObj,sf::RenderWindow *window)
{
    window->clear();
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(gridObj->tileSize, gridObj->tileSize));
    tile.setOutlineThickness(1.0f);
    tile.setOutlineColor(sf::Color::Black);

    for(int row=0;row<gridObj->gridSize;row++)
    {
        for(int col=0;col<gridObj->gridSize;col++)
        {
            tile.setFillColor(tileColors[gridObj->grid[row][col].state]);
            tile.setPosition(col*gridObj->tileSize,row*gridObj->tileSize);
            window->draw(tile);
        }
    }
    window->display();
}
bool stopWallDrawing = false;

void processEvents(sf::RenderWindow &app,Grid &gridObj)
{
    sf::Event event;
    while (app.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            app.close();
        }
        //draw walls
        if(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left&&!stopWallDrawing)
        {

            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {

                    sf::Vector2i mousePosition = sf::Mouse::getPosition(app);
                    int mouseX = mousePosition.x/gridObj.tileSize;
                    int mouseY = mousePosition.y/gridObj.tileSize;

                    if(gridObj.grid[mouseY][mouseX].state==TileState::notVisited)
                    {
                        gridObj.grid[mouseY][mouseX].state =TileState::wall;
                    }
                    renderGrid(&gridObj,&app);
                    sf::Event tempEvent;
                    while (app.pollEvent(tempEvent));
                }
        }
        if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Enter)
        {
            stopWallDrawing=true;
            visualizeBfs(&gridObj,&app);
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

        processEvents(app,grid);
        renderGrid(&grid,&app);
    }
}
