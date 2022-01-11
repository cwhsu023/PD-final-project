#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include "player.h"
#include "bike.h"

class Game
{
public:
    int c;
    int k;
    sf::RenderWindow window;
    sf::Texture t1, t3, ot1;
    sf::Sprite s1, s3, os1;
    // sf::CircleShape circle;
    std::vector<sf::CircleShape> obstacles;
    int t1PosX, t3PosX, dovePos;
    time_t startTime, endTime;
    Game();
    void refresh(Player &player ,int bikeAnimateControl);
    void openWindow(); 
    void collision(Player &player);
    void setCircle(int x, int y);
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
    //setting backgound
    t1.loadFromFile("resources/NEWroad.png");
    s1.setTexture(t1);
    t1PosX = 0;
    s1.setPosition(sf::Vector2f(t1PosX, 0));
    t3.loadFromFile("resources/NEWroad.png");
    s3.setTexture(t3);
    t3PosX = t3.getSize().x;
    s3.setPosition(sf::Vector2f(t3PosX,0));

    //setting bike 
    Player player;
    std::string fileName = "resources/Newbike" + std::to_string(k/10) + ".png";
    player.t2.loadFromFile(fileName, sf::IntRect(30,370,450,740));
    player.s2.setTexture(player.t2);
    player.s2.setPosition(sf::Vector2f(100,275));
    player.rectangle.setSize(sf::Vector2f(450, 50));
    player.rectangle.setFillColor(sf::Color::Transparent);
    // player.rectangle.setOutlineColor(sf::Color::Red);
    // player.rectangle.setOutlineThickness(5);
    player.rectangle.setPosition(100, 600);

    //setting dove
    ot1.loadFromFile("resources/dove.png", sf::IntRect(1300,460,980, 750));
    // ot1.loadFromFile("dove.png");
    os1.setTexture(ot1);
    os1.setScale(sf::Vector2f(0.15f, 0.15f));
    dovePos = 700;
    os1.setPosition(sf::Vector2f(dovePos, 700));
    setCircle(dovePos, 720);


    // std::cout << os1.getPosition().x << std::endl;
    // std::cout << os1.getGlobalBounds().width << std::endl;

    // background moving setting 
    t1.setRepeated(true);
    sf::Shader parallaxShader;
    parallaxShader.loadFromMemory(
        "uniform float offset;"

        "void main() {"
        "    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
        "    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
        "    gl_TexCoord[0].x = gl_TexCoord[0].x + offset;" // magic !!!
        "    gl_FrontColor = gl_Color;"
        "}"
        , sf::Shader::Vertex);
    float offset = 0.f;
    sf::Clock clock ;
    

    //bike moving setting
    float dt;
    sf::Clock dt_clock;

    sf::Clock timer;

    int bikeAnimateControl = 1 ;
    //跑了幾圈while 
    int distane =0 ;
    //速度
    float speedControler = 0.01 ;
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
                        // player.velocity.x += player.moveSpeed * dt;
                        speedControler += 0.01 ;
                        if(speedControler >= 0.11  )
                            speedControler = 0.11 ;
                        break;
                    }
                    case sf::Keyboard::Left:
                    {
                        // player.velocity.x += -player.moveSpeed * dt;
                        speedControler -= 0.02 ;
                        if(speedControler <= 0 )
                            speedControler = 0.01 ;
                        break;
                    }
                    case sf::Keyboard::Up:
                    {
                        player.s2.move(0,-70);
                        player.rectangle.move(0,-70);
                        break;
                    }
                    case sf::Keyboard::Down:
                    {
                        player.s2.move(0,70);
                        player.rectangle.move(0,70);
                        break;
                    }
                    default:
                        break;
                }
                player.s2.move(player.velocity);
                player.rectangle.move(player.velocity);
            }
        }
        //first bakgound , second bike , third dove or others ! display~
        //background drawing
        window.clear();
        parallaxShader.setUniform("offset", offset += clock.restart().asSeconds() * speedControler);
        window.draw(s1, &parallaxShader);
        

        refresh(player ,bikeAnimateControl) ;
        bikeAnimateControl++ ;
        if(bikeAnimateControl > 4)
        {
            bikeAnimateControl = 1;
        }
        window.display();
        

    }
    
}
//refresh  = bike animation 
void Game::refresh(Player &player, int bikeAnimateControl)
{
    //dove ; but this should be in another part !
    os1.setPosition(sf::Vector2f(dovePos, 700));
    for(auto &obs : obstacles)
    {
        obs.setPosition(sf::Vector2f(dovePos, 720));
    }
    // bike animation 
    std::string fileName = "resources/Newbike" + std::to_string(bikeAnimateControl) + ".png";
    player.t2.loadFromFile(fileName, sf::IntRect(30,370,450,740));
    player.s2.setTexture(player.t2);
    player.checkPosition();
    player.rectPosition();
    this->window.draw(player.s2);
    this->window.draw(this->os1);
    for(auto &obs : obstacles)
    {
        this->window.draw(obs);
    }
    this->window.draw(player.rectangle);
}
void Game::collision(Player &player)
{
    c++;
    for(auto &obs : obstacles)
    {
        sf::FloatRect playerBounds = player.rectangle.getGlobalBounds();
        sf::FloatRect obsBounds = obs.getGlobalBounds();
        if( playerBounds.intersects(obsBounds))
        {
            std::cout << "撞到鴿子了"  << c << std::endl;
            // std::cout << playerBounds.left << "," << obsBounds.left << std::endl;
        }
    }
}
void Game::setCircle(int x, int y)
{
    sf::CircleShape circle;
    circle.setRadius(40);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(5);
    circle.setPosition(x, y);
    obstacles.push_back(circle);
}