#ifndef _SFML_GRAPHICS_HPP_
#define _SFML_GRAPHICS_HPP_


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

enum directions {north, south, west, east};

class snakeHead{
    sf::Color eyeColor = sf::Color(25, 25, 25);
    private:
        sf::RectangleShape headRect;
        sf::RectangleShape eyeRectW;
        sf::RectangleShape eyeRectE;
        sf::Vector2f position;
        sf::Color headColor;
    public:
        snakeHead(sf::Vector2f rectSize, sf::Color color);
        void setHeadPosition(sf::Vector2f pos, float divWidth);
        sf::RectangleShape getHead(){return headRect;}
        vector<sf::RectangleShape*> getDrawables(){return vector<sf::RectangleShape*>{&headRect, &eyeRectW, &eyeRectE};}
};

snakeHead::snakeHead(sf::Vector2f rectSize, sf::Color color){
    headRect = sf::RectangleShape(rectSize);
    headColor = color;
    headRect.setFillColor(color);

    // Eyes are named as if the snake is looking upwards with eyeRectW being west and eyeRectE being east
    eyeRectW = sf::RectangleShape(sf::Vector2f(rectSize.x*0.1, rectSize.y*0.1));
    eyeRectW.setFillColor(eyeColor);
    eyeRectE = sf::RectangleShape(sf::Vector2f(rectSize.x*0.1, rectSize.y*0.1));
    eyeRectE.setFillColor(eyeColor);
}

void snakeHead::setHeadPosition(sf::Vector2f pos, float divWidth){
    // divWidth is only needed to move the snake's eyes
    position = pos;
    headRect.setPosition(pos);

    //cout << "head position: " << pos.x << " and " << pos.y << endl;
    //cout << "left eye position: " << pos.x+(divWidth*0.3) << " and " << pos.y+(divWidth*0.25) << endl;
    //cout << "right eye position: " << pos.x+(divWidth*0.6) << " and " << pos.y+(divWidth*0.25) << endl << endl;

    eyeRectW.setPosition(sf::Vector2f(pos.x+(divWidth*0.3), pos.y+(divWidth*0.25)));
    eyeRectE.setPosition(sf::Vector2f(pos.x+(divWidth*0.6), pos.y+(divWidth*0.25)));
}


// CREATE A FUNCTION TO OBTAIN POSITION IN GRID OF ADJACENT ELEMENT BY USING AN ENUM DATATYPE (UP, DOWN, LEFT, RIGHT)
class gameMatrix{
    private:
        sf::RenderWindow* masterWindow;
        unsigned int numDivs;
        float divWidth;
        vector<vector<sf::Vector2f>> gridMatrix;
        vector<vector<sf::Vertex>> linesVector;     // Cannot use a vector of sf::Vertex[2] arrays so we are using a vector of sf::Vertex vectors
        sf::Vector2f middlePos;
    public:
        gameMatrix(sf::RenderWindow &master, unsigned int numDivs);
        vector<vector<sf::Vector2f>> getGridMatrix(){return gridMatrix;}
        vector<vector<sf::Vertex>> getLinesVector(){return linesVector;}
        sf::Vector2f getMiddlePos(){return middlePos;}
        sf::Vector2f getDivWidth(){return sf::Vector2f(divWidth, divWidth);}
        sf::Vector2f getAdjacentPos(directions dir, sf::Vector2f currentPos);
};

