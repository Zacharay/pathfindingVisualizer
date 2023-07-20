#include "config.h"
#include <SFML/Graphics.hpp>
#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui-SFML.h"
#include "Grid/Grid.h"
#include "render.h"
#include "iostream"

bool isMouseOverImGuiWindow(sf::RenderWindow *window,CONFIG *config)
{
    sf::Vector2i mousePos= sf::Mouse::getPosition(*window);

    if(mousePos.x>config->WINDOW_WIDTH && mousePos.x < config->WINDOW_WIDTH+config->GUI_WIDTH)return true;
    else return false;
}

void renderImGuiWindow(CONFIG *config,Grid *gridObj,sf::RenderWindow *window)
{
    ImGui::SetNextWindowSize(ImVec2(config->GUI_WIDTH, config->GUI_HEIGHT));
    ImGui::SetNextWindowPos(ImVec2(config->WINDOW_WIDTH , 0));
    ImGui::Begin("SFML ImGui Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::Text("Grid Size");
    ImGui::RadioButton("Small", &config->gridSize, 25);
    ImGui::RadioButton("Medium", &config->gridSize, 45);
    ImGui::RadioButton("Big", &config->gridSize, 75);

    if (ImGui::Button("Resize"))
    {
        config->isResizeClicked = true;
    }

    ImGui::SliderInt("Speed" , &config->visualizationSpeed,1,100);

    ImGui::Combo("Algorithms", &config->selectedAlgorithm, config->algorithmsList, IM_ARRAYSIZE(config->algorithmsList));

    if (ImGui::Button("Clear Walls"))
    {
        config->isClearWallsClicked = true;
    }
    if (ImGui::Button("Start"))
    {
        config->isStartClicked = true;
    }


    ImGui::End();
}
