#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <time.h>

class Player
{
public:
    friend class Game;
    Player();
};
Player::Player()
{

}
class Game
{
public:
    int k;
    sf::RenderWindow window;
    sf::Texture t1, t2, t3, ot1;
    sf::Sprite s1, s2, s3, os1;
    int t1PosX, t3PosX;
    time_t startTime, endTime;
    Game();
    void refresh();
    void openWindow(); 
};
Game::Game()
{
    this->k = 49;
    this->window.create(sf::VideoMode(3000, 1200),"Game!!!");
    openWindow();
}
void Game::openWindow()
{
    t1.loadFromFile("NEWroad.png");
    s1.setTexture(t1);
    t1PosX = 0;
    s1.setPosition(sf::Vector2f(t1PosX, 0));
    t3.loadFromFile("NEWroad.png");
    s3.setTexture(t3);
    t3PosX = t3.getSize().x;
    s3.setPosition(sf::Vector2f(t3PosX,0));
    Player player;
    std::string fileName = "Newbike" + std::to_string(k/10) + ".png";
    t2.loadFromFile(fileName);
    s2.setTexture(t2);
    s2.setPosition(sf::Vector2f(100,400));
    // ot1.loadFromFile("dove.png", sf::IntRect(1285,460,2285,1200));
    ot1.loadFromFile("dove.png");
    os1.setTexture(ot1);
    os1.setScale(sf::Vector2f(0.3f, 0.3f));
    os1.setPosition(sf::Vector2f(700, 700));
    std::cout << ot1.getSize().x << std::endl;
    std::cout << ot1.getSize().y << std::endl;
    std::cout << t1.getSize().x << "," << t1.getSize().y << std::endl;

    
    startTime = time(0);
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                double time_dif = difftime( time(0), startTime);
                std::cout << "You've played " << time_dif << " seconds" << std::endl;  // 如果要計時要換一個好一點的計時方法
                window.close();
            }
            if(sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Right:
                    {
                        s2.move(20,0);
                        break;
                    }
                    case sf::Keyboard::Left:
                    {
                        s2.move(-20,0);
                        break;
                    }
                    case sf::Keyboard::Up:
                    {
                        s2.move(0,-20);
                        break;
                    }
                    case sf::Keyboard::Down:
                    {
                        s2.move(0,20);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        refresh();
    }
}
void Game::refresh()
{
    this->window.clear(sf::Color::Black);
    s1.setPosition(sf::Vector2f(t1PosX, 0));
    s3.setPosition(sf::Vector2f(t3PosX, 0));
    this->window.draw(this->s1);
    std::string fileName = "Newbike" + std::to_string(k/10) + ".png";
    t2.loadFromFile(fileName);
    s2.setTexture(t2);
    this->window.draw(this->s3);
    this->window.draw(s2);
    this->window.draw(this->os1);
    this->window.display();
    k == 10 ? k = 49 : k--;
    t1PosX == -(t1.getSize().x) ? t1PosX = t1.getSize().x : t1PosX--;
    t3PosX == -(t3.getSize().x) ? t3PosX = t3.getSize().x : t3PosX--;

}

