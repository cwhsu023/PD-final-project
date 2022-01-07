#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <time.h>

class Game
{
public:
    int k;
    sf::RenderWindow window;
    sf::Texture t1, t2, t3;
    sf::Sprite s1, s2, s3;
    int t1PosX, t3PosX;
    time_t startTime, endTime;
    Game();
    void refresh();
    void openWindow(); 
};
Game::Game()
{
    this->k = 49;
    this->window.create(sf::VideoMode(3000, 2500),"Game!!!");
    openWindow();
}
void Game::openWindow()
{
    t1.loadFromFile("Backgroundnew.jpg");
    s1.setTexture(t1);
    t1PosX = 0;
    s1.setPosition(sf::Vector2f(t1PosX, 300));
    t3.loadFromFile("Backgroundnew.jpg");
    s3.setTexture(t3);
    t3PosX = t3.getSize().x;
    s3.setPosition(sf::Vector2f(t3PosX,400));
    std::string fileName = "Newbike" + std::to_string(k/10) + ".png";
    t2.loadFromFile(fileName);
    s2.setTexture(t2);
    s2.setPosition(sf::Vector2f(100,400));
    
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
    s1.setPosition(sf::Vector2f(t1PosX, 300));
    s3.setPosition(sf::Vector2f(t3PosX, 300));
    this->window.draw(this->s1);
    std::string fileName = "Newbike" + std::to_string(k/10) + ".png";
    t2.loadFromFile(fileName);
    s2.setTexture(t2);
    this->window.draw(this->s3);
    this->window.draw(this->s2);
    this->window.display();
    k == 10 ? k = 49 : k--;
    t1PosX == -(t1.getSize().x) ? t1PosX = t1.getSize().x : t1PosX--;
    t3PosX == -(t3.getSize().x) ? t3PosX = t3.getSize().x : t3PosX--;

}

