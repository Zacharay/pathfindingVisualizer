#include <SFML/Graphics.hpp>
#include "../Algorithms/PatternGeneration/visualizePattern.h"
#include "../Algorithms/Pathfinding/visualizePathfinding.h"
#include <iostream>
#include "../mouseEventHandler.h"
#include "../libraries/imgui/imgui.h"
#include "../libraries/imgui/imgui-SFML.h"
#include "../config.h"
#include "../GUI.h"
#include "tileRenderer.h"

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
            gridObj->resizeGrid(config->gridSize,config->WINDOW_WIDTH,*config);
            renderGrid(window);
            config->isResizeClicked = false;
        }
        if(config->isClearWallsClicked)
        {
            gridObj->clearPath();
            gridObj->clearWalls();
            renderGrid(window);
            config->isClearWallsClicked = false;
        }
        if(config->isPatternStarted&&!isAlgorithmStarted)
        {
            isAlgorithmStarted= true;
            gridObj->clearPath();
            gridObj->clearWalls();
            visualizePattern(gridObj,window,config);
            config->isPatternStarted = false;
            isAlgorithmStarted=false;
        }
        if(config->isPathfindingStarted&&!isAlgorithmStarted)
        {
            isAlgorithmStarted= true;
            gridObj->clearPath();
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
    Grid gridObj(config.WINDOW_WIDTH);
    initializeTileColors();
    initializeGridTexture(config,gridObj);
    renderGrid(&window);

    ImGui::SFML::Init(window);




    sf::Clock deltaClock;

    while (window.isOpen())
    {
            processEvents(&window,&gridObj,&config);

            ImGui::SFML::Update(window, deltaClock.restart());

            renderImGuiWindow(&config,&gridObj,&window);

            ImGui::SFML::Render(window);
            window.display();

    }
    ImGui::SFML::Shutdown();
}
