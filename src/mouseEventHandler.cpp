#include "mouseEventHandler.h"
#include "Grid/Vector2.h"
#include "Render/tileRenderer.h"
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
                        gridObj->grid[mousePos.row][mousePos.col].setState(TileState::wall);
                    }
                    renderGrid(window);
                }
}

Tile *movingTile = nullptr;
bool hasTileMoved = false;

void moveTile(sf::RenderWindow *window,Grid *gridObj)
{
        Vector2 mousePos = getMousePosition(window,gridObj);
        if(gridObj->grid[mousePos.row][mousePos.col].state ==TileState::wall)return;
        hasTileMoved=true;

        bool tilePosChanged= false;



        if(movingTile->state==TileState::source)
        {
            Vector2 srcCoords = gridObj->sourceCoords;
            gridObj->grid[srcCoords.row][srcCoords.col].setState(TileState::notVisited);
            gridObj->sourceCoords=mousePos;
            if(movingTile != &gridObj->grid[mousePos.row][mousePos.col])tilePosChanged = true;

            movingTile = &gridObj->grid[mousePos.row][mousePos.col];
            movingTile->setState(TileState::source);
        }
        else
        {
            Vector2 destCoords = gridObj->destCoords;
            gridObj->grid[destCoords.row][destCoords.col].setState(TileState::notVisited);
            gridObj->destCoords=mousePos;

            if(movingTile != &gridObj->grid[mousePos.row][mousePos.col])tilePosChanged = true;

            movingTile = &gridObj->grid[mousePos.row][mousePos.col];
            movingTile->setState(TileState::destination);
        }

        if(tilePosChanged)renderGrid(window);

}

void handleMouseEvents(Grid *gridObj,sf::RenderWindow *window,sf::Event *event){

        if(event->type==sf::Event::MouseButtonPressed&&event->mouseButton.button==sf::Mouse::Left&&movingTile==nullptr)
        {
            Vector2 mousePos = getMousePosition(window,gridObj);
            Tile *currentTile = &gridObj->grid[mousePos.row][mousePos.col];
            bool isSpecialTile =
            currentTile->state==TileState::source||
            currentTile->state==TileState::destination;

            if(isSpecialTile)
            {
                hasTileMoved = false;
                movingTile = currentTile;
            }
            else{
                drawWalls(window,gridObj);
            }

        }
        if(event->type==sf::Event::MouseButtonPressed&&event->mouseButton.button==sf::Mouse::Left&&movingTile!=nullptr&&hasTileMoved)
        {
            movingTile = nullptr;
            renderGrid(window);
        }
        if(event->type==sf::Event::MouseMoved&&movingTile!=nullptr)
        {
            moveTile(window,gridObj);
        }

}
