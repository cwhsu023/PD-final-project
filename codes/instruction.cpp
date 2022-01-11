#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/System.hpp>
#include <iostream>
#include <string>

// bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) 
// {
//     if (sprite.contains(mp))
//     {
//         return true;
//     }
//     return false;
// }

class Instruct
{
public:
    sf::RenderWindow window;
    // sf::Texture t1, t2;
    // sf::Sprite s1, s2;
    sf::Vector2f mp;
    Instruct();
    void refresh();
    void openWindow(); 
};
Instruct::Instruct()
{
    this->window.create(sf::VideoMode(1000, 600),"How to play?");
    openWindow();
}
void Instruct::openWindow()
{
    mp.x = sf::Mouse::getPosition(this->window).x;
    mp.y = sf::Mouse::getPosition(this->window).y;
    // t1.loadFromFile("resources/button1.png");
    // s1.setTexture(t1);
    // s1.setPosition(sf::Vector2f(500, 500));
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();  
            // if(isSpriteHover(s1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            //     {
            //         if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            //         {
            //             // window.close();
            //             // Game game;
            //             // if(!game.window.isOpen())
            //             //     Login login;
            //         }
            //     }
        }
        refresh();
    }
}
void Instruct::refresh()
{
    this->window.clear(sf::Color::Black);
    // this->window.draw(s1);
    this->window.display();
}