#include "config.h"
#include <SFML/Graphics.hpp>
#include "libraries/imgui/imgui.h";
#include "libraries/imgui/imgui-SFML.h";
bool isMouseOverImGuiWindow(sf::RenderWindow *window)
{
    sf::Vector2i mousePos= sf::Mouse::getPosition(*window);

    if(mousePos.x>600 && mousePos.x < 900 &&mousePos.y>700 && mousePos.y < 900)return true;
    else return false;
}
void renderImGuiWindow(CONFIG& config)
{
    ImGui::SetNextWindowSize(ImVec2(300, 200));
    ImGui::SetNextWindowPos(ImVec2(config.WINDOW_WIDTH - 300, config.WINDOW_HEIGHT - 200));
    ImGui::Begin("SFML ImGui Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::SliderInt("Grid Size", &config.gridSize, 10, 100);

    ImGui::ListBox("Algorithms", &config.selectedAlgorithm, config.algorithmsList, IM_ARRAYSIZE(config.algorithmsList));

    if (ImGui::Button("Start"))
    {
        config.isStartClicked = true;
    }

    ImGui::End();
}
