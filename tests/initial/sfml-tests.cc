#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

// Key presses can be detected with window.pollEvent(event - created before) and then event.type == sf::Event::KeyPressed
// It is better to use sf::Keyboard::isKeyPressed(sf::Keyboard::<KeyName>)

int main(){
    
    sf::RenderWindow window(sf::VideoMode(200, 200, 64), "SFML works!");
    sf::CircleShape shape(100);
    shape.setFillColor(sf::Color(255, 255, 0));

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){window.close();}
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Event::KeyPressed:
                cout << "A key was pressed" << endl;
                if (event.key.code == sf::Keyboard::Escape){window.close();}
                break;
            
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}