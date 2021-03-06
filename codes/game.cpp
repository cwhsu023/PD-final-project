#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include "player.h"
// #include "obstacles.h"
#include "bike.h"
#include "randomDove.h"
// std::vector<Obstacles> allObstacle;
bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) 
{
    if (sprite.contains(mp))
    {
        return true;
    }
    return false;
}
class Game
{
public:
    int c, totalDist;
    bool inLibrary;
    sf::RenderWindow window;
    sf::Texture t1, gOverT, t_heart1, t_heart2, t_heart3, t_libraryFront, winT;
    sf::Sprite s1, gOverS, s_heart1, s_heart2, s_heart3, s_libraryFront, winS;
    sf::Font font;
    sf::Text text, text2;
    sf::RectangleShape r1, r2;
    sf::Vector2f mp;
    sf::SoundBuffer bgmBuffer, winBuffer, loseBuffer, crashBuffer, startBuffer;
    int t1PosX, t3PosX, dovePos;
    time_t startTime, endTime;
    Game();
    void refresh(Player &player ,int bikeAnimateControl, float currentSpeed);
    void openWindow();
    void heart(int playerLife);
    friend class Obstacles;
    void victory(Player &player , int victoryAnimateControl);
    int wirteToFile(int sss);
};
Game::Game()
{
    this->totalDist = 4;  // how many pic to ride
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
    //playing BGM
	bgmBuffer.loadFromFile("resources/loginBGM.ogg");
	sf::Sound bgm(bgmBuffer);

    //setting win & fail music
	winBuffer.loadFromFile("resources/win.ogg");
	sf::Sound win(winBuffer);
	loseBuffer.loadFromFile("resources/lose.ogg");
	sf::Sound lose(loseBuffer);
    crashBuffer.loadFromFile("resources/crash.ogg");
	sf::Sound crash(crashBuffer);
    startBuffer.loadFromFile("resources/ggo.ogg");
    sf::Sound start(startBuffer);

    // mouse position
    mp.x = sf::Mouse::getPosition(this->window).x;
    mp.y = sf::Mouse::getPosition(this->window).y;

    //setting backgound
    t1.loadFromFile("resources/NEWroad.png");
    s1.setTexture(t1);
    t1PosX = 0;
    s1.setPosition(sf::Vector2f(t1PosX, 0));
    t_libraryFront.loadFromFile("resources/45libraryFront.png");
    s_libraryFront.setTexture(t_libraryFront);
    // s_libraryFront.setPosition(sf::Vector2f(totalDist * this->s1.getGlobalBounds().width, 0));
    
    //setting bike 
    Player player;
    
    // obstacles
    dovePos = 700;
    // srand(time(NULL));
    srand(time(NULL));
    getRandomDove getRandomDove;

    // play music
    bgm.play();
	bgm.setLoop(true);

    // text setting
    font.loadFromFile("resources/gen.ttf");


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

    int bikeAnimateControl = 19 ;
    int victoryAnimateControl = 15 ;
    //??????
    // float speedControler = 0.01 ;
    Bike bike;
    start.play();
    while(window.isOpen())
    {
        dt = dt_clock.restart().asMilliseconds();
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                allObstacle.erase(allObstacle.begin(), allObstacle.begin()+allObstacle.size());
                window.close();
            }
            if(isSpriteHover(r1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "play again" << std::endl;
                        allObstacle.erase(allObstacle.begin(), allObstacle.begin()+allObstacle.size());
                        window.close();
                        Game game;
                    }
                }
            if(isSpriteHover(r2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                {
                    if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                    {
                        allObstacle.erase(allObstacle.begin(), allObstacle.begin()+allObstacle.size());
                        window.close();
                    }
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
                        bike.bikeAccelerating();
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
                    case sf::Keyboard::LShift:
                    {
                        player.life = 3;  // ????????????
                        break;
                    }
                    default:
                        break;
                }
                player.s2.move(player.velocity);
                player.rectangle.move(player.velocity);
            }
        }
        if(offset > totalDist && !inLibrary )
        {
            // window.clear();
            t1.loadFromFile("resources/45libraryBack.png");
            s1.setTexture(t1);
            inLibrary = true ;
        }
        if(offset > totalDist + 0.4)
        {
            // winning

            window.clear();
            // scoring
            if(!player.arrive)
            {
                bgm.stop();
                win.play();
                sf::Time elapsed = timer.getElapsedTime();
                int sss = elapsed.asSeconds() * 100;
                int place = wirteToFile(sss);
                std::cout << place << std::endl;
                int sc1 = sss / 100;
                int sc2 = sss - sc1*100;
                std::string winStr = "You won!!! You did it in " + std::to_string(sc1) + "." + std::to_string(sc2) + " seconds!!!";
                std::cout << winStr << std::endl;
                text.setString(std::to_string(sc1) + "." + std::to_string(sc2));
                text.setFont(font);
                text.setCharacterSize(70);
                text.setFillColor(sf::Color::Black);
                text.setPosition(sf::Vector2f(330,445));
                std::string p;
                if(place == 1)
                    p = "New High Score!!!";
                else if(place == 0)
                    p = "The slowest so far!!!";
                else
                    p = "#" + std::to_string(place) + " on the scoreboard.";
                text2.setString(p);
                text2.setFont(font);
                text2.setCharacterSize(45);
                text2.setFillColor(sf::Color::Red);
                text2.setPosition(sf::Vector2f(105,250));
                winT.loadFromFile("resources/win.png");
                winS.setTexture(winT);
                winS.setPosition(sf::Vector2f(100, 300));
                winS.setScale(sf::Vector2f(0.8f,0.8f));r1.setSize(sf::Vector2f(110, 25));
                r1.setSize(sf::Vector2f(200, 32));
                r1.setFillColor(sf::Color::Transparent);
                // r1.setOutlineColor(sf::Color::Red);
                // r1.setOutlineThickness(5);
                r1.setPosition(275, 610);
                r2.setSize(sf::Vector2f(200, 32));
                r2.setFillColor(sf::Color::Transparent);
                // r2.setOutlineColor(sf::Color::Red);
                // r2.setOutlineThickness(5);
                r2.setPosition(275, 740);
                player.arrive = true;
            }
            // inLibrary = true;
            float speedControler = bike.bikeSpeed() ;
            float currentSpeed = clock.restart().asSeconds() * speedControler;
            offset += currentSpeed;
            if(inLibrary && (offset - totalDist) * this->s1.getGlobalBounds().width > this->s1.getGlobalBounds().width - 3000)
                offset = totalDist + (static_cast<float>(this->s1.getGlobalBounds().width - 3000) / this->s1.getGlobalBounds().width);
            parallaxShader.setUniform("offset", offset = offset);
            window.draw(s1, &parallaxShader);
            victory(player ,victoryAnimateControl);
            player.velocity.x = 10.0f;
            player.velocity.y = 0.0f;
            player.s_victory.move(player.velocity);
            // text.move(player.velocity);
            // if((offset - totalDist) * this->s1.getGlobalBounds().width > 2000)
            //     std::cout << "yep "<< std::endl ;
            // std::cout << s1.getGlobalBounds().left << std::endl;
            float ppos = -((offset - totalDist) * s1.getGlobalBounds().width);
            s_libraryFront.setPosition(sf::Vector2f(ppos, 0)); //sf::Vector2f(totalDist * this->s1.getGlobalBounds().width
            window.draw(s_libraryFront) ;
    
            victoryAnimateControl--;
            if(victoryAnimateControl < 4)
            {
                victoryAnimateControl = 15 ;
            }
            window.display();
            
            continue ;
        }
        for(int i = 0; i < allObstacle.size(); i++)
        {
            // chceck collision
            bool hit = false;
            hit = allObstacle[i].collision(player);
            if(hit)
            {
                crash.play();
                allObstacle.erase(allObstacle.begin()+i);
            }
        }
        

        // refresh player
        if(!player.hit)
        {
            //first bakgound , second bike , third dove or others ! display~
            //background drawing
            window.clear();
            if(!player.alive)
                bike.speedControl = 0;
            float speedControler = bike.bikeSpeed() ;
            float currentSpeed = clock.restart().asSeconds() * speedControler;
            offset += currentSpeed;
            if(inLibrary && (offset - totalDist) * this->s1.getGlobalBounds().width > this->s1.getGlobalBounds().width - 3000)
                offset = totalDist + (static_cast<float>(this->s1.getGlobalBounds().width - 3000) / this->s1.getGlobalBounds().width);
            parallaxShader.setUniform("offset", offset = offset);
            window.draw(s1, &parallaxShader);
            refresh(player, bikeAnimateControl, currentSpeed);
            bikeAnimateControl-- ;
            if(bikeAnimateControl < 4)
            {
                bikeAnimateControl = 19;
            }
            heart(player.life);
            window.display();
        }
        else
        {
            // player flashing if collide
            for(int i = 1; i < 20; i++)
            {
                // crash.play();
                (i/3) % 2 == 0 ? player.hit = true : player.hit = false;
                //first bakgound , second bike , third dove or others ! display~
                //background drawing
                window.clear();
                float speedControler = bike.bikeSpeed() ;
                float currentSpeed = clock.restart().asSeconds() * speedControler;
                offset += currentSpeed;
                if(inLibrary && (offset - totalDist) * this->s1.getGlobalBounds().width > this->s1.getGlobalBounds().width - 3000)
                    offset = totalDist + (static_cast<float>(this->s1.getGlobalBounds().width - 3000) / this->s1.getGlobalBounds().width);
                parallaxShader.setUniform("offset", offset = offset);
                window.draw(s1, &parallaxShader);
                refresh(player, bikeAnimateControl, currentSpeed);
                bikeAnimateControl-- ;
                if(bikeAnimateControl < 4)
                {
                    bikeAnimateControl = 19;
                }
                heart(player.life);
                window.display();
                dt = dt_clock.restart().asMilliseconds();
            }
            player.hit = false;
        }
        if(player.life <= 0 && player.alive)
        {
            // gameover setting
            bgm.stop();
            lose.play();
            sf::Time elapsed = timer.getElapsedTime();
            gOverT.loadFromFile("resources/gameover.png");
            gOverS.setTexture(gOverT);
            gOverS.setPosition(sf::Vector2f(1150, 400));
            gOverS.setScale(sf::Vector2f(1.2f,1.2f));
            r1.setSize(sf::Vector2f(110, 25));
            r1.setFillColor(sf::Color::Transparent);
            // r1.setOutlineColor(sf::Color::Red);
            // r1.setOutlineThickness(5);
            r1.setPosition(1322, 610);
            r2.setSize(sf::Vector2f(110, 25));
            r2.setFillColor(sf::Color::Transparent);
            // r2.setOutlineColor(sf::Color::Red);
            // r2.setOutlineThickness(5);
            r2.setPosition(1322, 675);
            std::cout << "Game over. You've survived for " << elapsed.asSeconds() << " seconds" << std::endl;
            allObstacle.erase(allObstacle.begin(), allObstacle.begin()+allObstacle.size());
            player.alive = false;
        }

        
    }
}
void Game::refresh(Player &player, int bikeAnimateControl, float currentSpeed)
{
    // game over
    if(!player.alive)
    {
        this->window.draw(gOverS);
        this->window.draw(r1);
        this->window.draw(r2);
    }
    // bike animation 
    std::string fileName = "resources/Newbike" + std::to_string(bikeAnimateControl/4) + ".png";
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
}
void Game::victory(Player &player , int victoryAnimateControl)
{
    //bike victory animate
    // std::cout <<"victory" << std::endl ;
    std::string fileName3 = "resources/NewYahoo" + std::to_string(victoryAnimateControl/4) + ".png";
    player.t_victory.loadFromFile(fileName3, sf::IntRect(600,300,450,740)); //, sf::IntRect(30,370,450,740)
    player.s_victory.setTexture(player.t_victory);
    this -> window.draw(player.s_victory);
    
    this->window.draw(winS);
    this->window.draw(text);
    this->window.draw(r1);
    this->window.draw(r2);
    if(this->c < 0)
    {
        this->window.draw(text2);
    }
    c++;
    if(c == 4)
        c = -4;
}
int Game::wirteToFile(int sss)
{
    std::ifstream inFile("resources/output.txt");
    int score;
    int scoreCnt = 0;
    if(inFile)  //???????????????
    {
        while(inFile >> score)
        {
            scoreCnt++;
        }
    }
    inFile.close();
    std::ifstream inFile2("resources/output.txt");
    float* scoreArray = new float[scoreCnt];
    scoreCnt = 0;
    while(inFile2 >> score)
    {
        scoreArray[scoreCnt] = score;
        scoreCnt++;
    }
    inFile2.close();
    int the_score = sss;
    int temp_score = 0;
    int place = 0;
    std::ofstream outFile("resources/output.txt");
    if(outFile)
    {
        for(int i = 0; i < scoreCnt+1; i++)
        {
            if(i < scoreCnt)
            {
                if(scoreArray[i] < the_score)
                {
                    temp_score = scoreArray[i];
                }
                else
                {
                    temp_score = the_score;
                    the_score = scoreArray[i];
                    if(place == 0)
                        place = i + 1;
                }
            }
            else
            {
                temp_score = the_score;
            }
            outFile << temp_score << std::endl;
        }
    }
    outFile.close();
    return place;
}