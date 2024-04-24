#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

#define TEST_TEXTURE_PATH "./assets/ps-sprite.png"

int main(){
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Animation tests");
    int count = 1, maxCount=4400, moveRate=1;
    float countPercent;
    cout << countPercent << endl;
    sf::Texture psTexture;
    if (!psTexture.loadFromFile(TEST_TEXTURE_PATH)){
        cout << "Error while loading texture" << endl;
    }

    sf::Sprite psSprite(psTexture);
    psSprite.setPosition(sf::Vector2f(2200, 800));
    psSprite.setOrigin(250, 250);
    psSprite.rotate(90);



    while (window.isOpen()){
        countPercent = (float)count / (float)maxCount;
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        }

        if (count <= (maxCount/2)){
            psSprite.setPosition(sf::Vector2f(psSprite.getPosition().x-moveRate, 0));
            psSprite.setScale(sf::Vector2f(1+countPercent, 1+countPercent));
            // psSprite.rotate(360*countPercent);
        }else{
            psSprite.setPosition(sf::Vector2f(psSprite.getPosition().x+moveRate, 0));
            psSprite.setScale(sf::Vector2f(2-countPercent, 2-countPercent));
            // psSprite.rotate(-360*countPercent);
        }


        if (count >= maxCount){
            count = 1;
        }else{
            count++;
        }
        cout << (countPercent) << endl;
        //cout << count << "/" << maxCount << endl;

        window.clear(sf::Color(0+(countPercent*100), 100-(countPercent*100), (countPercent)*255));
        window.draw(psSprite);
        window.display();
    }


    return 0;
}