#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
// #include <>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
// #include <windows.h>
// #include "player.h"

// bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) 
// {
//     if (sprite.contains(mp))
//     {
//         return true;
//     }
//     return false;
// }

class Ranking
{
public:
    sf::RenderWindow window;
    sf::Texture tbg ,t1, t2, t3, t4, t5;
    sf::Sprite sbg ,s1 ,s2, s3, s4, s5;
    sf::SoundBuffer dingbuffer;
    sf::Vector2f mp;
    sf::Font font;
    sf::Text text;

    Ranking();
    void refresh();
    void openWindow();
};
Ranking::Ranking()
{
    this->window.create(sf::VideoMode(863, 620),"Ranking");
    openWindow();
}
void Ranking::openWindow()
{
    tbg.loadFromFile("resources/rkbg.png");
	sbg.setTexture(tbg);
    sbg.setScale(sf::Vector2f(1.0f, 1.0f));
    
    t1.loadFromFile("resources/wood.png");
    s1.setTexture(t1);
    s1.setScale(sf::Vector2f(1.5f, 1.0f));
    s1.setPosition(sf::Vector2f(137, 20));
    
	t2.loadFromFile("resources/wood.png");
    s2.setTexture(t2);
    s2.setScale(sf::Vector2f(1.5f, 1.0f));
    s2.setPosition(sf::Vector2f(137, 130));
    
    
	t3.loadFromFile("resources/wood.png");
    s3.setTexture(t3);
    s3.setScale(sf::Vector2f(1.5f, 1.0f));
    s3.setPosition(sf::Vector2f(137, 240));
    
	t4.loadFromFile("resources/wood.png");
    s4.setTexture(t4);
    s4.setScale(sf::Vector2f(1.5f, 1.0f));
    s4.setPosition(sf::Vector2f(137, 350));
    
	t5.loadFromFile("resources/wood.png");
	s5.setTexture(t5);
    s5.setScale(sf::Vector2f(1.5f, 1.0f));
    s5.setPosition(sf::Vector2f(137, 460));

    font.loadFromFile("resources/gen.ttf");
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);

    
    dingbuffer.loadFromFile("resources/dingdon.ogg");
	sf::Sound ding(dingbuffer);
	ding.play();

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

        }
        window.clear();
        refresh();
        std::ifstream ifs("resources/output.txt", std::ios::in);
        std::string s_scores;
        if(!ifs.is_open())
        {
            std::cout << "Failed to open"<< std::endl ;
        }
        else
        {
            // std::string s_scores;
            //std::string name;
            int score;
            int sc1,sc2;
            int i=0;
            for(int i = 0; i < 5; i++)
            {
                //std::cout << score;
                ifs >> score;
                int sc1 = score / 100;
                int sc2 = score - sc1*100;
                text.setString("TOP"+std::to_string(i+1)+":   "+std::to_string(sc1) + "." + std::to_string(sc2)+ "  s");
                text.setPosition(240, 60+110*i);
                this->window.draw(text);
            }
            // while(std::getline(ifs, s_scores))
            // {
            //     std::cout << s_scores << std::endl ;
            //     // std::cout << s_scores[0] << std::endl;
            //     // names.push_back(s_scores);
            // }
            // std::cout << s_scores  <<"y"<<std::endl;
            this->window.display();
            ifs.close();
            //std::cout << s_scores  <<"y"<<std::endl;
        }
        
    }
    //input ranking.txt 
    // std::string fileName("resources/output.txt");
    // std::fstream file_out;
    // file_out.open(filename ,std::ios_base::out);
    // std::ifstream ifs("resources/output.txt", std::ios::in);
    // std::string s_scores;
    // if(!ifs.is_open())
    // {
    //     std::cout << "Failed to open"<< std::endl ;
    // }
    // else
    // {
    //     // std::string s_scores;
    //     std::string name;
    //     int score;
    //     int sc1,sc2;
    //     int i=0;
    //     while (ifs >> score)
    //         {
    //             sc1 = score/100;
    //             sc2 = score%100;
    //             text.setString(std::to_string(sc1) + "." + std::to_string(sc2));
    //             text.setPosition(20, 20+5*i);
    //             this->window.draw(text);
    //             i++;
    //         }
    //     // while(std::getline(ifs, s_scores))
    //     // {
    //     //     std::cout << s_scores << std::endl ;
    //     //     // std::cout << s_scores[0] << std::endl;
    //     //     // names.push_back(s_scores);
    //     // }
    //     // std::cout << s_scores  <<"y"<<std::endl;
    //     ifs.close();
    //     //std::cout << s_scores  <<"y"<<std::endl;
    // }




}
void Ranking::refresh()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(sbg);
    this->window.draw(s1);
    this->window.draw(s2);
    this->window.draw(s3);
    this->window.draw(s4);
    this->window.draw(s5);
    
}

