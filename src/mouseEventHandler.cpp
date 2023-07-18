#include "mouseEventHandler.h"
#include "Grid/Vector2.h"
#include "render.h"
#include "iostream"

Vector2 getMousePosition(sf::RenderWindow *window,Grid *gridObj)
{
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
        int mouseX = mousePosition.x/gridObj->tileSize;
        int mouseY = mousePosition.y/gridObj->tileSize;
        return Vector2(mouseX,mouseY);
}
void drawWalls(sf::RenderWindow *window,Grid *gridObj)
{
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {

                    Vector2 mousePos = getMousePosition(window,gridObj);

                    if(gridObj->grid[mousePos.row][mousePos.col].state==TileState::notVisited)
                    {
                        gridObj->grid[mousePos.row][mousePos.col].state =TileState::wall;
                    }
                    renderGrid(gridObj,window);
                }
}
void moveTile(sf::RenderWindow *window,Grid *gridObj,Tile currentTile)
{

    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        Vector2 mousePos = getMousePosition(window,gridObj);
        currentTile = gridObj->grid[mousePos.row][mousePos.col];
        std::cout<<currentTile.state<<std::endl;
        int state = 0;
        if(currentTile.state==TileState::source)
        {
            Vector2 srcCoords = gridObj->sourceCoords;
            gridObj->grid[srcCoords.row][srcCoords.col].state=TileState::notVisited;

            gridObj->sourceCoords=mousePos;

        }
        gridObj->grid[mousePos.row][mousePos.col].state= TileState::source;
        renderGrid(gridObj,window);
    }

}

void handleMouseEvents(Grid *gridObj,sf::RenderWindow *window,sf::Event *event){


        if(event->type==sf::Event::MouseButtonPressed&&event->mouseButton.button==sf::Mouse::Left)
        {
            Vector2 mousePos = getMousePosition(window,gridObj);
            Tile currentTile = gridObj->grid[mousePos.row][mousePos.col];
            bool isSpecialTile =
            currentTile.state==TileState::source||
            currentTile.state==TileState::destination;

            if(isSpecialTile)
            {
                moveTile(window,gridObj,currentTile);
            }
            else{
                //drawWalls(window,gridObj);
            }

        }

}
