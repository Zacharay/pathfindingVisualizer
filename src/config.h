#pragma once
struct CONFIG{
    static const int WINDOW_WIDTH=900;
    static const int WINDOW_HEIGHT=900;
    static const int GUI_WIDTH=300;
    static const int GUI_HEIGHT = 900;

    int gridSize = 45;
    int substep = 2;
    int visualizationSpeed = 10;//max 10 min 1
    const char* algorithmsList[4]= {"Breadth First Search","Depth First Search","A*","Greedy Best First Search"};
    int selectedAlgorithm=0;
    const char* patternList[4]= {"Kruskal Maze","Prim Maze","Outer Spiral","Inner Spiral"};
    int selectedPattern=0;


    //buttons
    bool isPathfindingStarted= false;
    bool isPatternStarted = false;
    bool isClearWallsClicked = false;
    bool isResizeClicked = false;
};
