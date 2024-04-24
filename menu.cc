#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

#define TEST_TEXTURE_PATH "./assets/ps-sprite.png"
#define PIXEL_FONT_PATH "./fonts/pixel-font.ttf"

#define NORMAL_TEXT_COLOR sf::Color(255, 255, 255)
#define SELECTED_TEXT_COLOR sf::Color(95, 195, 245)

#define MAX_MENU 3

void startMenu(){
    cout << "Starting menu" << endl;
    system("./tests/2d-render");
}

void startCinematic(){
    cout << "Starting cinematic" << endl;
}

void animateTextForward(sf::Text &textToMove, sf::Vector2f initialTextPos, float maxCount, float &countVar, bool &containerMoving, bool &posReached){
    if (!containerMoving){
        countVar = 0;
        if (!posReached){
            containerMoving = true;
        }else{
            containerMoving = false;
            posReached = true;
        }
    }else{
        if (textToMove.getPosition().x >= (initialTextPos.x+maxCount)){  // desired pos was reached
            // cout << "Desired pos was reached" << endl;
            textToMove.setPosition(initialTextPos.x+maxCount, initialTextPos.y);
            containerMoving = false;
            posReached = true;
        }else{
            // cout << testText.getPosition().x << " = " << (initialTextPos.x+maxCount) << endl;
            // cout << "Moving text..." << endl;
            textToMove.setPosition(textToMove.getPosition().x+countVar, textToMove.getPosition().y);
            containerMoving = true;
            countVar++;
        }
    }
    textToMove.setFillColor(SELECTED_TEXT_COLOR);
}


void animateTextBackward(sf::Text &textToMove, sf::Vector2f initialTextPos, float maxCount, float &countVar, bool &containerMoving, bool &posReached){
    if (!containerMoving){
        countVar = 0;
        if (posReached){
            containerMoving = true;
        }
    }else{
        if (textToMove.getPosition().x <= initialTextPos.x){  // desired pos was reached
            // cout << "Desired pos was reached" << endl;
            textToMove.setPosition(initialTextPos);
            containerMoving = false;
            posReached = false;
        }else{
            // cout << "Moving text..." << endl;
            textToMove.setPosition(textToMove.getPosition().x-countVar, textToMove.getPosition().y);
            containerMoving = true;
            countVar++;
        }
    }
    textToMove.setFillColor(NORMAL_TEXT_COLOR);
}


int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Main menu");
    window.setKeyRepeatEnabled(false);

    float moveDistance = 20, count=0, count2=0, count3=0;
    bool textMoving=false, textPosReached=false, textMoving2=false, textPosReached2=false, textMoving3=false, textPosReached3=false;

    sf::Vector2i mousePosition;

    sf::Font pixelFont;
    if (!pixelFont.loadFromFile(PIXEL_FONT_PATH)){
        cout << "Error while loading font" << endl;
    }

    sf::Text stGameText, viewCinText, exitText, titleText;
    vector<sf::Text *> menuTextsVector{&stGameText, &viewCinText, &exitText};
    // Vector of sf::Text pointers needed because we need to modify their properties

    int long unsigned i=0;
    for (i=0; i<menuTextsVector.size(); i++){
        (*menuTextsVector[i]).setFont(pixelFont);
        (*menuTextsVector[i]).setCharacterSize(60);    // Size in pixels
        (*menuTextsVector[i]).setFillColor(NORMAL_TEXT_COLOR);
        (*menuTextsVector[i]).setPosition(sf::Vector2f(40, 500+i*150));
        // (*menuTextsVector[i]).setStyle(sf::Text::Bold);
    }

    stGameText.setString("START GAME");
    viewCinText.setString("VIEW CINEMATIC");
    exitText.setString("EXIT GAME");

    sf::FloatRect bBoxSt = stGameText.getGlobalBounds(), bBoxView = viewCinText.getGlobalBounds(), bBoxExit = exitText.getGlobalBounds();
    sf::Vector2f iPosStGameText = stGameText.getPosition(), iPosViewCinText = viewCinText.getPosition(), iPosExitText = exitText.getPosition();
    // A better option would be to make a container for each text and use that as a boundary box

    titleText.setFont(pixelFont);
    titleText.setCharacterSize(100);
    titleText.setFillColor(NORMAL_TEXT_COLOR);
    titleText.setPosition(sf::VideoMode::getDesktopMode().width/6, 30);
    titleText.setString("GAME TITLE");
    titleText.setStyle(sf::Text::Underlined);

    while (window.isOpen()){
        sf::Event event;
        mousePosition = sf::Mouse::getPosition(window);     // Gets pos relative to window so that it can be resized

        // Keyboard events management
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            // Mouse events management
            if (bBoxSt.contains(mousePosition.x, mousePosition.y)){
                animateTextForward(stGameText, iPosStGameText, moveDistance, count, textMoving, textPosReached);
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    startMenu();
                }
            }else{
                animateTextBackward(stGameText, iPosStGameText, moveDistance, count, textMoving, textPosReached);
            }
            if (bBoxView.contains(mousePosition.x, mousePosition.y)){
                animateTextForward(viewCinText, iPosViewCinText, moveDistance, count2, textMoving2, textPosReached2);
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    startCinematic();
                }
            }else{
                animateTextBackward(viewCinText, iPosViewCinText, moveDistance, count2, textMoving2, textPosReached2);
            }
            if (bBoxExit.contains(mousePosition.x, mousePosition.y)){
                animateTextForward(exitText, iPosExitText, moveDistance, count3, textMoving3, textPosReached3);
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    window.close();
                }
            }else{
                animateTextBackward(exitText, iPosExitText, moveDistance, count3, textMoving3, textPosReached3);
            }
        
        } // scope of pollEvent while loop ends here

        // Clearing and drawing the elements in the window
        window.clear(sf::Color(100, 100, 255));

        for (i=0; i<menuTextsVector.size(); i++){
            window.draw(*menuTextsVector[i]);
        }
        window.draw(titleText);

        window.display();
    }

    return 0;
}