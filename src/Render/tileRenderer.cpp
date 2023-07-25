#include "tileRenderer.h"

static sf::Color tileColors[7];
static sf::RenderTexture gridTexture;

void initializeTileColors()
{
    tileColors[TileState::notVisited] = sf::Color(240, 240, 240);
    tileColors[TileState::visited] = sf::Color(135, 206, 250);
    tileColors[TileState::inQueue] = sf::Color(255, 165, 0);
    tileColors[TileState::path] = sf::Color::Yellow;
    tileColors[TileState::wall] =sf::Color(0, 11, 33);
    tileColors[TileState::source]= sf::Color(41, 255, 87);
    tileColors[TileState::destination]= sf::Color(220,20,60);

}
void initializeGridTexture(const CONFIG& config,const Grid &gridObj)
{
    gridTexture.create(config.WINDOW_WIDTH,config.WINDOW_HEIGHT);
    for(int row=0;row<gridObj.gridSize;row++)
        for(int col=0;col<gridObj.gridSize;col++)
            updateTile(gridObj.grid[row][col]);

}
void renderGrid(sf::RenderWindow *window)
{
    window->clear();
    window->draw(sf::Sprite(gridTexture.getTexture()));
    window->display();
}
void updateTile(const Tile &tile)
{
    sf::RectangleShape tileShape;
    tileShape.setSize(sf::Vector2f(tile.tileSize-1, tile.tileSize-1));
    tileShape.setOutlineThickness(1.0f);
    tileShape.setOutlineColor(sf::Color(0, 11, 33));
    tileShape.setFillColor(tileColors[tile.state]);
    tileShape.setPosition(tile.pos.col*tile.tileSize,tile.pos.row*tile.tileSize);

    gridTexture.draw(tileShape);
    gridTexture.display();
}
