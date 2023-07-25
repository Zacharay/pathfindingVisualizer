#include "mouseEventHandler.h"
#include "Grid/Vector2.h"
#include "Render/tileRenderer.h"
#include "iostream"

bool isMouseInsideGrid(const int windowWidth, const int windowHeight,const sf::RenderWindow &window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if( mousePosition.x >0 && mousePosition.x < windowWidth&&
        mousePosition.y >0 && mousePosition.y < windowHeight)
    {
        return true;
    }

    return false;
}

Vector2 getMousePosition(const sf::RenderWindow &window,const Grid &gridObj)
{
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int mouseX = mousePosition.x/gridObj.tileSize;
        int mouseY = mousePosition.y/gridObj.tileSize;
        return Vector2(mouseX,mouseY);
}
void drawWalls(sf::RenderWindow &window,Grid &gridObj)
{
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                            if(!isMouseInsideGrid(900,900,window))
                            {
                                return;
                            }
                    Vector2 mousePos = getMousePosition(window,gridObj);

                    if(gridObj.grid[mousePos.row][mousePos.col].state==TileState::notVisited)
                    {
                        gridObj.grid[mousePos.row][mousePos.col].setState(TileState::wall);
                    }
                    renderGrid(&window);
                }
}

Tile *movingTile = nullptr;
bool hasTileMoved = false;

void moveTile(const int windowWidth,const int windowHeight,sf::RenderWindow &window,Grid &gridObj)
{
        Vector2 mousePos = getMousePosition(window,gridObj);
        if(
            gridObj.grid[mousePos.row][mousePos.col].state ==TileState::wall||
            gridObj.grid[mousePos.row][mousePos.col].state == TileState::source||
            gridObj.grid[mousePos.row][mousePos.col].state == TileState::destination){
            return;
        }
        if(!isMouseInsideGrid(windowWidth,windowHeight,window))
        {
            movingTile = nullptr;
            return;
        }


        hasTileMoved=true;

        bool tilePosChanged= false;



        if(movingTile->state==TileState::source)
        {
            gridObj.srcTile->setState(TileState::notVisited);

            if(movingTile != &gridObj.grid[mousePos.row][mousePos.col])tilePosChanged = true;

            movingTile = &gridObj.grid[mousePos.row][mousePos.col];
            gridObj.srcTile = movingTile;
            gridObj.srcTile->setState(TileState::source);
        }
        else
        {
            gridObj.destTile->setState(TileState::notVisited);

            if(movingTile != &gridObj.grid[mousePos.row][mousePos.col])tilePosChanged = true;

            movingTile = &gridObj.grid[mousePos.row][mousePos.col];
            gridObj.destTile =movingTile;
            gridObj.destTile->setState(TileState::destination);

        }
        if(tilePosChanged)renderGrid(&window);


}

void handleMouseEvents(const int windowWidth,const int windowHeight,Grid &gridObj,sf::RenderWindow &window,const sf::Event &event){



        if(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left&&movingTile==nullptr)
        {
            Vector2 mousePos = getMousePosition(window,gridObj);
            Tile *currentTile = &gridObj.grid[mousePos.row][mousePos.col];
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
        if(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left&&movingTile!=nullptr&&hasTileMoved)
        {
            movingTile = nullptr;
            renderGrid(&window);
        }
        if(event.type==sf::Event::MouseMoved&&movingTile!=nullptr)
        {
            moveTile(windowWidth,windowHeight,window,gridObj);
        }

}