gameMatrix::gameMatrix(sf::RenderWindow &master, unsigned int nDivs){
    unsigned int i=0, j=0;
    vector<sf::Vector2f> rowPositions;
    vector<sf::Vertex> currentLine;
    
    if (master.getSize().x != master.getSize().y){
        throw invalid_argument("game is designed for window to be a square");
    }
    masterWindow = &master;

    if (nDivs == 0){
        throw invalid_argument("number of divs is equal to zero");
    }
    numDivs = nDivs;

    if (((float)(masterWindow->getSize().x)) / ((float)numDivs-1) < 5.f){
        throw invalid_argument("number of divs is not small enough, which results in the width of each division being too small");
    }
    if (numDivs <= 2){
        throw invalid_argument("number of divs is too small, it is recommended to be above 10-20");
    }
    divWidth = ((float)(masterWindow->getSize().x)) / ((float)(numDivs-1));

    // Generating matrix of snake's coordinates
    for(i=0; i<numDivs; i++){
        rowPositions.clear();
        for (j=0; j<numDivs; j++){
            rowPositions.push_back(sf::Vector2f(i*divWidth, j*divWidth));
        }
        gridMatrix.push_back(rowPositions);
    }

    // Generating line grid to view the matrix
    // Vertical lines:
    for (i=0; i<gridMatrix[0].size(); i++){
        currentLine.clear();
        currentLine.push_back(sf::Vertex(gridMatrix[0][i]));
        currentLine.push_back(sf::Vertex(gridMatrix[(gridMatrix.size()-1)][i]));
        linesVector.push_back(currentLine);
    }
    // Horizontal lines
    for (i=0; i<gridMatrix.size(); i++){
        currentLine.clear();
        currentLine.push_back(sf::Vertex(gridMatrix[i][0]));
        currentLine.push_back(sf::Vertex(gridMatrix[i][gridMatrix[i].size()-1]));
        linesVector.push_back(currentLine);
    }

    // Calculating position of square in the middle of the grid
    // Coordinates of the norhwesternmost point in the square will be returned
    middlePos = gridMatrix[(gridMatrix.size()/2)-1][(gridMatrix[0].size()/2)-1];
    // if the matrix has an even number of rows & columns, the square NW of the 4 ones in the middle will be returned
}

sf::Vector2f gameMatrix::getAdjacentPos(directions dir, sf::Vector2f currentPos){
    sf::Vector2f goalVector;
    int long unsigned i=0, j=0, columnIndex=0, rowIndex=0;
    bool found = false;
    for (i=0; i<gridMatrix.size(); i++){
        for (j=0; j<gridMatrix[i].size(); j++){
            if (gridMatrix[i][j] == currentPos){
                rowIndex = i;
                columnIndex = j;
                found = true;
            }
        }
    }
    cout << "Current index is: \nrow: " << rowIndex << "\ncolumn: " << columnIndex << endl << endl;

    if (found){
        if (dir == north){
            goalVector = gridMatrix[rowIndex-1][columnIndex];
            cout << "New row: " << (rowIndex-1) << endl;
            cout << goalVector.x << "  " << goalVector.y << endl;
        }
        if (dir == south){
            goalVector = gridMatrix[rowIndex+1][columnIndex];
            cout << "New row: " << (rowIndex+1) << endl;
            cout << goalVector.x << "  " << goalVector.y << endl;
        }
        if (dir == east){
            goalVector = gridMatrix[rowIndex][columnIndex+1];
            cout << "New column: " << (columnIndex+1) << endl;
            cout << goalVector.x << "  " << goalVector.y << endl;
        }
        if (dir == west){
            goalVector == gridMatrix[rowIndex][columnIndex-1];
            cout << "New column: " << (columnIndex-1) << endl;
            cout << goalVector.x << "  " << goalVector.y << endl;
        }
    }else{
        cout << "Matrix position: " << currentPos.x << " x " << currentPos.y << " not found" << endl;
    }
    return goalVector;
}


int main(){
    unsigned int i=0;
    sf::RenderWindow window(sf::VideoMode(600, 600), "Snake game in c++");
    // head snakeHead(sf::Vector2f());
    cout << "Window size is: " << window.getSize().x << " x " << window.getSize().y << endl;

    gameMatrix matx(window, 20);
    vector<vector<sf::Vertex>> linesVector = matx.getLinesVector();
    sf::Vertex lineToDraw[2];

    snakeHead head(matx.getDivWidth(), sf::Color(100, 100, 255));
    head.setHeadPosition(matx.getMiddlePos(), matx.getDivWidth().x);
    vector<sf::RectangleShape*> headDrawables = head.getDrawables();

    sf::Vector2f nextHeadPos;

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))){
                window.close();
            }

            if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    nextHeadPos = matx.getAdjacentPos(north, head.getHead().getPosition());
                    head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);                    
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    nextHeadPos = matx.getAdjacentPos(south, head.getHead().getPosition());
                    head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    nextHeadPos = matx.getAdjacentPos(east, head.getHead().getPosition());
                    head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    nextHeadPos = matx.getAdjacentPos(west, head.getHead().getPosition());
                    head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);
                }
            }

        }

        window.clear();

        for (i=0; i<headDrawables.size(); i++){
            window.draw(*(headDrawables[i]));
        }
        
        for (i=0; i<linesVector.size(); i++){
            lineToDraw[0] = linesVector[i][0];
            lineToDraw[1] = linesVector[i][1];
            window.draw(lineToDraw, 2, sf::Lines);
        }
        window.display();
    }

    return 0;
}


#endif