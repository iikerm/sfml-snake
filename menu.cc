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

void lightupMenuText(sf::Text &menuText){
    menuText.setFillColor(SELECTED_TEXT_COLOR);
    // Better to use .setPosition because if not text will move infinitely
    menuText.setPosition(sf::Vector2f(60 ,menuText.getPosition().y));
}

void revertLightupMenuText(sf::Text &menuText){
    menuText.setFillColor(NORMAL_TEXT_COLOR);
    // Cant use .move here, must use .setPosition because this function is always called unless lightupMenuText is called so text will move infinitely
    menuText.setPosition(sf::Vector2f(40 ,menuText.getPosition().y));
}


int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Main menu");
    window.setKeyRepeatEnabled(false);

    int moveDistance = 20, count=0;

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

            // Commands for when main menu text interacts with mouse
            if (bBoxSt.contains(mousePosition.x, mousePosition.y)){
                lightupMenuText(stGameText);
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    startMenu();
                }
            }else{
                revertLightupMenuText(stGameText);
            }
            if (bBoxView.contains(mousePosition.x, mousePosition.y)){
                lightupMenuText(viewCinText);
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    startCinematic();
                }
            }else{
                revertLightupMenuText(viewCinText);
            }
            if (bBoxExit.contains(mousePosition.x, mousePosition.y)){
                lightupMenuText(exitText);
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    window.close();
                }
            }else{
                revertLightupMenuText(exitText);
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