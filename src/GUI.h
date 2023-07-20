#pragma once
#include "config.h"
#include <SFML/Graphics.hpp>
#include "Grid/Grid.h"
bool isMouseOverImGuiWindow(sf::RenderWindow *window,CONFIG *config);
void renderImGuiWindow(CONFIG *config,Grid *gridObj,sf::RenderWindow *window);
