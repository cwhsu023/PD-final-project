#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include "game.cpp"
// #include "ranking.cpp"
#include "instruction.cpp"

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
    sf::Texture t1, t2, b1, t3, t4;
    sf::Sprite s1, s2, bb1, s3, s4; 
    sf::Vector2f mp;
    Login();
    bool Open() {return window.isOpen();}
    void refresh();
    void openWindow(); 
};
Login::Login()
{
    this->window.create(sf::VideoMode(3000, 1200),"Game!!!");
    openWindow();
}
void Login::openWindow()
{
    mp.x = sf::Mouse::getPosition(this->window).x;
    mp.y = sf::Mouse::getPosition(this->window).y;

    // bike
    t1.loadFromFile("resources/NEWbike1.png");
    s1.setTexture(t1);
    s1.setPosition(sf::Vector2f(2000, 200));

    // ranking
    t2.loadFromFile("resources/champion_board.png");
    s2.setTexture(t2);
    s2.setPosition(sf::Vector2f(100,100));

    s1.setScale(sf::Vector2f(1.2f, 1.2f));
    s2.setScale(sf::Vector2f(1.2f, 1.2f));

    // background
    b1.loadFromFile("resources/loginbg.png");
    bb1.setTexture(b1);
    bb1.setPosition(sf::Vector2f(0, 0));

    // label in front of bike
    t3.loadFromFile("resources/click.png");
    s3.setTexture(t3);
    s3.setPosition(sf::Vector2f(2010, 950));
    s3.setScale(sf::Vector2f(0.2f, 0.2f));

    // intruction
    t4.loadFromFile("resources/book.png");
    s4.setTexture(t4);
    s4.setPosition(sf::Vector2f(150, 750));
    s4.setScale(sf::Vector2f(0.6f, 0.6f));


    
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
                        // play game
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
                        // ??????????????????
                        // Ranking rank;
                    }
                }
            if(isSpriteHover(s4.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                    {
                        // ????????????
                        Instruct instruct;
                        if(!instruct.window.isOpen())
                            Login login;
                    }
                }
        }
        refresh();
    }
}
void Login::refresh()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(bb1);
    this->window.draw(s1);
    this->window.draw(s2);
    this->window.draw(s3);
    this->window.draw(s4);
    this->window.display();
}