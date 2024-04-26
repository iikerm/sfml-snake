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
        float squareDivisionWidth;
    public:
        snakeHead(sf::Vector2f rectSize, sf::Color color);
        void setHeadPosition(sf::Vector2f pos, float divWidth);
        sf::RectangleShape getHead(){return headRect;}
        vector<sf::RectangleShape> getDrawables(){return vector<sf::RectangleShape>{headRect, eyeRectW, eyeRectE};}
        void moveHead(sf::Vector2f sumToPos);
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
    position = pos;
    headRect.setPosition(pos);

    squareDivisionWidth = divWidth;

    // cout << pos.x << " and " << pos.y << endl;

    eyeRectW.setPosition(sf::Vector2f(pos.x+(divWidth*0.3), pos.y+(divWidth*0.25)));
    eyeRectE.setPosition(sf::Vector2f(pos.x+(divWidth*0.6), pos.y+(divWidth*0.25)));
}

void snakeHead::moveHead(sf::Vector2f sumToPos){
    sf::Vector2f headPos = headRect.getPosition(),
                 eyeWPos = eyeRectW.getPosition(),
                 eyeEPos = eyeRectE.getPosition();
    headRect.setPosition(headPos.x+sumToPos.x, headPos.y+sumToPos.y);
    eyeRectW.setPosition(eyeWPos.x+sumToPos.x, eyeWPos.y+sumToPos.y);
    eyeRectE.setPosition(eyeEPos.x+sumToPos.x, eyeEPos.y+sumToPos.y);
}



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
        sf::Vector2f getAdjacentPos(directions direct, sf::Vector2f currPos);
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

sf::Vector2f gameMatrix::getAdjacentPos(directions direct, sf::Vector2f currPos){
    float addToPosX=0, addToPosY=0;
    sf::Vector2f returnVector;

    if (direct == north){
        addToPosY = -divWidth;
        if ((currPos.y + addToPosY) < 0){     // if it goes up past the limit, it appears at the bottom
            addToPosY = gridMatrix[gridMatrix.size()-1][0].y - currPos.y;
        }
    }
    if (direct == south){
        addToPosY = divWidth;
        if ((currPos.y + addToPosY) > gridMatrix[gridMatrix.size()-1][0].y){
            addToPosY = -(currPos.y);
        }
    }
    if (direct == west){
        addToPosX = -divWidth;
        if ((currPos.x + addToPosX) < 0){
            addToPosX = gridMatrix[0][gridMatrix[0].size()-1].x - currPos.x;
        }
    }
    if (direct == east){
        addToPosX = divWidth;
        if ((currPos.x + addToPosX) > gridMatrix[0][gridMatrix[0].size()-1].x){
            addToPosX = -(currPos.x);
        }
        cout << "Moving east" << endl;
    }
    returnVector.y = addToPosY;
    returnVector.x = addToPosX;
    return returnVector;
}

int main(){
    unsigned int i=0;
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "Snake game in c++");
    // head snakeHead(sf::Vector2f());
    cout << "Window size is: " << window.getSize().x << " x " << window.getSize().y << endl;

    gameMatrix matx(window, 20);
    vector<vector<sf::Vertex>> linesVector = matx.getLinesVector();
    sf::Vertex lineToDraw[2];

    snakeHead head(matx.getDivWidth(), sf::Color(100, 100, 255));
    head.setHeadPosition(matx.getMiddlePos(), matx.getDivWidth().x);
    vector<sf::RectangleShape> headDrawables = head.getDrawables();

    sf::Vector2f newHeadPos;

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))){
                window.close();
            }else{
                if (event.type == sf::Event::KeyPressed){
                    cout << "Key pressed" << endl;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                        newHeadPos = matx.getAdjacentPos(north, head.getHead().getPosition());
                        head.moveHead(newHeadPos);
                        cout << "Up" << endl;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                        newHeadPos = matx.getAdjacentPos(south, head.getHead().getPosition());
                        head.moveHead(newHeadPos);
                        cout << "Down" << endl;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                        newHeadPos = matx.getAdjacentPos(west, head.getHead().getPosition());
                        head.moveHead(newHeadPos);
                        cout << "Left" << endl;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                        newHeadPos = matx.getAdjacentPos(east, head.getHead().getPosition());
                        cout << head.getHead().getPosition().x << " x " << head.getHead().getPosition().y << endl;
                        head.setHeadPosition(sf::Vector2f(head.getHead().getPosition().x+matx.getDivWidth().x, head.getHead().getPosition().y), matx.getDivWidth().x);
                        cout << newHeadPos.x << " x " << newHeadPos.y << endl;
                        cout << "Right" << endl;
                    }
                }
            }
        }

        window.clear();

        for (i=0; i<headDrawables.size(); i++){
            window.draw(headDrawables[i]);
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