#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/System.hpp>
#include <iostream>
#include <string>

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
    sf::Texture t1;  // 需要新的圖片在這邊增加texture, sprite
    sf::Sprite s1;
    sf::Vector2f mp;
    Ranking();
    void refresh();
    void openWindow(); 
};
Ranking::Ranking()
{
    this->window.create(sf::VideoMode(1000, 600),"Ranking!!!");  // 視窗大小
    openWindow();
}
void Ranking::openWindow()
{
    // 如果要偵測滑鼠開這兩行
    // mp.x = sf::Mouse::getPosition(this->window).x;
    // mp.y = sf::Mouse::getPosition(this->window).y;
    t1.loadFromFile("resources/button1.png");  // 插入圖片
    s1.setTexture(t1);
    s1.setPosition(sf::Vector2f(500, 500));  // 圖片位置
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();  
            // if(isSpriteHover(s1.getGlobalBounds(), sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) == true)
            //     {
            //         if(event.type == sf::Event::MouseButtonReleased &&  event.mouseButton.button == sf::Mouse::Left)
            //         {
            //               // 點選後的指令
            //         }
            //     }
        }
        refresh();
    }
}
void Ranking::refresh()
{
    this->window.clear(sf::Color::Black);
    this->window.draw(s1);  // 顯示圖片
    this->window.display();
}