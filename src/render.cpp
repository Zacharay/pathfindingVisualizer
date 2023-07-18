#include <SFML/Graphics.hpp>
#include "Grid/Grid.h"
#include "Algorithms/BFS.h"
#include <thread>
#include <iostream>
#include "mouseEventHandler.h"
#include <SFML/Graphics.hpp>
#include "libraries/imgui/imgui.h";
#include "libraries/imgui/imgui-SFML.h";
#include <string>
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
bool isMouseOverImGuiWindow(sf::RenderWindow *window)
{
    sf::Vector2i mousePos= sf::Mouse::getPosition(*window);

    if(mousePos.x>600 && mousePos.x < 900 &&mousePos.y>700 && mousePos.y < 900)return true;
    else return false;
}

struct CONFIG{
    int gridSize = 50;
    const char* algorithmsList[2]= {"Breadth First Search","Depth First Search"};
    int selectedAlgorithm;
    bool isStartClicked=false;
};

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

bool stopMouseEvents = false;
void processEvents(sf::RenderWindow &window,Grid &gridObj)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if(event.type==sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Enter)
        {
            stopMouseEvents = true;
            visualizeBfs(&gridObj,&window);
        }
        if(!stopMouseEvents&&!isMouseOverImGuiWindow(&window))
        {
            handleMouseEvents(&gridObj,&window,&event);
        }

    }
}

void renderLoop()
{
    const int WINDOW_WIDTH=900;
    const int WINDOW_HEIGHT=900;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    Grid grid(WINDOW_WIDTH);
    initializeTileColors();

    const int targetFrameRate = 30;
    const sf::Time frameTime = sf::seconds(1.f / targetFrameRate);

    sf::Clock clock;
    sf::Time elapsedTime;

    ImGui::SFML::Init(window);

    CONFIG config;

    while (window.isOpen())
    {
        processEvents(window,grid);

        elapsedTime += clock.restart();
        if (elapsedTime >= frameTime)
        {
            renderGrid(&grid,&window);
            ImGui::SFML::Update(window, frameTime);
            ImGui::SetNextWindowSize(ImVec2(300, 200));
            ImGui::SetNextWindowPos(ImVec2(WINDOW_WIDTH - 300, WINDOW_HEIGHT - 200));

            ImGui::Begin("SFML ImGui Window",nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

            ImGui::SliderInt("Grid Size", &config.gridSize, 10, 100);

            ImGui::ListBox("Algorithms",&config.selectedAlgorithm,config.algorithmsList,IM_ARRAYSIZE(config.algorithmsList));

            if (ImGui::Button("Start"))
            {
                config.isStartClicked = true;
            }
            ImGui::End();

            ImGui::SFML::Render(window);
            window.display();
            elapsedTime -= frameTime;
        }

    }
    ImGui::SFML::Shutdown();
}
