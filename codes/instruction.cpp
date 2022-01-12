#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
// #include "bike.h"
// #include "player.h"

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
    sf::Texture t1 ,t2 ,t_keyBoard;
    sf::Sprite s1 ,s2 ,s_keyBoard;
    // float speedControler ;
    int bikeAnimateControl  ;
    sf::Vector2f mp;
    sf::Vector2f velocity;

    Instruct();
    void refresh();
    void openWindow();
    void checkPosition();
    // void rectPosition();

};
Instruct::Instruct()
{
    this->window.create(sf::VideoMode(1200, 800),"How to play?");
    // speedControler = 0.2 ;
    bikeAnimateControl = 19 ;
    openWindow();
}
void Instruct::openWindow()
{
    // mp.x = sf::Mouse::getPosition(this->window).x;
    // mp.y = sf::Mouse::getPosition(this->window).y;
    t1.loadFromFile("resources/NEWroad.png");
    s1.setTexture(t1);
    s1.setScale(sf::Vector2f(0.5f, 0.68f));
    // s1.setPosition(sf::Vector2f(500, 500));
    //background setup
    t1.setRepeated(true);
    sf::Shader parallaxShader;
    parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic
        "    gl_FrontColor = gl_Color;"
        "}"
        , sf::Shader::Vertex);
    float offset = 0.f;
    sf::Clock clock ;
    // bike setting
    std::string fileName = "resources/Newbike4.png";
    t2.loadFromFile(fileName, sf::IntRect(30,370,450,740));
    s2.setTexture(t2);
    s2.setScale(sf::Vector2f(0.8f,0.8f)) ;
    s2.setPosition(sf::Vector2f(150,150));
    //create bike
    Bike instructBike ;

    //create keyboard
    t_keyBoard.loadFromFile("resources/arrow_key.png") ;
    s_keyBoard.setTexture(t_keyBoard);
    s_keyBoard.setPosition(sf::Vector2f(800,600));
    s_keyBoard.setScale(sf::Vector2f(2.0f,2.0f)) ;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                this -> window.close(); 

            velocity.x = 0.f;
            velocity.y = 0.f;
            if(sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Up:
                    {
                        velocity.y = -40;
                        break;
                    }
                    case sf::Keyboard::Down:
                    {
                        velocity.y = 40;
                        break;
                    }
                    case sf::Keyboard::Right:
                    {
                        instructBike.testbikeAccelerating();
                            break;
                    }
                    case sf::Keyboard::Left:
                    {
                        instructBike.bikeDecelerating();
                        break;
                    }
                    default:
                        break;

                }
                s2.move(velocity);
                // velocity.x = 0.f;
                // velocity.y = 0.f;
            }
        }
        
       
        window.clear();
        float speedControler = instructBike.bikeSpeed() ;
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() * speedControler);
        window.draw(s1, &parallaxShader);
        window.draw(s_keyBoard) ;
        refresh();
        bikeAnimateControl-- ;
        if(bikeAnimateControl < 4)
        {
            bikeAnimateControl = 19;
        }
        
    }
}
void Instruct::refresh()
{
    // this->window.clear(sf::Color::Black);
    // this->window.draw(s1);
    std::string fileName = "resources/Newbike" + std::to_string(bikeAnimateControl/4) + ".png";
    t2.loadFromFile(fileName, sf::IntRect(30,370,450,740));
    s2.setTexture(t2);
    checkPosition();
    this->window.draw(s2);
    this->window.display();
}
void Instruct::checkPosition()
{
    if(s2.getGlobalBounds().left < 150)
        s2.setPosition(150, s2.getPosition().y);
    if(s2.getGlobalBounds().left + s2.getGlobalBounds().width > 510)
        s2.setPosition(510 - s2.getGlobalBounds().width, s2.getPosition().y);
    if(s2.getPosition().y < 150)
        s2.setPosition(s2.getPosition().x, 150);
    if(s2.getGlobalBounds().top + s2.getGlobalBounds().height > 800)
        s2.setPosition(s2.getPosition().x, 800 - s2.getGlobalBounds().height);
    // std::cout << s2.getGlobalBounds().left << std::endl;
    // std::cout << s2.getGlobalBounds().left + s2.getGlobalBounds().width << std::endl;
    // std::cout << s2.getGlobalBounds().top << std::endl;
    // std::cout << s2.getGlobalBounds().top + s2.getGlobalBounds().height << std::endl;
    // std::cout << std::endl;
}
