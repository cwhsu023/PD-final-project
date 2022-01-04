#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<string>

bool isSpriteHover(sf::FloatRect sprite, sf::Vector2f mp) 
{
    if (sprite.contains(mp))
    {
        return true;
    }
    return false;
}

class Page
{
public:
    sf::RenderWindow window;
    sf::Texture t[1000];
    sf::Sprite s[1000];
    // sf::Texture *temp_t;
    // sf::Sprite *temp_s;
    int imageCnt;
    Page(float width, float height, std::string name);
    void addImage(float posX, float posY, std::string imageName);
    bool Open() {return window.isOpen();}
    void refresh();
    
    
};
Page::Page(float width, float height, std::string name)
{
    this->imageCnt = 0;
    this->window.create(sf::VideoMode(width, height),name);
}
void Page::addImage(float posX, float posY, std::string imageName)
{
    sf::Texture texture;
    if(!texture.loadFromFile(imageName))
        std::cout << "fail loading image" << std::endl;
    t[imageCnt] = texture;
    sf::Sprite sprite;
    sprite.setTexture(t[imageCnt]);
    sprite.setPosition(sf::Vector2f(posX, posY));
    s[imageCnt] = sprite;
    this->imageCnt++;
}
void Page::refresh()
{
    this->window.clear(sf::Color::Black);
    for(int i = 0; i < this->imageCnt; i++)
        this->window.draw(this->s[i]);
    this->window.display();
}