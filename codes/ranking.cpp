#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <windows.h>
// #include "player.h"

// bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) 
// {
//     if (sprite.contains(mp))
//     {
//         return true;
//     }
//     return false;
// }

class Ranking
{
public:
    sf::RenderWindow window;
    sf::Texture tbg ,t1, t2, t3, t4, t5;
    sf::Sprite sbg ,s1 ,s2, s3, s4, s5;
    sf::Vector2f mp;

    Ranking();
    void refresh();
    void openWindow();
};
Ranking::Ranking()
{
    this->window.create(sf::VideoMode(863, 620),"Ranking");
    openWindow();
}
void Ranking::openWindow()
{
    tbg.loadFromFile("resources/rkbg.png");
	sbg.setTexture(tbg);
    sbg.setScale(sf::Vector2f(1.0f, 1.0f));
    
    t1.loadFromFile("resources/wood.png");
    s1.setTexture(t1);
    s1.setScale(sf::Vector2f(1.5f, 1.0f));
    s1.setPosition(sf::Vector2f(137, 20));
    
	t2.loadFromFile("resources/wood.png");
    s2.setTexture(t2);
    s2.setScale(sf::Vector2f(1.5f, 1.0f));
    s2.setPosition(sf::Vector2f(137, 130));
    
    
	t3.loadFromFile("resources/wood.png");
    s3.setTexture(t3);
    s3.setScale(sf::Vector2f(1.5f, 1.0f));
    s3.setPosition(sf::Vector2f(137, 240));
    
	t4.loadFromFile("resources/wood.png");
    s4.setTexture(t4);
    s4.setScale(sf::Vector2f(1.5f, 1.0f));
    s4.setPosition(sf::Vector2f(137, 350));
    
	t5.loadFromFile("resources/wood.png");
	s5.setTexture(t5);
    s5.setScale(sf::Vector2f(1.5f, 1.0f));
    s5.setPosition(sf::Vector2f(137, 460));
    

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();  
        }
        window.clear();
        refresh();
    }
}
void Ranking::refresh()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(sbg);
    this->window.draw(s1);
    this->window.draw(s2);
    this->window.draw(s3);
    this->window.draw(s4);
    this->window.draw(s5);
    this->window.display();
}
