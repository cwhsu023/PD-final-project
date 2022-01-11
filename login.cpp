#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include "game.cpp"

bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) 
{
    if (sprite.contains(mp))
    {
        return true;
    }
    return false;
}

class Login
{
public:
    sf::RenderWindow window;
    sf::Texture t1, t2;
    sf::Sprite s1, s2;
    sf::Vector2f mp;
    Login();
    bool Open() {return window.isOpen();}
    void refresh();
    void openWindow(); 
};
Login::Login()
{
    // this->playGame = false;
    this->window.create(sf::VideoMode(3000, 1200),"Game!!!");
    openWindow();
}
void Login::openWindow()
{
    mp.x = sf::Mouse::getPosition(this->window).x;
    mp.y = sf::Mouse::getPosition(this->window).y;
    t1.loadFromFile("resources/button1.png");
    s1.setTexture(t1);
    s1.setPosition(sf::Vector2f(500, 500));
    t2.loadFromFile("resources/champion_board.png");
    s2.setTexture(t2);
    s2.setPosition(sf::Vector2f(2000,500));
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();  
            if(isSpriteHover(s1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                    {
                        window.close();
                        Game game;
                        if(!game.window.isOpen())
                            Login login;
                    }
                }
            if(isSpriteHover(s2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                    {
                        // 排行榜的資訊
                        continue;
                    }
                }
        }
        refresh();
    }
}
void Login::refresh()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(s1);
    this->window.draw(s2);
    this->window.display();
}