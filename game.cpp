#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include "player.h"

class Game
{
public:
    int c;
    int k;
    sf::RenderWindow window;
    sf::Texture t1, t3, ot1;
    sf::Sprite s1, s3, os1;
    std::vector<sf::Sprite> obstacles;
    int t1PosX, t3PosX, dovePos;
    time_t startTime, endTime;
    Game();
    void refresh(Player &player);
    void openWindow(); 
    void collision(Player &player, sf::Sprite &obs);
};
Game::Game()
{
    this->c = 0;
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
    player.t2.loadFromFile(fileName, sf::IntRect(30,370,450,770));
    player.s2.setTexture(player.t2);
    player.s2.setPosition(sf::Vector2f(100,400));
    ot1.loadFromFile("dove.png", sf::IntRect(1285,460,2285,1200));
    // ot1.loadFromFile("dove.png");
    os1.setTexture(ot1);
    os1.setScale(sf::Vector2f(0.3f, 0.3f));
    dovePos = 700;
    os1.setPosition(sf::Vector2f(dovePos, 700));
    obstacles.push_back(os1);

    // std::cout << os1.getPosition().x << std::endl;
    // std::cout << os1.getGlobalBounds().width << std::endl;

    float dt;
    sf::Clock dt_clock;

    
    sf::Clock timer;
    while(window.isOpen())
    {
        dt = dt_clock.restart().asMilliseconds();
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                sf::Time elapsed = timer.getElapsedTime();
                std::cout << elapsed.asSeconds() << std::endl;
                window.close();
            }
            player.velocity.x = 0.f;
            player.velocity.y = 0.f;
            if(sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Right:
                    {
                        player.velocity.x += player.moveSpeed * dt;
                        break;
                    }
                    case sf::Keyboard::Left:
                    {
                        player.velocity.x += -player.moveSpeed * dt;
                        break;
                    }
                    case sf::Keyboard::Up:
                    {
                        player.velocity.y += -player.moveSpeed * dt;
                        break;
                    }
                    case sf::Keyboard::Down:
                    {
                        player.velocity.y += player.moveSpeed * dt;
                        break;
                    }
                    default:
                        break;
                }
                player.s2.move(player.velocity);
            }
        }
        collision(player, os1);
        refresh(player);
    }
}
void Game::refresh(Player &player)
{
    this->window.clear(sf::Color::Black);
    s1.setPosition(sf::Vector2f(t1PosX, 0));
    s3.setPosition(sf::Vector2f(t3PosX, 0));
    os1.setPosition(sf::Vector2f(dovePos, 700));
    std::string fileName = "Newbike" + std::to_string(k/10) + ".png";
    player.t2.loadFromFile(fileName, sf::IntRect(30,370,450,770));
    player.s2.setTexture(player.t2);
    player.checkPosition();
    this->window.draw(this->s1);
    this->window.draw(this->s3);
    this->window.draw(player.s2);
    this->window.draw(this->os1);
    this->window.display();
    k == 10 ? k = 49 : k--;
    t1PosX == -(t1.getSize().x) ? t1PosX = t1.getSize().x : t1PosX--;
    t3PosX == -(t3.getSize().x) ? t3PosX = t3.getSize().x : t3PosX--;
    dovePos--;
}
void Game::collision(Player &player, sf::Sprite &obs)
{
    c++;
    sf::FloatRect playerBounds = player.s2.getGlobalBounds();
    sf::FloatRect obsBounds = obs.getGlobalBounds();
    if( playerBounds.intersects(obsBounds))
    {
        std::cout << "撞到鴿子了"  << c << std::endl;
        // std::cout << playerBounds.left << "," << obsBounds.left << std::endl;
    }
}