#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

#define TEST_TEXTURE_PATH "./assets/ps-sprite.png"
#define PIXEL_FONT_PATH "./fonts/pixel-font.ttf"

void animateTextForward(sf::Text &testText, sf::Vector2f initialTextPos, float maxCount, float &countVar, bool &containerMoving, bool &posReached){
    if (!containerMoving){
        countVar = 0;
        if (!posReached){
            containerMoving = true;
        }else{
            containerMoving = false;
            posReached = true;
        }
    }else{
        if (testText.getPosition().x >= (initialTextPos.x+maxCount)){  // desired pos was reached
            cout << "Desired pos was reached" << endl;
            testText.setPosition(initialTextPos.x+maxCount, initialTextPos.y);
            containerMoving = false;
            posReached = true;
        }else{
            cout << testText.getPosition().x << " = " << (initialTextPos.x+maxCount) << endl;
            //cout << "Moving text..." << endl;
            testText.setPosition(testText.getPosition().x+countVar, testText.getPosition().y);
            containerMoving = true;
            countVar++;
        }
    }
}


void animateTextBackward(sf::Text &testText, sf::Vector2f initialTextPos, float maxCount, float &countVar, bool &containerMoving, bool &posReached){
    if (!containerMoving){
        countVar = 0;
        if (posReached){
            containerMoving = true;
        }
    }else{
        if (testText.getPosition().x <= initialTextPos.x){  // desired pos was reached
            cout << "Desired pos was reached" << endl;
            testText.setPosition(initialTextPos);
            containerMoving = false;
            posReached = false;
        }else{
            cout << "Moving text..." << endl;
            testText.setPosition(testText.getPosition().x-countVar, testText.getPosition().y);
            containerMoving = true;
            countVar++;
        }
    }
}


int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Text animation tests");
    float moveCount=0, maxCount=20;
    bool containerMoving=false, posReached=false;
    sf::Vector2i mousePos;
    sf::Vector2f initialTextPos(200, 200);

    sf::Font pxFont;
    if (!pxFont.loadFromFile(PIXEL_FONT_PATH)){
        cout << "Error while loading font" << endl;
    }

    sf::Text testText;
    testText.setFont(pxFont);
    testText.setCharacterSize(60);
    testText.setString("Start Game");
    testText.setPosition(initialTextPos);

    sf::FloatRect testBbox = testText.getGlobalBounds();

    while (window.isOpen()){
        sf::Event event;
        mousePos = sf::Mouse::getPosition(window);      // 'window' in brackets is important idk why
        // testBbox = testText.getGlobalBounds();

        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }


            // Forwards (east) movement
            if (testBbox.contains(mousePos.x, mousePos.y)){
                animateTextForward(testText, initialTextPos, maxCount, moveCount, containerMoving, posReached);

            }else{      // mouse is outside text boundaries. this one works the other way around
                // Backwards (west) movement
                animateTextBackward(testText, initialTextPos, maxCount, moveCount, containerMoving, posReached);
            }

        
        }


        window.clear(sf::Color(100, 100, 255));
        window.draw(testText);
        window.display();
    }


    return 0;
}