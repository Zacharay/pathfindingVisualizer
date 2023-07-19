#pragma once
struct CONFIG{
    static const int WINDOW_WIDTH=900;
    static const int WINDOW_HEIGHT=900;

    int gridSize = 50;
    const char* algorithmsList[2]= {"Breadth First Search","Depth First Search"};
    int selectedAlgorithm=0;
    bool isStartClicked=false;
};
