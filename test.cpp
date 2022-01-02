#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;

int main()
{
sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
sf::CircleShape shape(100.f);
shape.setFillColor(sf::Color::Blue);

while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            cout << "close" << endl;
            window.close();
        }
        if (isKeyPressed(Keyboard::A)) {
            changeX = -2;
        } else if (isKeyPressed(Keyboard::D) {
            changeX = 2;
        } else {
            changeX = 0;
        } if (isKeyPressed(Keyboard::W) {
            changeY = -2;
        } else if (isKeyPressed(Keyboard::S)) {
            changeY = 2;
        } else {
            changeY = 0;
        }

    }
    

    window.clear();
    window.draw(shape);
    window.display();
}

return 0;
}