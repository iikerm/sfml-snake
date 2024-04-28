#ifndef _SFML_GRAPHICS_HPP_
#define _SFML_GRAPHICS_HPP_


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>      // used for rand() in appleBlock
using namespace std;

const sf::Color BG_COLOR = sf::Color(0, 0, 0);
const sf::Color SNAKE_COLOR = sf::Color(100, 100, 255);

enum directions {north, south, west, east};

directions oppositeDir(directions currentDir){
    switch (currentDir){
        case north:
            return south;
            break;
        case south:
            return north;
            break;
        case west:
            return east;
            break;
        default:
            return west;
            break;
    }
}


class appleBlock{
    sf::Color appleColor = sf::Color(250, 50, 50);      // default color for apples declared using first constructor
    private:
        sf::RectangleShape apple;
        sf::Vector2f position;
    public:
        appleBlock(sf::Vector2f rectSize);
        appleBlock(sf::Vector2f rectSize, sf::Color customAppleColor);    // overload to include custom color
        void setApplePosition(sf::Vector2f newPos){position = newPos; apple.setPosition(position);}
        void setAppleRandPosition(vector<vector<sf::Vector2f>> gridMatrix);
        sf::RectangleShape getAppleRect(){return apple;}
        sf::FloatRect getAppleBounds(){return sf::FloatRect(apple.getGlobalBounds());}
        sf::Vector2f getApplePosition(){return position;}
};

appleBlock::appleBlock(sf::Vector2f rectSize){      // normal constructor with default color
    apple = sf::RectangleShape(rectSize);
    apple.setFillColor(appleColor);
}

appleBlock::appleBlock(sf::Vector2f rectSize, sf::Color customAppleColor){    // overload to include custom color
    apple = sf::RectangleShape(rectSize);
    apple.setFillColor(customAppleColor);
}

void appleBlock::setAppleRandPosition(vector<vector<sf::Vector2f>> gridMatrix){
    // we need the grid matrix in order to establish what the maximum x and y values can be
    int unsigned maxRowIndex=0, maxColIndex=0, rowIndex=0, colIndex=0;
    sf::Vector2f randPosition;

    maxColIndex = gridMatrix.size();    // Maximum index possible for a column (Y value) inside the grid matrix
    maxRowIndex = gridMatrix[0].size();    // Maximum index possible for a row (X value) inside the grid matrix
    // It doesn't matter which index is taken to calculate maxRowIndex because all the rows in the matrix should be the same size
    
    srand(time(0));     // Set random (based on current time) seed for random number
    
    do{
        colIndex = (rand()%maxColIndex);
        rowIndex = (rand()%maxRowIndex);
        randPosition = sf::Vector2f(gridMatrix[rowIndex][colIndex]);        // matrix should be square so order of row/column should not matter in theory
    }while(randPosition == position);       // so that position cannot be the same two consecutive times
    
    position = randPosition;
    apple.setPosition(position);
}



class snakeHead{
    sf::Color snakeColor = SNAKE_COLOR;
    sf::Color eyeColor = sf::Color(25, 25, 25);
    private:
        sf::RectangleShape headRect;
        sf::RectangleShape eyeRectW;
        sf::RectangleShape eyeRectE;
        sf::Vector2f position;
        sf::Color headColor;
    public:
        snakeHead(sf::Vector2f rectSize);
        void setHeadPosition(sf::Vector2f pos, float divWidth);
        sf::RectangleShape getHead(){return headRect;}
        sf::Vector2f getHeadSize(){return headRect.getSize();}

        // pointer array is important, because if not we will be trying to draw copies of current drawables on screen instead of the actual ones we want to draw
        vector<sf::RectangleShape*> getDrawables(){return vector<sf::RectangleShape*>{&headRect, &eyeRectW, &eyeRectE};}
};

