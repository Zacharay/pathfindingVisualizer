#include <SFML/Graphics.hpp>
#include "Grid/Grid.h"
#include "Algorithms/PatternGeneration/visualizePattern.h"
#include "Algorithms/Pathfinding/visualizePathfinding.h"
#include <thread>
#include <atomic>
#include <iostream>
#include "mouseEventHandler.h"
#include <SFML/Graphics.hpp>
#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui-SFML.h"
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
void processEvents(sf::RenderWindow *window,Grid *gridObj,CONFIG *config)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if(config->isResizeClicked)
        {
            gridObj->resizeGrid(config->gridSize,config->WINDOW_WIDTH);
            renderGrid(gridObj,window);
            switch(gridObj->gridSize)
            {
                case 25:
                    config->substep= 1;
                    break;
                case 45:
                    config->substep=2;
                    break;
                case 75:
                    config->substep=3;
                    break;
            }
            config->isResizeClicked = false;
        }
        if(config->isClearWallsClicked)
        {
            gridObj->clearWalls();
            renderGrid(gridObj,window);
            config->isClearWallsClicked = false;
        }
        if(config->isPatternStarted&&!isAlgorithmStarted)
        {
            isAlgorithmStarted= true;
            visualizePattern(gridObj,window,config);
            config->isPatternStarted = false;
            isAlgorithmStarted=false;
        }
        if(config->isPathfindingStarted&&!isAlgorithmStarted)
        {
            isAlgorithmStarted= true;
            visualizePathfinding(gridObj,window,config);

            isAlgorithmStarted = false;
            config->isPathfindingStarted = false;
        }
        if(!(config->isPathfindingStarted||config->isPatternStarted)&&!isMouseOverImGuiWindow(window,config))
        {
            handleMouseEvents(gridObj,window,&event);
        }

    }
}


void renderLoop()
{
    CONFIG config;
    sf::RenderWindow window(sf::VideoMode(config.WINDOW_WIDTH+config.GUI_WIDTH, config.WINDOW_HEIGHT), "SFML window");
    Grid grid(config.WINDOW_WIDTH);
    initializeTileColors();

    ImGui::SFML::Init(window);

    renderGrid(&grid,&window);
    sf::Clock deltaClock;

    while (window.isOpen())
    {
            processEvents(&window,&grid,&config);

            ImGui::SFML::Update(window, deltaClock.restart());

            renderImGuiWindow(&config,&grid,&window);

            ImGui::SFML::Render(window);
            window.display();

    }
    ImGui::SFML::Shutdown();
}
