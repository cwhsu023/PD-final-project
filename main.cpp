#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<string>
#include "page.cpp"

int main()
{    
    Page login(3000, 2500, "Game!!");
    login.addImage(50, 300, "button1.png");
    login.addImage(1500, 300, "champion_board.png");
    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(login.window).x;
    mp.y = sf::Mouse::getPosition(login.window).y;

    while(login.Open())
    {
        sf::Event event;
            
        while(login.window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                login.window.close();                 
    
            if(isSpriteHover(login.s[0].getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            {
                if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                {
                        sf::RenderWindow window2;
                        window2.create(sf::VideoMode(1800, 1600),"Let's Gooooooo!!!!!");
                        sf::Texture texture3;
                        if(!texture3.loadFromFile("topview_car.png"))
                        {
                            return 1;
                        }
                        sf::Sprite sprite3;
                        sprite3.setTexture(texture3);
                        int sprite3x = 50, sprite3y = 300;
                        sprite3.setPosition(sf::Vector2f(sprite3x, sprite3y));
                        while(window2.isOpen())
                        {
                            sf::Event event;

                            while(window2.pollEvent(event))
                            {
                                if(event.type == sf::Event::Closed)
                                    window2.close(); 
                                if(sf::Event::KeyPressed)
                                {
                                    switch(event.key.code)
                                    {
                                        case sf::Keyboard::Right:
                                        {
                                            sprite3.move(20,0);
                                            break;
                                        }
                                        case sf::Keyboard::Left:
                                        {
                                            sprite3.move(-20,0);
                                            break;
                                        }
                                        case sf::Keyboard::Up:
                                        {
                                            sprite3.move(0,-20);
                                            break;
                                        }
                                        case sf::Keyboard::Down:
                                        {
                                            sprite3.move(0,20);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            }
                            
                            window2.clear(sf::Color::Black);
                            window2.draw(sprite3);
                            window2.display();
                        }
                }
            }
            // if(isSpriteHover(sprite2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            // {
            //     if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            //     {
            //             window.create(sf::VideoMode(1800, 1600),"Rank!");
            //             while(window.isOpen())
            //             {
            //                 sf::Event event;
                            
            //                 while(window.pollEvent(event))
            //                 {
            //                     if(event.type == sf::Event::Closed)
            //                         window.close(); 
            //                 }
            //             }
            //     }
            // }
        }
        login.refresh();

}
        
return 0;
}