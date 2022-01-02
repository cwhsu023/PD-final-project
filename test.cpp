#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>


bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) 
{
    if (sprite.contains(mp))
    {
        return true;
    }
    return false;
}


int main()
{       

    sf::RenderWindow window, window2, window3;
            window.create(sf::VideoMode(3000, 2500),"My first Visual Studio window!");
    
    sf::Texture texture;
    if(!texture.loadFromFile("button1.png"))
    {
        return 1;
    }
    sf::Sprite sprite1;
    sprite1.setTexture(texture);

    sf::Texture texture2;
    if(!texture2.loadFromFile("champion_board.png"))
    {
        return 1;
    }
    sf::Sprite sprite2;
    sprite2.setTexture(texture2);

    sf::Texture texture3;
    if(!texture3.loadFromFile("topview_car.png"))
    {
        return 1;
    }
    sf::Sprite sprite3;
    sprite3.setTexture(texture3);
    

    sf::Vector2f mp;
    mp.x = sf::Mouse::getPosition(window).x;
    mp.y = sf::Mouse::getPosition(window).y;



        while(window.isOpen())
        {
            sf::Event event;
                
                while(window.pollEvent(event))
                {
                    if(event.type == sf::Event::Closed)
                        window.close();                 
            
                    if(isSpriteHover(sprite1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                    {
                        if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                        {
                                window2.create(sf::VideoMode(1800, 1600),"Game!");
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
                                            }
                                        }
                                    }
                                    
                                    window2.clear(sf::Color::Black);
                                    window2.draw(sprite3);
                                    window2.display();
                                }
                        }
                    }
                    if(isSpriteHover(sprite2.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
                    {
                        if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
                        {
                                window.create(sf::VideoMode(1800, 1600),"Rank!");
                                while(window.isOpen())
                                {
                                    sf::Event event;
                                    
                                    while(window.pollEvent(event))
                                    {
                                        if(event.type == sf::Event::Closed)
                                            window.close(); 
                                    }
                                }
                        }
                    }
                }
            window.clear(sf::Color::Black);

            sprite1.setPosition(sf::Vector2f(50, 300));
            
            window.draw(sprite1);

            sprite2.setPosition(sf::Vector2f(1500, 300));
            
            window.draw(sprite2);
            
            window.display();

}
        
return 0;
}