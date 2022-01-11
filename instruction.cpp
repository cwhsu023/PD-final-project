#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/System.hpp>
#include <iostream>
#include <string>
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
    sf::Texture t1 ,t2;
    sf::Sprite s1 ,s2;
    float speedControler ;
    int bikeAnimateControl  ;
    sf::Vector2f mp;

    Instruct();
    void refresh();
    void openWindow();
    void checkPosition();
    // void rectPosition();

};
Instruct::Instruct()
{
    this->window.create(sf::VideoMode(1200, 800),"How to play?");
    speedControler = 0.2 ;
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
    std::string fileName = "resources/Newbike4.png";
    t2.loadFromFile(fileName, sf::IntRect(30,200,450,740));
    s2.setTexture(t2);
    s2.setPosition(sf::Vector2f(200,150));
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();  
        }
        window.clear();
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() * speedControler);
        window.draw(s1, &parallaxShader);
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
    t2.loadFromFile(fileName, sf::IntRect(30,200,450,740));
    s2.setTexture(t2);
    // checkPosition();
    this->window.draw(s2);
    this->window.display();
}
void Instruct::checkPosition()
{
    if(s2.getGlobalBounds().left < 0)
        s2.setPosition(0, s2.getPosition().y);
    if(s2.getGlobalBounds().left + s2.getGlobalBounds().width > 2950)
        s2.setPosition(2950 - s2.getGlobalBounds().width, s2.getPosition().y);
    if(s2.getPosition().y < 275)
        s2.setPosition(s2.getPosition().x, 275);
    if(s2.getGlobalBounds().top + s2.getGlobalBounds().height > 1250)
        s2.setPosition(s2.getPosition().x, 1250 - s2.getGlobalBounds().height);
    // std::cout << s2.getPosition().x << std::endl;
    // std::cout << s2.getPosition().y << std::endl;
}
// void Instruct::rectPosition()
// {
//     if(rectangle.getGlobalBounds().left < 0)
//         rectangle.setPosition(0, rectangle.getPosition().y);
//     if(rectangle.getGlobalBounds().left + rectangle.getGlobalBounds().width > 2950)
//         rectangle.setPosition(2950 - rectangle.getGlobalBounds().width, rectangle.getPosition().y);
//     if(rectangle.getPosition().y < 600)
//         rectangle.setPosition(rectangle.getPosition().x, 600);
//     if(rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height > 1200)
//         rectangle.setPosition(rectangle.getPosition().x, 1200 - rectangle.getGlobalBounds().height);
// }