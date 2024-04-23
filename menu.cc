#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

#define TEST_TEXTURE_PATH "./assets/ps-sprite.png"
#define PIXEL_FONT_PATH "./fonts/pixel-font.ttf"

#define NORMAL_TEXT_COLOR sf::Color(255, 255, 255)
#define SELECTED_TEXT_COLOR sf::Color(95, 195, 245)

#define MAX_MENU 3


int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Main menu");
    window.setKeyRepeatEnabled(false);

    sf::Font pixelFont;
    if (!pixelFont.loadFromFile(PIXEL_FONT_PATH)){
        cout << "Error while loading font" << endl;
    }

    sf::Text stGameText, viewCinText, exitText;
    vector<sf::Text *> menuTextsVector{&stGameText, &viewCinText, &exitText};
    // Vector of sf::Text pointers needed because we need to modify their properties

    int long unsigned i=0;
    for (i=0; i<menuTextsVector.size(); i++){
        (*menuTextsVector[i]).setFont(pixelFont);
        (*menuTextsVector[i]).setCharacterSize(75);    // Size in pixels
        (*menuTextsVector[i]).setFillColor(NORMAL_TEXT_COLOR);
        (*menuTextsVector[i]).setPosition(sf::Vector2f(10, 500+i*150));
        // (*menuTextsVector[i]).setStyle(sf::Text::Bold);
    }

    stGameText.setString("START GAME");
    viewCinText.setString("VIEW CINEMATIC");
    exitText.setString("EXIT GAME");

    while (window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear(sf::Color::Green);

        for (i=0; i<menuTextsVector.size(); i++){
            window.draw(*menuTextsVector[i]);
        }

        window.display();
    }

    return 0;
}