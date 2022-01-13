#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>
#include "game.cpp"
#include "ranking.cpp"
#include "instruction.cpp"



class Login
{
public:
    sf::RenderWindow window;
    sf::Texture t1, t2, b1, t3, t4 ,t_thief, t_bike ,t_last;
    sf::Sprite s1, s2, bb1, s3, s4, s_thief, s_bike, s_last; 
    sf::Vector2f mp;
    sf::SoundBuffer bgmBuffer ;
    int thiefAnimateControl;
    int ridingAnimateControl ;
    Login();
    bool Open() {return window.isOpen();}
    bool switchToAnimate2 ;
    bool letsStart ;
    void refresh();
    void refreshAnimateStart();
    void openWindow(); 
    void start();
    void animate1(int thiefAnimateControl);
    void animate2(int ridingAnimateControl);
};
Login::Login()
{
    this->window.create(sf::VideoMode(3000, 1200),"Game!!!");
    thiefAnimateControl = 4 ;
    ridingAnimateControl = 19 ;
    switchToAnimate2 = false ;
    letsStart = false ;
    openWindow();
}
void Login::openWindow()
{
    mp.x = sf::Mouse::getPosition(this->window).x;
    mp.y = sf::Mouse::getPosition(this->window).y;

    //playing BGM
	bgmBuffer.loadFromFile("resources/loginBGM.ogg");
	sf::Sound bgm(bgmBuffer);
	bgm.play();
	bgm.setLoop(true);

    // bike
    t1.loadFromFile("resources/NEWbike1.png");
    s1.setTexture(t1);
    s1.setPosition(sf::Vector2f(2000, 200));
    s1.setScale(sf::Vector2f(1.2f, 1.2f));
    // s1.setRotation(-45.f);

    // ranking
    t2.loadFromFile("resources/champion_board.png");
    s2.setTexture(t2);
    s2.setPosition(sf::Vector2f(70,70));
    s2.setScale(sf::Vector2f(0.8f, 0.8f));
    


    b1.loadFromFile("resources/loginBackG.png", sf::IntRect(2000,0,3000,1200));
    bb1.setTexture(b1);
    bb1.setPosition(sf::Vector2f(0, 0));

    // label in front of bike
    t3.loadFromFile("resources/click.png");
    s3.setTexture(t3);
    s3.setPosition(sf::Vector2f(75, 950));
    s3.setScale(sf::Vector2f(0.2f, 0.2f));

    // intruction
    t4.loadFromFile("resources/book.png");
    s4.setTexture(t4);
    s4.setPosition(sf::Vector2f(300, 80));
    s4.setScale(sf::Vector2f(0.45f, 0.45f));

    //thief
    t_thief.loadFromFile("resources/thief1.png", sf::IntRect(30,320,500,780));
    s_thief.setTexture(t_thief);
    s_thief.setPosition(sf::Vector2f(70,570)) ;
    s_thief.setScale(sf::Vector2f(1.2f,1.2f));
    
    //bike
    t_bike.loadFromFile("resources/Newbike4.png");
    s_bike.setTexture(t_bike);
    s_bike.setPosition(sf::Vector2f(130,650));
    s_bike.setScale(sf::Vector2f(1.1f,1.1f));

    //final bike
    t_last.loadFromFile("resources/Newbike4.png");
    s_last.setTexture(t_last);
    s_last.setPosition(sf::Vector2f(2000,200));
    s_last.setScale(sf::Vector2f(1.1f,1.1f));
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();  
            if(isSpriteHover(s_thief.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    // play game
                    std::cout << "start" <<std::endl ;
                    start();
                    if(letsStart)
                    {
                        bgm.stop();
                        window.close();
                        Game game;
                        if(!game.window.isOpen())
                            Login login;
                    }
                }
            }
            else if(isSpriteHover(s3.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    // play game
                    std::cout << "start" <<std::endl ;
                    start();
                    if(letsStart)
                    {
                        bgm.stop();
                        window.close();
                        Game game;
                        if(!game.window.isOpen())
                            Login login;
                    }
                }
            }
            if(isSpriteHover(s2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    // 排行榜的資訊
                    bgm.stop();
                    Ranking rank;
                }
                bgm.play();
            }
            if(isSpriteHover(s4.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                    // 遊戲說明
                    bgm.stop();
                    Instruct instruct;
                }
                bgm.play();
            }
            
        }
        refresh();
        window.draw(s_thief);
        window.display();
    }
}
void Login::animate1(int thiefAnimatecontrol)
{
    std::string fileName = "resources/thief" + std::to_string(thiefAnimateControl/4) + ".png";
    t_thief.loadFromFile(fileName, sf::IntRect(30,320,500,780));
    s_thief.setTexture(t_thief);
    // this->window.draw(s_thief);
}
void Login::animate2(int ridingAnimateControl)
{
    std::string fileName = "resources/Newbike" + std::to_string(ridingAnimateControl/4) + ".png";
    t_bike.loadFromFile(fileName, sf::IntRect(30,370,450,740));
    s_bike.setTexture(t_bike);
    this -> window.draw(s_bike);

}
void Login::refresh()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(bb1);
    // this->window.draw(s_thief);
    this->window.draw(s2);
    this->window.draw(s3);
    this->window.draw(s4);
}
void Login::refreshAnimateStart()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(bb1);
    // this->window.draw(s_thief);
    this->window.draw(s2);
    // this->window.draw(s3);
    this->window.draw(s4);
}
void Login::start()
{
    int i=0 ;
    while(i <= 350)
    {
        //animate display~
        refreshAnimateStart();
        if(!switchToAnimate2)
        {
            animate1(thiefAnimateControl);
            window.draw(s_thief);
            if(thiefAnimateControl < 79)
            {
                thiefAnimateControl++;
            }
        }
        // std :: cout << thiefAnimateControl << std::endl ; 
        if(thiefAnimateControl == 79)
        {
            animate2(ridingAnimateControl);
            sf::Vector2f velocity(10.0f,0.0f);
            // sf::Vector2f velocity.y = 0.0f ;
            s_bike.move(velocity) ;
            ridingAnimateControl--;
            if(ridingAnimateControl <4)
            {
                ridingAnimateControl = 19 ;
            }
            // std::cout << "control: "<<thiefAnimateControl  << ","<< ridingAnimateControl << std::endl ;
            switchToAnimate2 = true ;
        }
        window.display();
        i++;
        if(i == 349)
        {
            letsStart = true ;
        }
    }
}