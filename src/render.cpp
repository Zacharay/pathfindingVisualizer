#include <SFML/Graphics.hpp>
#include "Grid/Grid.h"
#include "Algorithms/algorithms.h"
#include <thread>
#include <iostream>
#include "mouseEventHandler.h"
#include <SFML/Graphics.hpp>
#include "libraries/imgui/imgui.h";
#include "libraries/imgui/imgui-SFML.h";
#include "config.h"
#include "GUI.h"

static sf::Color tileColors[6];
void initializeTileColors()
{
    tileColors[TileState::notVisited] = sf::Color::White;
    tileColors[TileState::visited] = sf::Color::Cyan;
    tileColors[TileState::path] = sf::Color::Yellow;
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
bool isAlgorithmStarted = false;
void processEvents(sf::RenderWindow &window,Grid &gridObj,CONFIG &config)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if(config.isStartClicked&&!isAlgorithmStarted)
        {
            isAlgorithmStarted= true;
            if(config.selectedAlgorithm==0)
            {
                visualizeBfs(&gridObj,&window,&config);
            }
            else if(config.selectedAlgorithm==1)
            {
                visualizeDfs(&gridObj,&window,&config);
            }

        }
        if(!config.isStartClicked&&!isMouseOverImGuiWindow(&window))
        {
            handleMouseEvents(&gridObj,&window,&event);
        }

    }
}


void renderLoop()
{
    CONFIG config;
    sf::RenderWindow window(sf::VideoMode(config.WINDOW_WIDTH, config.WINDOW_HEIGHT), "SFML window");
    Grid grid(config.WINDOW_WIDTH);
    initializeTileColors();

    ImGui::SFML::Init(window);

    renderGrid(&grid,&window);

    sf::Clock deltaClock;
    while (window.isOpen())
    {
            processEvents(window,grid,config);

            ImGui::SFML::Update(window, deltaClock.restart());

            renderImGuiWindow(config);

            ImGui::SFML::Render(window);
            window.display();

    }
    ImGui::SFML::Shutdown();
}
