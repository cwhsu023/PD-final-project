#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include "player.h"
#include "obstacles.h"
#include "bike.h"
std::vector<Obstacles> allObstacle;
class Game
{
public:
    int c;
    bool inLibrary;
    sf::RenderWindow window;
    sf::Texture t1, gOverT, t_heart1, t_heart2, t_heart3;
    sf::Sprite s1, gOverS, s_heart1, s_heart2, s_heart3;
    int t1PosX, t3PosX, dovePos;
    time_t startTime, endTime;
    Game();
    void refresh(Player &player ,int bikeAnimateControl, float currentSpeed);
    void openWindow();
    void heart(int playerLife);
};
Game::Game()
{
    this->c = 0;
    this->inLibrary = false;
    this->window.create(sf::VideoMode(3000, 1200),"Game!!!");
    openWindow();
}
void Game::heart(int playerLife)
{
    std::string fileName = "resources/valentinesday_heart.png" ;
    this -> t_heart1.loadFromFile(fileName);
    this -> s_heart1.setTexture(this -> t_heart1);
    this -> t_heart2.loadFromFile(fileName);
    this -> s_heart2.setTexture(this -> t_heart2);
    this -> t_heart3.loadFromFile(fileName);
    this -> s_heart3.setTexture(this -> t_heart3);
    this -> s_heart1.setScale(sf::Vector2f(0.3f, 0.3f));
    this -> s_heart2.setScale(sf::Vector2f(0.3f, 0.3f));
    this -> s_heart3.setScale(sf::Vector2f(0.3f, 0.3f));

    if(playerLife == 3)
    {
        s_heart1.setPosition(sf::Vector2f(100,20)) ;
        s_heart2.setPosition(sf::Vector2f(250,20)) ;
        s_heart3.setPosition(sf::Vector2f(400,20)) ;
        this -> window.draw(this -> s_heart1) ;
        this -> window.draw(this -> s_heart2) ;
        this -> window.draw(this -> s_heart3) ;
    }
    if(playerLife == 2)
    {
        s_heart1.setPosition(sf::Vector2f(100,20)) ;
        s_heart2.setPosition(sf::Vector2f(250,20)) ;
        this -> window.draw(this -> s_heart1) ;
        this -> window.draw(this -> s_heart2) ;
    }
    if(playerLife == 1)
    {
        s_heart1.setPosition(sf::Vector2f(100,20)) ;
        this -> window.draw(this -> s_heart1) ;
    }
}
void Game::openWindow()
{
    //setting backgound
    t1.loadFromFile("resources/NEWroad.png");
    s1.setTexture(t1);
    t1PosX = 0;
    s1.setPosition(sf::Vector2f(t1PosX, 0));
    
    //setting bike 
    Player player;
    

    // obstacles
    dovePos = 700;
    Obstacles dove1(dovePos+1000, 700, -2, 0);
    allObstacle.push_back(dove1);
    Obstacles dove2(dovePos+1800, 950, -2, 0);
    allObstacle.push_back(dove2);

    // background moving setting 
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

    float dt;
    sf::Clock dt_clock;

    sf::Clock timer;

    int bikeAnimateControl = 4 ;
    //跑了幾圈while 
    int distane =0 ;
    //速度
    // float speedControler = 0.01 ;
    Bike bike;
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
                allObstacle.erase(allObstacle.begin(), allObstacle.begin()+allObstacle.size());
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
                        // bike.bikeAccelerating() ;
                        bike.testbikeAccelerating();
                        break;
                    }
                    case sf::Keyboard::Left:
                    {
                        bike.bikeDecelerating();
                        break;
                    }
                    case sf::Keyboard::Up:
                    {
                        player.velocity.y = -70;
                        break;
                    }
                    case sf::Keyboard::Down:
                    {
                        player.velocity.y = 70;
                        break;
                    }
                    default:
                        break;
                }
                player.s2.move(player.velocity);
                player.rectangle.move(player.velocity);
            }
        }
        for(int i = 0; i < allObstacle.size(); i++)
        {
            
            bool hit = false;
            hit = allObstacle[i].collision(player);
            if(hit)
            {
                allObstacle.erase(allObstacle.begin()+i);
            }
        }
        

        // refresh player
        if(!player.hit)
        {
            //first bakgound , second bike , third dove or others ! display~
            //background drawing
            window.clear();
            float speedControler = bike.bikeSpeed() ;
            float currentSpeed = clock.restart().asSeconds() * speedControler;
            parallaxShader.setUniform("offset", offset += currentSpeed);
            window.draw(s1, &parallaxShader);
            refresh(player, bikeAnimateControl, currentSpeed);
            bikeAnimateControl-- ;
            if(bikeAnimateControl < 1)
            {
                bikeAnimateControl = 4;
            }
            heart(player.life);
            window.display();
        }
        else
        {
            // player flashing if collide
            for(int i = 1; i < 20; i++)
            {
                (i/3) % 2 == 0 ? player.hit = true : player.hit = false;
                //first bakgound , second bike , third dove or others ! display~
                //background drawing
                window.clear();
                float speedControler = bike.bikeSpeed() ;
                float currentSpeed = clock.restart().asSeconds() * speedControler;
                parallaxShader.setUniform("offset", offset += currentSpeed);
                window.draw(s1, &parallaxShader);
                refresh(player, bikeAnimateControl, currentSpeed);
                bikeAnimateControl-- ;
                if(bikeAnimateControl < 1)
                {
                    bikeAnimateControl = 4;
                }
                heart(player.life);
                window.display();
                dt = dt_clock.restart().asMilliseconds();
            }
            player.hit = false;
        }
        if(player.life < 0)
        {
            // gameover setting
            sf::Time elapsed = timer.getElapsedTime();
            gOverT.loadFromFile("resources/topView_car.png");
            gOverS.setTexture(gOverT);
            gOverS.setPosition(sf::Vector2f(700, 700));
            std::cout << "Game over. You've survived for " << elapsed.asSeconds() << " seconds" << std::endl;
            allObstacle.erase(allObstacle.begin(), allObstacle.begin()+allObstacle.size());
            // window.close();
        }
        if(offset > 1 && !inLibrary )
        {
            t1.loadFromFile("resources/library.png");
            s1.setTexture(t1);
            inLibrary = true;
        }

        
    }
}
void Game::refresh(Player &player, int bikeAnimateControl, float currentSpeed)
{
    // bike animation 
    std::string fileName = "resources/Newbike" + std::to_string(bikeAnimateControl) + ".png";
    player.t2.loadFromFile(fileName, sf::IntRect(30,370,450,740));
    player.s2.setTexture(player.t2);
    player.checkPosition();
    player.rectPosition();
    for(auto &obs : allObstacle)
    {
        // move obstacle
        obs.move(currentSpeed * this->s1.getGlobalBounds().width);
    }
    for(auto &obs : allObstacle)
    {
        // obstacle behind bike draw first
        // std::cout << bikeSpeed << std::endl;
        if(obs.obsSprite.getGlobalBounds().top > player.s2.getGlobalBounds().top)
        {
            this->window.draw(obs.obsSprite);
            this->window.draw(obs.circle);
        }
    }
    if(!player.hit)
    {
        this->window.draw(player.s2);
        this->window.draw(player.rectangle);
    }
    for(auto &obs : allObstacle)
    {
        // obstacle in front of bike
        if(obs.obsSprite.getGlobalBounds().top <= player.s2.getGlobalBounds().top)
        {
            this->window.draw(obs.obsSprite);
            this->window.draw(obs.circle);
        }
    }
    
    // game over
    this->window.draw(gOverS);
}