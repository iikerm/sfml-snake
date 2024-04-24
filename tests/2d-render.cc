#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#define TEST_TEXTURE_PATH "./assets/ps-sprite.png"
// Texture can be seen as image from which sprites are taken out
// It is more efficient to load all sprites from the same texture (i.e. texture contains 
// areas for each sprite and sprites are loaded in their respective positions by using sf::IntRect(x1, y1, x2, y2))

int main()
{
    float moveDistance = 50;
    // create the window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "My window");      // sf::Style::Fullscreen can be added at the end for F11 fullscreen

    // loads the image as a texture
    sf::Texture psTexture;
    if (!psTexture.loadFromFile(TEST_TEXTURE_PATH)){
        cout << "Error happened" << endl;
    }

    sf::Sprite psSprite;
    psSprite.setTexture(psTexture);
    psSprite.setPosition(sf::Vector2f(120.f, 50.f));
    psSprite.scale(sf::Vector2f(5, 5));      // ps is supposed to be a square


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            
            if (event.type == sf::Event::KeyPressed){   // inside this if so that the event only happens once per key press
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    psSprite.move(sf::Vector2f(0.f, -moveDistance));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    psSprite.move(sf::Vector2f(0.f, moveDistance));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    psSprite.move(sf::Vector2f(moveDistance, 0.f));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    psSprite.move(sf::Vector2f(-moveDistance, 0.f));
                }
            }
        }

        


        // clear the window with black color
        // window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(psSprite);

        // end the current frame
        window.display();
    }

    return 0;
}