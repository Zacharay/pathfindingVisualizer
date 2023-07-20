#pragma once
struct CONFIG{
    static const int WINDOW_WIDTH=900;
    static const int WINDOW_HEIGHT=900;
    static const int GUI_WIDTH=300;
    static const int GUI_HEIGHT = 900;

    int gridSize = 50;
    int visualizationSpeed = 100;//max 100 min 1
    const char* algorithmsList[2]= {"Breadth First Search","Depth First Search"};
    int selectedAlgorithm=0;
    bool isStartClicked=false;
    bool isResizeClicked = false;
};