snakeHead::snakeHead(sf::Vector2f rectSize){
    headRect = sf::RectangleShape(rectSize);
    headColor = snakeColor;
    headRect.setFillColor(headColor);

    // Eyes are named as if the snake is looking upwards with eyeRectW being west and eyeRectE being east
    eyeRectW = sf::RectangleShape(sf::Vector2f(rectSize.x*0.1, rectSize.y*0.2));
    eyeRectW.setFillColor(eyeColor);
    eyeRectE = sf::RectangleShape(sf::Vector2f(rectSize.x*0.1, rectSize.y*0.2));
    eyeRectE.setFillColor(eyeColor);
}

void snakeHead::setHeadPosition(sf::Vector2f pos, float divWidth){
    // divWidth is only needed to move the snake's eyes
    position = pos;
    headRect.setPosition(pos);

    //cout << "head position: " << pos.x << " and " << pos.y << endl;
    //cout << "left eye position: " << pos.x+(divWidth*0.3) << " and " << pos.y+(divWidth*0.25) << endl;
    //cout << "right eye position: " << pos.x+(divWidth*0.6) << " and " << pos.y+(divWidth*0.25) << endl << endl;

    eyeRectW.setPosition(sf::Vector2f(pos.x+(divWidth*0.3), pos.y+(divWidth*0.4)));
    eyeRectE.setPosition(sf::Vector2f(pos.x+(divWidth*0.6), pos.y+(divWidth*0.4)));
}


// Unused func
void animateRect(snakeHead &headToMove, sf::Vector2f initialPos, float distToMove, float countVar, bool &containerMoving, bool &posReached){
    if (!containerMoving){
        if (!posReached){
            containerMoving = true;
        }else{
            containerMoving = false;
            posReached = true;
        }
    }else{
        if (headToMove.getHead().getPosition().x >= (initialPos.x+distToMove)){  // desired pos was reached
            // cout << "Desired pos was reached" << endl;
            headToMove.setHeadPosition(sf::Vector2f(initialPos.x+distToMove, initialPos.y), headToMove.getHeadSize().x);
            containerMoving = false;
            posReached = true;
        }else{
            // cout << rectToMove.getPosition().x << " = " << (initialPos.x+distToMove) << endl;
            // cout << "Moving element..." << endl;
            headToMove.setHeadPosition(sf::Vector2f(headToMove.getHead().getPosition().x+countVar, headToMove.getHead().getPosition().y), headToMove.getHeadSize().x);
            containerMoving = true;
        }
    }
}


class gameMatrix{
    sf::Color lineColor = BG_COLOR;
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

    // Arguments validation
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
    divWidth = ((float)(masterWindow->getSize().x)) / ((float)(numDivs));       // numDivs -1

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
        currentLine.push_back(sf::Vertex(gridMatrix[0][i], sf::Color(0, 0, 0)));
        currentLine.push_back(sf::Vertex(sf::Vector2f(gridMatrix[(gridMatrix.size()-1)][i].x+divWidth, gridMatrix[(gridMatrix.size()-1)][i].y), lineColor));
        linesVector.push_back(currentLine);
    }
    // Horizontal lines
    for (i=0; i<gridMatrix.size(); i++){
        currentLine.clear();
        currentLine.push_back(sf::Vertex(gridMatrix[i][0], sf::Color(0, 0, 0)));
        currentLine.push_back(sf::Vertex(sf::Vector2f(gridMatrix[i][gridMatrix[i].size()-1].x, gridMatrix[i][gridMatrix[i].size()-1].y+divWidth), lineColor));
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
    
    if (found){
        if (dir == north){
            columnIndex -= 1;
        }
        if (dir == south){
            columnIndex += 1;
        }
        if (dir == east){
            rowIndex += 1;
        }
        if (dir == west){
            rowIndex -= 1;
        }        

        if (rowIndex == -1){
            rowIndex = (gridMatrix.size()-1);
        }
        if (rowIndex > gridMatrix.size()-1){
            rowIndex = 0;
        }
        if (columnIndex == -1){
            columnIndex = (gridMatrix[0].size()-1);
        }
        if (columnIndex > gridMatrix[0].size()-1){
            columnIndex = 0;
        }
        

        goalVector = gridMatrix[rowIndex][columnIndex];
        // cout << "Current pos is: " << goalVector.x << " x " << goalVector.y << endl;
        // cout << "Current index is: \nrow: " << rowIndex << "\ncolumn: " << columnIndex << endl << endl;

    }/*else{
        cout << "Matrix position: " << currentPos.x << " x " << currentPos.y << " not found" << endl;
        throw invalid_argument("Matrix position not found");
    }*/
    return goalVector;
}


int main(){
    unsigned int i=0, score=0;
    sf::RenderWindow window(sf::VideoMode(600, 600), "Snake game in c++");
    cout << "Window size is: " << window.getSize().x << " x " << window.getSize().y << endl;

    gameMatrix matx(window, 15);
    vector<vector<sf::Vertex>> linesVector = matx.getLinesVector();
    sf::Vertex lineToDraw[2];

    snakeHead head(matx.getDivWidth());
    head.setHeadPosition(matx.getMiddlePos(), matx.getDivWidth().x);
    vector<sf::RectangleShape*> headDrawables = head.getDrawables();

    sf::Vector2f nextHeadPos;
    appleBlock theApple(matx.getDivWidth());
    theApple.setAppleRandPosition(matx.getGridMatrix());

    directions currentDir=east;
    unsigned int count=0, lastMoved=0, controlDelay=0, itersUpdate=2000;
    // count%itersUpdate gives the max "fps" i.e. the snake's speed
    // tested values for itersUpdate: 4000 ~ slow speed;  2500 ~ medium speed;  1000 ~ fast speed;

    /*animation vars
    bool headMoving=false, headPosReached=false;
    sf::Vector2f headInitialPos;*/

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))){
                window.close();
            }

            if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    // nextHeadPos = matx.getAdjacentPos(north, head.getHead().getPosition());
                    // head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);
                    if (currentDir != oppositeDir(north)){
                        currentDir = north;
                    }
                    lastMoved = count;
                }else{
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                        // nextHeadPos = matx.getAdjacentPos(south, head.getHead().getPosition());
                        // head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);
                        if (currentDir != oppositeDir(south)){
                            currentDir = south;
                        }
                        lastMoved = count;
                    }else{
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                            // nextHeadPos = matx.getAdjacentPos(east, head.getHead().getPosition());
                            // head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);
                            if (currentDir != oppositeDir(east)){
                                currentDir = east;
                            }
                            lastMoved = count;
                        }else{
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                                // nextHeadPos = matx.getAdjacentPos(west, head.getHead().getPosition());
                                // head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);
                                if (currentDir != oppositeDir(west)){
                                    currentDir = west;
                                }
                                lastMoved = count;
                            }
                        }
                    }
                }
            }
        }
        
        nextHeadPos = matx.getAdjacentPos(currentDir, head.getHead().getPosition());
        

        if (count%itersUpdate == 0){

            // detecting collisions
            if (theApple.getAppleBounds().intersects(head.getHead().getGlobalBounds())){
                theApple.setAppleRandPosition(matx.getGridMatrix());
                score++;
                cout << "New score is: " << score << endl;
            }
            
            head.setHeadPosition(nextHeadPos, matx.getDivWidth().x);         // works but animation is weird

            window.clear(BG_COLOR);

            window.draw(theApple.getAppleRect());

            for (i=0; i<headDrawables.size(); i++){
                window.draw(*(headDrawables[i]));
            }
            
            for (i=0; i<linesVector.size(); i++){
                lineToDraw[0] = linesVector[i][0];
                lineToDraw[1] = linesVector[i][1];
                window.draw(lineToDraw, 2, sf::Lines);
            }

        }

        if (count == UINT32_MAX){
            count = 0;
        }
        count++;

        window.display();
    }

    return 0;
}


#endif